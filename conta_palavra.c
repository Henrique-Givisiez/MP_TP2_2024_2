// Copyright 2024 Henrique Givisiez dos Santos
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

// Estrutura para armazenar uma palavra e sua contagem
typedef struct {
    char palavra[50]; // Palavra com no máximo 49 caracteres
    int contagem;     // Quantidade de ocorrências
} Item;

// Estrutura para armazenar o "map"
typedef struct {
    Item* itens;      // Array dinâmico de itens
    size_t tamanho;   // Quantidade de itens no array
} Map;

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
    char* token = strtok(textoCopia, " \n");

    while (token != NULL) {
        adicionarPalavra(mapa, token);
        token = strtok(NULL, " \n");
    }

    free(textoCopia); // Liberar a cópia do texto
    return mapa;
}

char* ContaPalavra(const char * caminhoArquivo) {
    
    // Obtém o conteúdo do arquivo como string
    char* conteudo = lerArquivo(caminhoArquivo);
    // Passa o conteúdo para a função contarPalavras
    Map* mapa = contarPalavras(conteudo);

    return conteudo;
}