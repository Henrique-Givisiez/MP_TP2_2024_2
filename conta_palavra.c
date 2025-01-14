// Copyright 2024 Henrique Givisiez dos Santos

/**
 * @file conta_palavra.c
 * @brief Implementação do programa para contar palavras em arquivos de texto.
 *
 * Este arquivo contém as definições de funções para leitura de arquivos,
 * manipulação de mapas de palavras, ordenação e geração de saídas formatadas.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h>
#include "./conta_palavra.h"

/**
 * @brief Lê o conteúdo de um arquivo e retorna como uma string wide (UTF-8).
 * 
 * @param caminhoArquivo Caminho para o arquivo a ser lido.
 * @return wchar_t* Conteúdo do arquivo em wide string. Deve ser liberado pelo chamador.
 */
wchar_t* lerArquivo(const char* caminhoArquivo) {
    setlocale(LC_ALL, ""); // Define o locale para UTF-8

    FILE* arquivo = fopen(caminhoArquivo, "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return NULL;
    }

    // Posiciona o ponteiro no final do arquivo para determinar o tamanho
    fseek(arquivo, 0, SEEK_END);
    long tamanhoArquivo = ftell(arquivo);
    rewind(arquivo); // Retorna o ponteiro ao início do arquivo

    // Aloca memória para armazenar o conteúdo do arquivo
    char* conteudo = (char*)malloc((tamanhoArquivo + 1) * sizeof(char));
    if (conteudo == NULL) {
        perror("Erro ao alocar memória para o conteúdo do arquivo");
        fclose(arquivo);
        return NULL;
    }

    // Lê o conteúdo do arquivo para a string
    size_t lido = fread(conteudo, 1, tamanhoArquivo, arquivo);
    if (lido != (size_t)tamanhoArquivo) {
        perror("Erro ao ler o arquivo");
        free(conteudo);
        fclose(arquivo);
        return NULL;
    }

    // Garante que a string é terminada corretamente
    conteudo[tamanhoArquivo] = '\0';

    // Converte para wchar_t
    size_t tamanhoWide = mbstowcs(NULL, conteudo, 0);
    if (tamanhoWide == (size_t)-1) {
        perror("Erro ao converter para wchar_t");
        free(conteudo);
        fclose(arquivo);
        return NULL;
    }

    wchar_t* conteudoWide = (wchar_t*)malloc((tamanhoWide + 1) * sizeof(wchar_t));
    if (conteudoWide == NULL) {
        perror("Erro ao alocar memória para wchar_t");
        free(conteudo);
        fclose(arquivo);
        return NULL;
    }

    mbstowcs(conteudoWide, conteudo, tamanhoWide + 1);

    free(conteudo);
    fclose(arquivo);
    return conteudoWide;
}

/**
 * @brief Cria uma estrutura de mapa para armazenar palavras e suas contagens.
 * 
 * @return Map* Ponteiro para o mapa criado. Deve ser liberado pelo chamador.
 */
Map* criarMap() {
    // Aloca a estrutura Map
    Map* mapa = (Map*)malloc(sizeof(Map));
    if (mapa == NULL) {
        perror("Erro ao alocar memória para o mapa");
        exit(EXIT_FAILURE);
    }

    // Inicializa o mapa vazio
    mapa->tamanho = 0;

    return mapa;
}

/**
 * @brief Adiciona uma palavra ao mapa, incrementando sua contagem se já existir.
 * 
 * @param mapa Ponteiro para o mapa onde a palavra será adicionada.
 * @param palavra Palavra a ser adicionada.
 */
void adicionarPalavra(Map* mapa, const wchar_t* palavra) {
    // Verifica se a palavra já existe no mapa
    for (int i = 0; i < mapa->tamanho; i++) {
        if (wcscmp(mapa->itens[i].palavra, palavra) == 0) {
            mapa->itens[i].contagem++; // Incrementa a contagem
            return;
        }
    }

    // Verifica se há espaço no array fixo
    if (mapa->tamanho >= 1000) {
        fprintf(stderr, "Erro: limite de 1000 itens no mapa atingido\n");
        return;
    }

    // Adiciona uma nova palavra ao mapa
    wcscpy(mapa->itens[mapa->tamanho].palavra, palavra); // Copia a palavra
    mapa->itens[mapa->tamanho].contagem = 1;             // Define a contagem inicial
    mapa->tamanho++;                                     // Incrementa o tamanho do mapa
}

/**
 * @brief Libera a memória utilizada por uma estrutura de mapa.
 * 
 * @param mapa Ponteiro para o mapa a ser liberado.
 */
void liberarMap(Map* mapa) {
    free(mapa);
}

/**
 * @brief Conta as palavras em um texto e retorna um mapa com as contagens.
 * 
 * @param texto Texto a ser processado.
 * @return Map* Ponteiro para o mapa com palavras e contagens. Deve ser liberado pelo chamador.
 */
Map* contarPalavras(const wchar_t* texto) {
    // Duplicar texto (como wide string)
    wchar_t* textoCopia = wcsdup(texto);
    if (!textoCopia) {
        perror("Erro ao duplicar texto");
        return NULL;
    }

    Map* mapa = criarMap(); // Inicializa o mapa
    wchar_t* estado;
    wchar_t* token = wcstok(textoCopia, L" \r\n", &estado);

    while (token != NULL) {
        // Adiciona a palavra diretamente como wchar_t
        adicionarPalavra(mapa, token);

        token = wcstok(NULL, L" \r\n", &estado);
    }

    free(textoCopia);
    return mapa;
}

/**
 * @brief Converte um mapa de palavras e contagens para uma string formatada.
 * 
 * @param mapa Ponteiro para o mapa a ser convertido.
 * @return char* String formatada com palavras e contagens. Deve ser liberada pelo chamador.
 */
char* mapParaString(Map* mapa) {
    // Buffer para armazenar o resultado
    size_t tamanhoTotal = 1024; // Tamanho inicial
    char* resultado = (char*)malloc(tamanhoTotal);
    if (!resultado) {
        perror("Erro ao alocar memória para a saída");
        return NULL;
    }
    resultado[0] = '\0'; // Inicia como string vazia

    for (int i = 0; i < mapa->tamanho; i++) {
        char palavraChar[256];
        wcstombs(palavraChar, mapa->itens[i].palavra, sizeof(palavraChar)); // Converte para char*

        char buffer[256];
        snprintf(buffer, sizeof(buffer), "%s,%d", palavraChar, mapa->itens[i].contagem);

        // Ajusta o tamanho do resultado, se necessário
        if (strlen(resultado) + strlen(buffer) + 2 > tamanhoTotal) {
            tamanhoTotal *= 2;
            resultado = (char*)realloc(resultado, tamanhoTotal);
            if (!resultado) {
                perror("Erro ao redimensionar o buffer de saída");
                return NULL;
            }
        }

        // Adiciona ao resultado
        strcat(resultado, buffer);
        if (i < mapa->tamanho - 1) {
            strcat(resultado, ","); // Adiciona separador entre itens
        }
    }

    return resultado;
}

/**
 * @brief Define a ordem de caracteres considerando acentos e capitalização.
 * 
 * @param c Caractere a ser avaliado.
 * @return int Rank do caractere.
 */
int ordemAcento(wchar_t c) {
    wchar_t base = towlower(c); // Obtém a forma base minúscula do caractere

    if (c == base) {
        return 0; // Minúscula base
    } else if (c == towupper(base)) {
        return 1; // Maiúscula base
    } else {
        return 2; // Outras variações
    }
}

/**
 * @brief Converte um caractere para sua forma base minúscula.
 * 
 * @param c Caractere a ser convertido.
 * @return char Caractere convertido.
 */
char converteMinusculo(char c) {
    switch ((unsigned char)c) {
        // -- Variações de 'a'
        case 'A': case 'Á': case 'À': case 'Â': case 'Ã':
        case 'a': case 'á': case 'à': case 'â': case 'ã':
            return 'a';

        // -- Variações de 'e'
        case 'E': case 'É': case 'Ê':
        case 'e': case 'é': case 'ê':
            return 'e';

        // -- Variações de 'i'
        case 'I': case 'Í':
        case 'i': case 'í':
            return 'i';

        // -- Variações de 'o'
        case 'O': case 'Ó': case 'Ô': case 'Õ':
        case 'o': case 'ó': case 'ô': case 'õ':
            return 'o';

        // -- Variações de 'u'
        case 'U': case 'Ú':
        case 'u': case 'ú':
            return 'u';

        // -- Variações de 'c' (cedilha)
        case 'C': case 'Ç':
        case 'c': case 'ç':
            return 'c';

        // Se quiser lidar com 'n' e til espanhol, adicione aqui:
        // case 'Ñ': case 'ñ': return 'n';

        default:
            // Outros caracteres: apenas converta para minúsculo básico
            return (char)tolower((unsigned char)c);
    }
}

/**
 * @brief Remove os acentos de um caractere wide, se aplicável.
 * 
 * @param c Caractere a ser processado.
 * @return wchar_t Caractere sem acento.
 */
wchar_t removerAcento(wchar_t c) {
    switch (c) {
        case L'à': case L'á': case L'â': case L'ã': case L'ä': case L'å': return L'a';
        case L'À': case L'Á': case L'Â': case L'Ã': case L'Ä': case L'Å': return L'A';
        case L'è': case L'é': case L'ê': case L'ë': return L'e';
        case L'È': case L'É': case L'Ê': case L'Ë': return L'E';
        case L'ì': case L'í': case L'î': case L'ï': return L'i';
        case L'Ì': case L'Í': case L'Î': case L'Ï': return L'I';
        case L'ò': case L'ó': case L'ô': case L'õ': case L'ö': return L'o';
        case L'Ò': case L'Ó': case L'Ô': case L'Õ': case L'Ö': return L'O';
        case L'ù': case L'ú': case L'û': case L'ü': return L'u';
        case L'Ù': case L'Ú': case L'Û': case L'Ü': return L'U';
        case L'ç': return L'c';
        case L'Ç': return L'C';
        default: return c; // Retorna o caractere original se não for acentuado
    }
}

/**
 * @brief Função de comparação para ordenação de palavras no mapa.
 * 
 * @param a Ponteiro para o primeiro elemento.
 * @param b Ponteiro para o segundo elemento.
 * @return int Resultado da comparação (-, 0, +).
 */
int compararPalavras(const void* a, const void* b) {
    const Item* itemA = (const Item*)a;
    const Item* itemB = (const Item*)b;

    const wchar_t* strA = itemA->palavra;
    const wchar_t* strB = itemB->palavra;

    while (*strA != L'\0' && *strB != L'\0') {
        wchar_t charA = removerAcento(towlower(*strA)); // Remove acento e converte para minúsculo
        wchar_t charB = removerAcento(towlower(*strB)); // Remove acento e converte para minúsculo

        if (charA != charB) {
            return charA - charB; // Ordena com base no caractere normalizado
        }

        // Se os caracteres normalizados são iguais, ordena por capitalização
        if (*strA != *strB) {
            return *strB - *strA; // Maiúsculas antes de minúsculas
        }

        strA++;
        strB++;
    }

    // Se uma string terminou, a menor string vem primeiro
    return *strA - *strB;
}

/**
 * @brief Ordena o mapa de palavras em ordem alfabética.
 * 
 * @param mapa Ponteiro para o mapa a ser ordenado.
 */
void ordenarMapa(Map* mapa) {
    qsort(mapa->itens,
        mapa->tamanho,
        sizeof(Item),
        compararPalavras);
}

/**
 * @brief Converte uma string de caracteres multibyte para wide string.
 * 
 * @param str String multibyte.
 * @return wchar_t* Wide string correspondente. Deve ser liberada pelo chamador.
 */
wchar_t* converterParaWide(const char* str) {
    size_t tamanho = mbstowcs(NULL, str, 0); // Calcula o tamanho necessário
    if (tamanho == (size_t)-1) {
        perror("Erro ao converter string para wchar_t");
        return NULL;
    }

    wchar_t* strWide = (wchar_t*)malloc((tamanho + 1) * sizeof(wchar_t));
    if (strWide == NULL) {
        perror("Erro ao alocar memória para wchar_t");
        return NULL;
    }

    mbstowcs(strWide, str, tamanho + 1); // Faz a conversão
    return strWide;
}

/**
 * @brief Função principal para contar palavras em um arquivo.
 * 
 * @param caminhoArquivo Caminho para o arquivo a ser processado.
 * @return char* String formatada com palavras e contagens. Deve ser liberada pelo chamador.
 */
char* ContaPalavra(const char* caminhoArquivo) {
    // Obtém o conteúdo do arquivo como string
    wchar_t* conteudo = lerArquivo(caminhoArquivo);
    if (conteudo == NULL) {
        return NULL; // Retorna NULL em caso de erro
    }
    // Passa o conteúdo para a função contarPalavras
    Map* mapa = contarPalavras(conteudo);
    if (mapa == NULL) {
        free(conteudo);
        return NULL; // Retorna NULL se o mapa não for criado corretamente
    }

    ordenarMapa(mapa);

    // Converte o mapa para string e exibe
    char* resultado = mapParaString(mapa);

    // Libera memória
    free(conteudo);
    liberarMap(mapa);
    return resultado;
}
