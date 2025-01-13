// Copyright 2024 Henrique Givisiez dos Santos
#define CATCH_CONFIG_MAIN
#include "./catch.hpp"
#include "./conta_palavra.h"
#include <stdio.h>

TEST_CASE("Conta palavra", "[single-file]") {
    char* teste1 = ContaPalavra("./arquivos teste/teste1.txt");
    std::string result1(teste1);
    free(teste1);
    REQUIRE(result1 == "é,1,Este,1,o,1,que,1,será,1,texto,2,utilizado,1");

    char* teste2 = ContaPalavra("./arquivos teste/teste2.txt");
    std::string result2(teste2);
    free(teste2);
    REQUIRE(result2 == "é,1,Este,1,o,1,que,1,será,1,texto,2,utilizado,1");
   
    char* teste3 = ContaPalavra("./arquivos teste/teste3.txt");
    std::string result3(teste3);
    free(teste3);
    REQUIRE(result3 == "arquivo,2,belo,2,olha,2,que,2");

    char* teste4 = ContaPalavra("./arquivos teste/teste4.txt");
    std::string result4(teste4);
    free(teste4);
    REQUIRE(result4 == "a,3,A,1,e,1,E,1");

    char* teste5 = ContaPalavra("./arquivos teste/teste5.txt");
    std::string result5(teste5);
    free(teste5);
    REQUIRE(result5 == "a,24,b,24,c,24,d,24");
}
