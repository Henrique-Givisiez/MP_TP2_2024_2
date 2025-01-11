// Copyright 2024 Henrique Givisiez dos Santos
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "./conta_palavra.h"

// Função para processar o arquivo e retornar seu conteúdo como string
char* lerArquivo(const char* caminhoArquivo) {
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
    if ((unsigned char)conteudo[0] == 0xEF &&
    (unsigned char)conteudo[1] == 0xBB &&
    (unsigned char)conteudo[2] == 0xBF) {
    // Deslocar tudo para a esquerda
    memmove(conteudo, conteudo + 3, (tamanhoArquivo - 2));
    tamanhoArquivo -= 3;
    conteudo[tamanhoArquivo] = '\0';
}   
    if (conteudo == NULL) {
        perror("Erro ao alocar memória para o conteúdo do arquivo");
        fclose(arquivo);
        return NULL;
    }

    // Lê o conteúdo do arquivo para a string
    size_t lido = fread(conteudo, 1, tamanhoArquivo, arquivo);
    if (lido != tamanhoArquivo) {
        perror("Erro ao ler o arquivo");
        free(conteudo);
        fclose(arquivo);
        return NULL;
    }

    conteudo[tamanhoArquivo] = '\0'; // Garante que a string é terminada corretamente

    fclose(arquivo);
    return conteudo;
}

// Função para criar um "map" com palavras e contagens
Map* criarMap() {
    // Aloca o mapa dinamicamente
    Map* mapa = (Map*)malloc(sizeof(Map));
    if (mapa == NULL) {
        perror("Erro ao alocar memória para o mapa");
        exit(EXIT_FAILURE);
    }
    
    // Inicializa o mapa vazio
    mapa->itens = NULL;
    mapa->tamanho = 0;

    return mapa;
}

// Função para adicionar ou atualizar uma palavra no mapa
void adicionarPalavra(Map* mapa, const char* palavra) {
    for (size_t i = 0; i < mapa->tamanho; i++) {
        if (strcmp(mapa->itens[i].palavra, palavra) == 0) {
            mapa->itens[i].contagem++;
            return;
        }
    }

    // Se não encontrou, adiciona a nova palavra
    mapa->itens = (Item*)realloc(mapa->itens, (mapa->tamanho + 1) * sizeof(Item));
    if (mapa->itens == NULL) {
        perror("Erro ao realocar memória para itens");
        exit(EXIT_FAILURE);
    }

    strcpy(mapa->itens[mapa->tamanho].palavra, palavra);
    mapa->itens[mapa->tamanho].contagem = 1;
    mapa->tamanho++;
}

// Função para liberar memória
void liberarMap(Map* mapa) {
    free(mapa->itens);
    free(mapa);
}

// Função principal
Map* contarPalavras(const char* texto) {
    Map* mapa = criarMap();
    char* textoCopia = strdup(texto); // Criar uma cópia do texto para tokenizar
    char* token = strtok(textoCopia, " \r\n");

    while (token != NULL) {
        adicionarPalavra(mapa, token);
        token = strtok(NULL, " \r\n");
    }

    free(textoCopia); // Liberar a cópia do texto
    return mapa;
}

// Função para transformar o map em string
char* mapParaString(const Map* mapa) {
    size_t bufferSize = 1024; // Tamanho inicial do buffer
    char* resultado = (char*)malloc(bufferSize);
    if (resultado == NULL) {
        perror("Erro ao alocar memória para a string do mapa");
        exit(EXIT_FAILURE);
    }
    resultado[0] = '\0'; // Inicia a string vazia

    for (size_t i = 0; i < mapa->tamanho; i++) {
        char buffer[100];
        snprintf(buffer, sizeof(buffer), "%s,%d", mapa->itens[i].palavra, mapa->itens[i].contagem);
        if (strlen(resultado) + strlen(buffer) + 2 >= bufferSize) { // Realocar se necessário
            bufferSize *= 2;
            resultado = (char*)realloc(resultado, bufferSize);
            if (resultado == NULL) {
                perror("Erro ao realocar memória para a string do mapa");
                exit(EXIT_FAILURE);
            }
        }
        strcat(resultado, buffer);
        if (i < mapa->tamanho - 1) {
            strcat(resultado, ",");
        }
    }

    return resultado;
}

// Retorna "rank" para variações de acentos/maiúscula de uma mesma letra base
// Quanto MENOR o rank, MAIS cedo aparece na ordenação.
int ordemAcento(char c) {
    switch ((unsigned char)c) {
        // ---- Letra 'a'
        case 'a': return 0;
        case 'A': return 1;
        case 'á': return 2;
        case 'Á': return 3;
        case 'à': return 4;
        case 'À': return 5;
        case 'â': return 6;
        case 'Â': return 7;
        case 'ã': return 8;
        case 'Ã': return 9;

        // ---- Letra 'e'
        case 'e': return 0;
        case 'E': return 1;
        case 'é': return 2;
        case 'É': return 3;
        case 'ê': return 4;
        case 'Ê': return 5;

        // ---- Letra 'i'
        case 'i': return 0;
        case 'I': return 1;
        case 'í': return 2;
        case 'Í': return 3;

        // ---- Letra 'o'
        case 'o': return 0;
        case 'O': return 1;
        case 'ó': return 2;
        case 'Ó': return 3;
        case 'ô': return 4;
        case 'Ô': return 5;
        case 'õ': return 6;
        case 'Õ': return 7;

        // ---- Letra 'u'
        case 'u': return 0;
        case 'U': return 1;
        case 'ú': return 2;
        case 'Ú': return 3;

        // ---- Letra 'c' (cedilha)
        case 'c': return 0;
        case 'C': return 1;
        case 'ç': return 2;
        case 'Ç': return 3;

        // Para qualquer outra letra, devolvemos algo "padrão" (por ex., 0).
        // Isso significa que, se não for uma letra mapeada, não diferenciamos minúscula/acento.
        default:
            return 0;
    }
}


// Converte o caractere acentuado/maiúsculo em uma forma base minúscula.
// Exemplos: 'Á', 'à', 'â', 'ã' -> 'a', 'Ç' -> 'c', etc.
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


// Função de comparação para ordenar o mapa por palavra
int compararPalavras(const void* a, const void* b) {
    // Supondo que existam structs com campo .palavra
    const Item* itemA = (const Item*)a;
    const Item* itemB = (const Item*)b;

    const char* s1 = itemA->palavra;
    const char* s2 = itemB->palavra;

    while (*s1 != '\0' && *s2 != '\0') {
        // 1) Obtemos a letra base (em minúsculo)
        char base1 = converteMinusculo(*s1);
        char base2 = converteMinusculo(*s2);

        // 2) Se as bases forem diferentes, ordenamos primeiro por base
        if (base1 != base2) {
            return (base1 - base2); 
        } else {
            // 3) As bases são iguais, checamos o "rank" de acentuação
            int rank1 = ordemAcento(*s1);
            int rank2 = ordemAcento(*s2);

            if (rank1 != rank2) {
                return (rank1 - rank2);
            } else {
                // Mesmo rank => mesmo "tipo" de caractere (ou não mapeado).
                // Continuar para o próximo caractere
                s1++;
                s2++;
            }
        }
    }

    // 4) Se chegamos aqui, ou *s1 ou *s2 é '\0'.
    //    Se um terminou e o outro não, o que terminou é "menor"
    return (*s1 - *s2);
}

// Função para ordenar o mapa
void ordenarMapa(Map* mapa) {
    qsort(mapa->itens,
        mapa->tamanho,
        sizeof(Item),
        compararPalavras);
}

char* ContaPalavra(const char * caminhoArquivo) {

    // Obtém o conteúdo do arquivo como string
    char* conteudo = lerArquivo(caminhoArquivo);
    
    // Passa o conteúdo para a função contarPalavras
    Map* mapa = contarPalavras(conteudo);

    ordenarMapa(mapa);

    // Converte o mapa para string e exibe
    char* resultado = mapParaString(mapa);

    // Libera memória
    free(conteudo);
    liberarMap(mapa);
    return resultado;
}