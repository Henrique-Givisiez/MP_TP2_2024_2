// Copyright 2024 Henrique Givisiez dos Santos
#define CATCH_CONFIG_MAIN'
#include "./catch.hpp"
#include "./conta_palavra.h"
#include <stdio.h>

TEST_CASE("Conta palavra", "[single-file]" ) {
    REQUIRE(ContaPalavra("./arquivos teste/teste1.txt") == "Este,2,é,1,o,1,texto,2,que,1,será,1,utilizado,1");
}
