// Copyright 2024 Henrique Givisiez dos Santos

/**
 * @file conta_palavra.h
 * @brief Declaração de funções e estruturas para contar palavras em arquivos de texto.
 *
 * Este arquivo contém definições de estruturas e protótipos de funções utilizadas para
 * processar textos, contar palavras, ordenar resultados e gerar strings formatadas.
 */

#ifndef CONTA_PALAVRA_H_
#define CONTA_PALAVRA_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Conta palavras em um arquivo de texto.
 * 
 * @param caminho_arquivo Caminho para o arquivo a ser processado.
 * @return char* String formatada contendo palavras e suas respectivas contagens.
 * A memória retornada deve ser liberada pelo chamador.
 */
char* ContaPalavra(const char* caminho_arquivo);

/**
 * @brief Lê o conteúdo de um arquivo de texto.
 * 
 * @param caminhoArquivo Caminho para o arquivo.
 * @return wchar_t* Conteúdo do arquivo lido. Deve ser liberado pelo chamador.
 */
wchar_t* lerArquivo(const char* caminhoArquivo);

/**
 * @brief Estrutura para armazenar uma palavra e sua contagem de ocorrências.
 */
typedef struct {
    wchar_t palavra[256]; ///< Palavra com no máximo 255 caracteres.
    int contagem;         ///< Quantidade de ocorrências da palavra.
} Item;

/**
 * @brief Estrutura para armazenar um mapa de palavras e contagens.
 */
typedef struct {
    Item itens[1000]; ///< Array de itens que contém palavras e suas contagens.
    int tamanho;      ///< Quantidade de itens presentes no array.
} Map;

/**
 * @brief Cria uma nova estrutura Map.
 * 
 * @return Map* Ponteiro para a nova estrutura Map. Deve ser liberada pelo chamador.
 */
Map* criarMap();

/**
 * @brief Adiciona uma palavra ao mapa, incrementando sua contagem caso já exista.
 * 
 * @param mapa Ponteiro para o mapa onde a palavra será adicionada.
 * @param palavra Palavra a ser adicionada.
 */
void adicionarPalavra(Map* mapa, const wchar_t* palavra);

/**
 * @brief Libera a memória utilizada por um mapa.
 * 
 * @param mapa Ponteiro para o mapa a ser liberado.
 */
void liberarMap(Map* mapa);

/**
 * @brief Conta as palavras em um texto e retorna um mapa com os resultados.
 * 
 * @param texto Texto a ser processado.
 * @return Map* Ponteiro para o mapa com as palavras e contagens. Deve ser liberado pelo chamador.
 */
Map* contarPalavras(const wchar_t* texto);

/**
 * @brief Converte um mapa em uma string formatada.
 * 
 * @param mapa Ponteiro para o mapa a ser convertido.
 * @return char* String formatada contendo as palavras e suas contagens.
 * A memória retornada deve ser liberada pelo chamador.
 */
char* mapParaString(Map* mapa);

/**
 * @brief Função de comparação para ordenação de palavras.
 * 
 * @param a Ponteiro para o primeiro elemento a ser comparado.
 * @param b Ponteiro para o segundo elemento a ser comparado.
 * @return int Resultado da comparação (negativo, zero ou positivo).
 */
int compararPalavras(const void* a, const void* b);

/**
 * @brief Ordena as palavras no mapa em ordem alfabética.
 * 
 * @param mapa Ponteiro para o mapa a ser ordenado.
 */
void ordenarMapa(Map* mapa);

/**
 * @brief Retorna a ordem de um caractere considerando acentos.
 * 
 * @param c Caractere a ser avaliado.
 * @return int Ordem do caractere.
 */
int ordemAcento(wchar_t c);

/**
 * @brief Converte um caractere para minúsculo.
 * 
 * @param c Caractere a ser convertido.
 * @return char Caractere convertido para minúsculo.
 */
char converteMinusculo(char c);

#ifdef __cplusplus
}
#endif

#endif  // CONTA_PALAVRA_H_
