//
// Created by Jia Ming Sim on 22/9/23.
//
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../../src/Storage/Record.h"
#include "../../src/Storage/Parser.h"

TEST_CASE("Unit Test - Parser"){
    Parser parser;
    SECTION("Test parsing games1.txt") {
        std::vector<Record> records = parser.parse("../assets/games1.txt");
        REQUIRE(records.size() == 12);
    }

    SECTION("Test parsing games.txt") {
        std::vector<Record> records = parser.parse("../assets/games.txt");
        REQUIRE(records.size() == 26651);
    }

    SECTION("Negative test: Failed to open input file") {
        std::vector<Record> records = parser.parse("../assets/hello.txt");
        REQUIRE(records.size() == 0);
    }
}