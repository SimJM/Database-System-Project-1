//
// Created by Jia Ming Sim on 17/9/23.
//
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../../src/Storage/Record.h"

TEST_CASE("Unit Test - Record")
{
    SECTION("Record Size should be 80 bytes")
    {
        Record testRecord("17/09/2023", 1234567890, 123, 0.500, 0.900, 0.450, 23, 45, 1);
        REQUIRE(testRecord.getSize() == 56);
    }

    SECTION("Record toString")
    {
        Record testRecord("17/09/2023", 1234567890, 123, 0.500, 0.900, 0.450, 23, 45, 1);
        std::string expected = "GAME_DATE_EST: 17/09/2023\nTEAM_ID_home: 1234567890\nPTS_home: 123\nFG_PCT_home: 0.500000\nFT_PCT_home: 0.900000\nFG3_PCT_home: 0.450000\nAST_home: 23\nREB_home: 45\nHOME_TEAM_WINS: true\n";
        REQUIRE(testRecord.toString() == expected);
    }
}
