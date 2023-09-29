#include <iostream>
#include "Storage/Record.h"
#include "Storage/Parser.h"
#include "Storage/Storage.h"
#include "Indexing/BPlusTree.cpp"

int main() {
    std::cout << "Hello, World!" << std::endl;

    Parser parser;

    Storage storage;
    std::vector<Record> records = parser.parse("../assets/games.txt");
    std::vector<Address> addresses;

    for(const Record& record : records) {
        Address addr = storage.writeRecordToStorage(record);
        addresses.push_back(addr);
    }
    std::cout << "" << std::endl;

    // Experiment 1
    std::cout << "Experiment 1" << std::endl;
    std::cout << "Number of records: " + std::to_string(records.size()) << std::endl;
    std::cout << "Record size: " + std::to_string(records[0].getSize()) << std::endl;
    int noOfRecordsPerBlock = storage.getBlock(0).getSize()/records[0].getSize();
    std::cout << "Number of records in a block: " + std::to_string(noOfRecordsPerBlock) << std::endl;
    int noOfFullBlocks = storage.getNumOfFullBlocks();
    std::cout << "Number of blocks in Storage: " + std::to_string(noOfFullBlocks) << std::endl;
    std::cout << "" << std::endl;

    // Experiment 2
    std::cout << "Experiment 2" << std::endl;
    BPlusTree bPlusTree;
    for(const Address addr : addresses) {
        Record rec = storage.getRecord(addr);
        double fgPctHome = rec.getFgPctHome();
        Address* addrPointer = const_cast<Address *>(&addr);
        bPlusTree.insert(fgPctHome, addrPointer );
    }
    std::cout << "n value: " + std::to_string(22) << std::endl;
    std::cout << "Number of nodes in B+ tree: " + std::to_string(bPlusTree.getNumberOfNodes()) << std::endl;
    std::cout << "Number of levels in B+ tree: " + std::to_string(bPlusTree.getNumberOfLevels()) << std::endl;
    bPlusTree.getRootValue();
    std::cout << "" << std::endl;

    // Experiment 3
    std::cout << "Experiment 3" << std::endl;
//Todo: indexing              std::cout << "Number of index nodes the process accesses: " + std::to_string(bPlusTree.getIndexNodeAccessCount()) << std::endl;
//Todo: storage               std::cout << "Number of data blocks the process accesses: " + std::to_string(bPlusTree.getDataBlockAccessCount()) << std::endl;
//Todo: storage               std::cout << "Average of “FG3_PCT_home” of the records that are returned: " + std::to_string(bPlusTree.getIndexNodeAccessCount()) << std::endl;
//Todo: storage + indexing    std::cout << "Running time of the retrieval process: " + std::to_string(bPlusTree.getIndexNodeAccessCount()) << std::endl;
//Todo: storage    std::cout << "Number of data blocks that would be accessed by a brute-force linear scan method: " + std::to_string(bPlusTree.getIndexNodeAccessCount()) << std::endl;
//Todo: storage    std::cout << "Running time for brute-force: " + std::to_string(bPlusTree.getIndexNodeAccessCount()) << std::endl;
    std::cout << "" << std::endl;

// Experiment 4
    std::cout << "Experiment 4" << std::endl;
//Todo: indexing              std::cout << "Number of index nodes the process accesses: " + std::to_string(bPlusTree.getIndexNodeAccessCount()) << std::endl;
//Todo: storage               std::cout << "Number of data blocks the process accesses: " + std::to_string(bPlusTree.getDataBlockAccessCount()) << std::endl;
//Todo: storage               std::cout << "Average of “FG3_PCT_home” of the records that are returned: " + std::to_string(bPlusTree.getIndexNodeAccessCount()) << std::endl;
//Todo: storage + indexing    std::cout << "Running time of the retrieval process: " + std::to_string(bPlusTree.getIndexNodeAccessCount()) << std::endl;
//Todo: storage    std::cout << "Number of data blocks that would be accessed by a brute-force linear scan method: " + std::to_string(bPlusTree.getIndexNodeAccessCount()) << std::endl;
//Todo: storage    std::cout << "Running time for brute-force: " + std::to_string(bPlusTree.getIndexNodeAccessCount()) << std::endl;

    return 0;
}
