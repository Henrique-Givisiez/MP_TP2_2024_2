// Copyright 2024 Henrique Givisiez dos Santos
#define CATCH_CONFIG_MAIN
#include "./catch.hpp"
#include "./conta_palavra.h"
#include <stdio.h>

TEST_CASE("Conta palavra", "[single-file]") {
    char* teste1 = ContaPalavra("./arquivos teste/teste1.txt");

    std::string result(teste1);
    free(teste1);

    // Compare com std::string literal
    REQUIRE(result == "é,1,Este,1,o,1,que,1,será,1,texto,2,utilizado,1");
}
