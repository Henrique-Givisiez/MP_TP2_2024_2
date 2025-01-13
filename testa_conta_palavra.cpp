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
}
