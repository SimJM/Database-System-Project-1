//
// Created by Esther Teo on 24/9/23.
//
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../../src/Storage/Storage.h"

TEST_CASE("Unit Test - Storage")
{
    // check everything is 0 at initialisation
    SECTION("Storage Initialisation")
    {
        Storage testStorage;
        int numOfBlocks = testStorage.getNumOfFullBlocks();
        REQUIRE(numOfBlocks == 0);
        REQUIRE(testStorage.getCurrentNumOfRecords() == 0);
    }

    SECTION("Inserting Records")
    {
        Storage testStorage;
        Record testRecord1("17/09/2023", 1234567890, 123, 0.500, 0.900, 0.450, 23, 45, 1);
        Record testRecord2("18/09/2023", 9876543210, 456, 0.600, 0.850, 0.400, 30, 40, 0);

        Address address1 = testStorage.writeRecordToStorage(testRecord1);
        Address address2 = testStorage.writeRecordToStorage(testRecord2);

        // Check if the records were successfully inserted
        REQUIRE(address1.getBlockID() == 0);
        REQUIRE(address2.getBlockID() == 0);
    }

    SECTION("Block Status")
    {
        Storage testStorage;
        Record testRecord("17/09/2023", 1234567890, 123, 0.500, 0.900, 0.450, 23, 45, 1);

        int blockPtr = testStorage.getFirstAvailableBlockId();

        for (int i = 0; i < 7; ++i)
        {
            Address address = testStorage.insertRecordIntoBlock(blockPtr, testRecord);
            REQUIRE(address.getBlockID() == 0);
        }

        // Check if the block is marked as filled after inserting 7 records
        REQUIRE(testStorage.getNumOfFullBlocks() == 1);
        REQUIRE(testStorage.getFirstAvailableBlockId() == 1);
    }

    SECTION("Retrieve Record")
    {
        Storage testStorage;
        Record testRecord("17/09/2023", 1234567890, 123, 0.500, 0.900, 0.450, 23, 45, 1);

        Address address = testStorage.writeRecordToStorage(testRecord);

        Record retrievedRecord = testStorage.getRecord(address);
        REQUIRE(retrievedRecord == testRecord);
    }

}