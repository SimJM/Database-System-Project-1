#include <iostream>
#include "Storage/Record.h"
#include "Storage/Parser.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    Parser parser;
    std::vector<Record> records = parser.parse("../assets/games.txt");

//    for(const Record& record : records) {
//        // disk.add(record) - add each record in to the disk
//    }

    return 0;
}
