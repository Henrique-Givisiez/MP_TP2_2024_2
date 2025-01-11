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

// Função de comparação para ordenar o mapa por palavra
int compararPalavras(const void* a, const void* b) {
    const Item* itemA = (const Item*)a;
    const Item* itemB = (const Item*)b;
    return strcmp(itemA->palavra, itemB->palavra);
}

// Função para ordenar o mapa
void ordenarMapa(Map* mapa) {
    qsort(mapa->itens, mapa->tamanho, sizeof(Item), compararPalavras);
}

char* ContaPalavra(const char * caminhoArquivo) {

    // Obtém o conteúdo do arquivo como string
    char* conteudo = lerArquivo(caminhoArquivo);
    // Passa o conteúdo para a função contarPalavras
    Map* mapa = contarPalavras(conteudo);

    // Converte o mapa para string e exibe
    char* resultado = mapParaString(mapa);

    // Libera memória
    free(conteudo);
    free(resultado);
    liberarMap(mapa);
    return resultado;
}