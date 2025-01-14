// Copyright 2024 Henrique Givisiez dos Santos
#ifndef CONTA_PALAVRA_H_
#define CONTA_PALAVRA_H_
#ifdef __cplusplus
extern "C" {
#endif
char* ContaPalavra(const char* caminho_arquivo);
wchar_t* lerArquivo(const char* caminhoArquivo);
// Estrutura para armazenar uma palavra e sua contagem
typedef struct {
    wchar_t palavra[256];  // Palavra com no máximo 49 caracteres
    int contagem;     // Quantidade de ocorrências
} Item;

// Estrutura para armazenar o "map"
typedef struct {
    Item itens[1000];      // Array dinâmico de itens
    int tamanho;   // Quantidade de itens no array
} Map;
Map* criarMap();
void adicionarPalavra(Map* mapa, const wchar_t* palavra);
void liberarMap(Map* mapa);
Map* contarPalavras(const wchar_t* texto);
char* mapParaString(Map* mapa);
int compararPalavras(const void* a, const void* b);
void ordenarMapa(Map* mapa);
int ordemAcento(wchar_t  c);
char converteMinusculo(char c);
#ifdef __cplusplus
}
#endif
#endif  // CONTA_PALAVRA_H_
