//
// Created by Esther Teo on 24/9/23.
//
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../../src/Storage/Block.h"

TEST_CASE("Unit Test - Block")
{
    SECTION("Block Initialisation")
    {
        Block testBlock;
        REQUIRE(testBlock.getSize() == 0);
        REQUIRE(testBlock.getMaxCapacity() == 400);
    }

    SECTION("Block Insertion")
    {
        Block testBlock;
        Record testRecord("17/09/2023", 1234567890, 123, 0.500, 0.900, 0.450, 23, 45, 1);

        for (int i = 0; i < 7; i++)
        {
            int offset = testBlock.addRecord(testRecord);
            REQUIRE(offset != -1);
        }

        REQUIRE(testBlock.isFull());
    }

    SECTION("Block Retrieval")
    {
        Block testBlock;
        Record testRecord("17/09/2023", 1234567890, 123, 0.500, 0.900, 0.450, 23, 45, 1);

        for (int i = 0; i < 5; i++)
        {
            testBlock.addRecord(testRecord);
        }

        for (int i = 0; i < 5; i++)
        {
            Record retrievedRecord = testBlock.getRecord(i);
            REQUIRE(retrievedRecord == testRecord);
        }
    }

    SECTION("Block Overflow")
    {
        Block testBlock;
        Record testRecord("17/09/2023", 1234567890, 123, 0.500, 0.900, 0.450, 23, 45, 1);

        for (int i = 0; i < 10; i++)
        {
            // inserting within block capacity of 400B
            if (i < 7)
            {
                int offset = testBlock.addRecord(testRecord);
                REQUIRE(offset != -1);
            }
            else
            {
                int offset = testBlock.addRecord(testRecord);
                REQUIRE(offset == -1);
            }
        }
    }
}