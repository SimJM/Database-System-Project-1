#include <iostream>
#include "Storage/Record.h"
#include "Storage/Block.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    Record gameRecord("2023-09-14", 1234567890, 100, 0.526, 0.750, 0.333, 25, 40, true);

    // Access and print the attributes
    std::cout << "GAME_DATE_EST: " << gameRecord.GAME_DATE_EST << std::endl;
    std::cout << "TEAM_ID_home: " << gameRecord.TEAM_ID_home << std::endl;
    std::cout << "PTS_home: " << gameRecord.PTS_home << std::endl;
    std::cout << "FG_PCT_home: " << gameRecord.FG_PCT_home << std::endl;
    std::cout << "FT_PCT_home: " << gameRecord.FT_PCT_home << std::endl;
    std::cout << "FG3_PCT_home: " << gameRecord.FG3_PCT_home << std::endl;
    std::cout << "AST_home: " << gameRecord.AST_home << std::endl;
    std::cout << "REB_home: " << gameRecord.REB_home << std::endl;
    std::cout << "HOME_TEAM_WINS: " << (gameRecord.HOME_TEAM_WINS ? "Yes" : "No") << std::endl;

    // size of record
    size_t sizeOfRecord = gameRecord.getSize();
    std::cout << "Size of Record object: " << sizeOfRecord << " bytes" << std::endl;

    // Create a Block object with a maximum capacity of 400 bytes
    Block block(1);

    // Create some Record objects and add them to the Block
    Record record1("2023-09-14", 1234567890LL, 100, 0.526, 0.750, 0.333, 25, 40, true);
    Record record2("2023-09-15", 9876543210LL, 85, 0.482, 0.812, 0.289, 20, 35, false);
    Record record3("2023-09-15", 9876543210LL, 85, 0.482, 0.812, 0.289, 20, 35, false);
    Record record4("2023-09-15", 9876543210LL, 85, 0.482, 0.812, 0.289, 20, 35, false);
    Record record5("2023-09-15", 9876543210LL, 85, 0.482, 0.812, 0.289, 20, 35, false);
    Record record6("2023-09-15", 9876543210LL, 85, 0.482, 0.812, 0.289, 20, 35, false);
    Record record7("2023-09-15", 9876543210LL, 85, 0.482, 0.812, 0.289, 20, 35, false);

    block.addRecord(record1);
    block.addRecord(record2);
    block.addRecord(record3);
    block.addRecord(record4);
    block.addRecord(record5);
    block.addRecord(record6);
    block.addRecord(record7);

    // Check if the Block is full
    if (block.isFull()) {
        std::cout << "The Block is full." << std::endl;
    } else {
        std::cout << "The Block is not full." << std::endl;
    }

    std::cout << block.getSize() << std::endl;
    std::cout << block.getId() << std::endl;

    return 0;
}
