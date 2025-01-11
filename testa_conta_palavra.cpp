// Copyright 2024 Henrique Givisiez dos Santos
#define CATCH_CONFIG_MAIN'
#include "./catch.hpp"
#include "./conta_palavra.h"
#include <stdio.h>

TEST_CASE("Conta palavra", "[single-file]" ) {
    REQUIRE(ContaPalavra("./arquivos teste/teste1.txt") == "é,1,Este,1,o,1,que,1,será,1,texto,2,utilizado,1");
}
