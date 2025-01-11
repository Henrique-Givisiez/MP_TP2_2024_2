// Copyright 2024 Henrique Givisiez dos Santos
#ifndef CONTA_PALAVRA_H_
#define CONTA_PALAVRA_H_
#ifdef __cplusplus
extern "C" {
#endif
char* ContaPalavra(const char* caminho_arquivo);
char* lerArquivo(const char* caminhoArquivo);
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
Map* criarMap();
void adicionarPalavra(Map* mapa, const char* palavra);
void liberarMap(Map* mapa);
Map* contarPalavras(const char* texto);
char* mapParaString(const Map* mapa);
int compararPalavras(const void* a, const void* b);
void ordenarMapa(Map* mapa);
#ifdef __cplusplus
}
#endif
#endif  // CONTA_PALAVRA_H_
