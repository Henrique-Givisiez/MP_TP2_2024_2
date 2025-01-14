// Copyright 2024 Henrique Givisiez dos Santos

/**
 * @file teste_conta_palavra.cpp
 * @brief Arquivo de teste para a função `ContaPalavra`.
 *
 * Este arquivo utiliza a biblioteca Catch2 para realizar testes unitários
 * da função `ContaPalavra`, verificando sua capacidade de contar palavras
 * em arquivos de texto e retornar resultados formatados.
 */

#define CATCH_CONFIG_MAIN ///< Define o ponto de entrada principal para os testes Catch2.
#include <string>
#include "./catch.hpp"
#include "./conta_palavra.h"

/**
 * @brief Testes para a função `ContaPalavra`.
 *
 * Cada teste verifica se a função `ContaPalavra` processa corretamente um arquivo
 * de entrada e retorna o resultado esperado no formato de string.
 */
TEST_CASE("Conta palavra", "[single-file]") {
    /**
     * @test Caso de teste 1
     * @brief Verifica o processamento de um arquivo simples (`teste1.txt`).
     */
    char* teste1 = ContaPalavra("./arquivos teste/teste1.txt");
    std::string result1(teste1);
    free(teste1);
    REQUIRE(result1 == "é,1,Este,1,o,1,que,1,será,1,texto,2,utilizado,1");

    /**
     * @test Caso de teste 2
     * @brief Verifica o processamento de um arquivo simples (`teste2.txt`).
     */
    char* teste2 = ContaPalavra("./arquivos teste/teste2.txt");
    std::string result2(teste2);
    free(teste2);
    REQUIRE(result2 == "é,1,Este,1,o,1,que,1,será,1,texto,2,utilizado,1");

    /**
     * @test Caso de teste 3
     * @brief Verifica o processamento de um arquivo com múltiplas palavras repetidas (`teste3.txt`).
     */
    char* teste3 = ContaPalavra("./arquivos teste/teste3.txt");
    std::string result3(teste3);
    free(teste3);
    REQUIRE(result3 == "arquivo,2,belo,2,olha,2,que,2");

    /**
     * @test Caso de teste 4
     * @brief Verifica a diferenciação entre palavras em maiúsculas e minúsculas (`teste4.txt`).
     */
    char* teste4 = ContaPalavra("./arquivos teste/teste4.txt");
    std::string result4(teste4);
    free(teste4);
    REQUIRE(result4 == "a,3,A,1,e,1,E,1");

    /**
     * @test Caso de teste 5
     * @brief Verifica o processamento de um arquivo com grande repetição de palavras (`teste5.txt`).
     */
    char* teste5 = ContaPalavra("./arquivos teste/teste5.txt");
    std::string result5(teste5);
    free(teste5);
    REQUIRE(result5 == "a,24,b,24,c,24,d,24");

    /**
     * @test Caso de teste 6
     * @brief Verifica o processamento de um arquivo com acentos em palavras (`teste6.txt`).
     */
    char* teste6 = ContaPalavra("./arquivos teste/teste6.txt");
    std::string result6(teste6);
    free(teste6);
    REQUIRE(result6 == "á,2,a,2,A,1,é,2,e,1,E,1");

    /**
     * @test Caso de teste 7
     * @brief Verifica o processamento de um arquivo com palavras similares (`teste7.txt`).
     */
    char* teste7 = ContaPalavra("./arquivos teste/teste7.txt");
    std::string result7(teste7);
    free(teste7);
    REQUIRE(result7 == "arquivo,3,belo,2,é,2,este,1,Este,1,sim,2,um,1");

    /**
     * @test Caso de teste 8
     * @brief Verifica o processamento de um arquivo com palavras variadas e repetição (`teste8.txt`).
     */
    char* teste8 = ContaPalavra("./arquivos teste/teste8.txt");
    std::string result8(teste8);
    free(teste8);
    REQUIRE(result8 == "belo,1,com,1,é,2,É,1,este,2,Este,2,teste,1,texto,2,um,1");

    /**
     * @test Caso de teste 9
     * @brief Verifica o processamento de palavras relacionadas a árvores (`teste9.txt`).
     */
    char* teste9 = ContaPalavra("./arquivos teste/teste9.txt");
    std::string result9(teste9);
    free(teste9);
    REQUIRE(result9 == "árvore,2,Árvores,1,arvore,2,Arvore,1");

    /**
     * @test Caso de teste 10
     * @brief Verifica o processamento de um trava-língua (`teste10.txt`).
     */
    char* teste10 = ContaPalavra("./arquivos teste/teste10.txt");
    std::string result10(teste10);
    free(teste10);
    REQUIRE(result10 == "de,2,para,2,pratos,2,tigres,2,três,2,trigo,2,tristes,2,Três,2");
}
