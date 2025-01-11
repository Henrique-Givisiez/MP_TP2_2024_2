// Copyright 2024 Henrique Givisiez dos Santos
#ifndef CONTA_PALAVRA_H_
#define CONTA_PALAVRA_H_
#ifdef __cplusplus
extern "C" {
#endif
char* ContaPalavra(const char* caminho_arquivo);
char* lerArquivo(const char* caminhoArquivo);
Map* criarMap();
void adicionarPalavra(Map* mapa, const char* palavra);
#ifdef __cplusplus
}
#endif
#endif  // CONTA_PALAVRA_H_
