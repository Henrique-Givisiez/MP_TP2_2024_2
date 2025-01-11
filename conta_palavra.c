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

char* ContaPalavra(const char * caminhoArquivo) {
    char* conteudo = lerArquivo(caminhoArquivo);
    return conteudo;
}