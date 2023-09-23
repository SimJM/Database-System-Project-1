#include <iostream>
#include "Storage/Record.h"
#include "Storage/Parser.h"
#include "Storage/Storage.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    Parser parser;

    Storage storage;
    std::vector<Record> records = parser.parse("../assets/games.txt");

    for(const Record& record : records) {
        std::cout << "Record size: " + std::to_string(record.getSize()) << std::endl;
        storage.writeRecordToStorage(record);
    }
    int noOfFullBlocks = storage.getNumOfFullBlocks();
    std::cout << "Done writing record to Storage: " + std::to_string(noOfFullBlocks) << std::endl;
    return 0;
}
