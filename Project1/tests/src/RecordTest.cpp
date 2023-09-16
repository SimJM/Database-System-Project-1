//
// Created by Jia Ming Sim on 17/9/23.
//
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../../src/Storage/Record.h"

TEST_CASE("Record Size should be 80 bytes"){
    Record testRecord("17/09/2023", 1234567890, 123, 0.500, 0.900, 0.450, 23, 45, 1);
    REQUIRE(testRecord.getSize() == 80);
}

