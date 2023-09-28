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

    for(const Record& record : records) {
        std::cout << "Record size: " + std::to_string(record.getSize()) << std::endl;
        storage.writeRecordToStorage(record);
    }
    int noOfFullBlocks = storage.getNumOfFullBlocks();
    std::cout << "Done writing record to Storage: " + std::to_string(noOfFullBlocks) << std::endl;
    BPlusTree tree;

    // Insert key-value pairs into the B+ tree
    tree.insert(10.5, nullptr);
    tree.insert(5.0, nullptr);
    tree.insert(20.0, nullptr);
    tree.insert(15.0, nullptr);
    tree.insert(25.0, nullptr);
    tree.insert(12.0, nullptr);
    tree.insert(11.0, nullptr);
    tree.insert(12.0, nullptr);
    tree.insert(6.0, nullptr);
    tree.insert(19.0, nullptr);
    tree.insert(26.0, nullptr);
    tree.insert(27.0, nullptr);
    tree.insert(11.5, nullptr);
    tree.insert(19.5, nullptr);
    tree.insert(28.0, nullptr);

    tree.getRootValue();
    std::cout << "Number of Levels: " << tree.getNumberOfLevels() << std::endl;
    std::cout << "Number of Nodes: " << tree.getNumberOfNodes() << std::endl;

    tree.printTree();
    float keyToSearch = 19.5;
    bool found = tree.search(keyToSearch);
    if (found) {
        std::cout << "Key " << keyToSearch << " found!" << std::endl;
        std::cout << "Index nodes accessed: " << tree.getIndexNodeAccessCount() << std::endl;
        std::cout << "Data blocks accessed: " << tree.getDataBlockAccessCount() << std::endl;
    } else {
        std::cout << "Key " << keyToSearch << " not found." << std::endl;
    }

    return 0;
}
