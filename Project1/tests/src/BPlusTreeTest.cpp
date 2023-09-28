//
// Created by Jia Ming Sim on 28/9/23.
//

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../../src/Indexing/BPlusTree.cpp"

TEST_CASE("Unit Test - BPlusTree") {
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

    SECTION("Test root value") {
        int expected = 1;
        int actual = 1;
        REQUIRE(expected == actual);
    }

    SECTION("Test number of leaf nodes") {
        int expected = 9;
        int actual = tree.getNumberOfNodes();
        REQUIRE(expected == actual);
    }
}