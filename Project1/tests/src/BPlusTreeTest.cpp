//
// Created by Jia Ming Sim on 28/9/23.
//

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../../src/Indexing/BPlusTree.cpp"

TEST_CASE("Unit Test 1 - BPlusTree") {
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
    } else {
        std::cout << "Key " << keyToSearch << " not found." << std::endl;
    }
    tree.printTree();


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

TEST_CASE("Unit Test 2 - BPlusTree") {
    BPlusTree tree;
    //sample records
    std::string record1 = "Record for 20.0";
    std::string record2 = "Record for 15.0";
    std::string record3 = "Record for 25.0";
    std::string record4 = "Record for 12.0";
    std::string record5 = "Record for 11.0";
    std::string record6 = "Record for 12.0";
    std::string record7 = "Record for 6.0";
    std::string record8 = "Record for 19.0";
    std::string record9 = "Record for 26.0";
    std::string record10 = "Record for 27.0";
    std::string record11 = "Record for 11.5";
    std::string record12 = "Record for 19.5";
    std::string record13 = "Record for 28.0";
    std::string record14 = "Record for 12.0";
    std::string record15 = "Record for 12.0";

    tree.insert(20.0, &record1);
    tree.insert(15.0, &record2);
    tree.insert(25.0, &record3);
    tree.insert(12.0, &record4);
    tree.insert(11.0, &record5);
    tree.insert(12.0, &record6);
    tree.insert(6.0, &record7);
    tree.insert(19.0, &record8);
    tree.insert(26.0, &record9);
    tree.insert(27.0, &record10);
    tree.insert(11.5, &record11);
    tree.insert(19.5, &record12);
    tree.insert(28.0, &record13);
    tree.insert(12.0, &record14);
    tree.insert(12.0, &record15);


    tree.getRootValue();
    std::cout << "Number of Levels: " << tree.getNumberOfLevels() << std::endl;
    std::cout << "Number of Nodes: " << tree.getNumberOfNodes() << std::endl;

    tree.printTree();
    float keyToSearch = 19.5; //1st instance of key
    bool found = tree.search(keyToSearch);
    if (found) {
        std::cout << "Key " << keyToSearch << " found!" << std::endl;
        std::cout << "Index nodes accessed(To get 1st instance of key): " << tree.getIndexNodeAccessCount() << std::endl;
    }
    else{
        std::cout << "Key " << keyToSearch << " not found." << std::endl;
    }

    int rangeindexNodesAccessed;
    std::vector<void*> retrievedRecords;
    auto start = std::chrono::high_resolution_clock::now();//start timer
    retrievedRecords = tree.retrieveRange(12.0, 12.0, rangeindexNodesAccessed);
    auto end = std::chrono::high_resolution_clock::now(); // end timer
    std::chrono::duration<double> duration = end - start; //difference

    std::cout << "Time taken by function: " << duration.count() << " seconds" << std::endl; //print out time

    for(void* recordAddress : retrievedRecords) {
        std::string* actualRecord = reinterpret_cast<std::string*>(recordAddress);
        std::cout << "Retrieved Record: " << *actualRecord << std::endl;
    }
    std::cout << "Index nodes accessed: " << rangeindexNodesAccessed << std::endl;
}

TEST_CASE("Unit Test 3 - BPlusTree removing duplicate") {
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
    tree.remove(12.0);
    //tree.remove(6.0);
    //tree.remove(11.0);
    //tree.remove(10.5);
    //tree.remove(11.5);
    //tree.remove(15.0);

    std::cout<<"after removal" <<std::endl;
    tree.printTree();

}

TEST_CASE("Unit Test 4 - BPlusTree Larger Tree and multiple removal") {
    BPlusTree tree;

    // Insert key-value pairs into the B+ tree
    tree.insert(1.5, nullptr);
    tree.insert(2.3, nullptr);
    tree.insert(3.7, nullptr);
    tree.insert(4.9, nullptr);
    tree.insert(7.4, nullptr);
    tree.insert(8.6, nullptr);
    tree.insert(9.1, nullptr);
    tree.insert(13.2, nullptr);
    tree.insert(14.8, nullptr);
    tree.insert(16.3, nullptr);
    tree.insert(17.4, nullptr);
    tree.insert(18.7, nullptr);
    tree.insert(21.9, nullptr);
    tree.insert(22.5, nullptr);
    tree.insert(23.3, nullptr);
    tree.insert(24.2, nullptr);
    tree.insert(29.6, nullptr);
    tree.insert(30.1, nullptr);
    tree.insert(31.3, nullptr);
    tree.insert(32.5, nullptr);
    tree.insert(33.9, nullptr);
    tree.insert(34.0, nullptr);
    tree.insert(35.4, nullptr);
    tree.insert(36.7, nullptr);
    tree.insert(37.8, nullptr);
    tree.insert(38.2, nullptr);
    tree.insert(39.3, nullptr);
    tree.insert(40.5, nullptr);
    tree.insert(41.6, nullptr);
    tree.insert(42.9, nullptr);
    tree.insert(43.0, nullptr);
    tree.insert(44.1, nullptr);
    tree.insert(45.3, nullptr);
    tree.insert(46.5, nullptr);
    tree.insert(47.7, nullptr);
    tree.insert(48.8, nullptr);
    tree.insert(49.0, nullptr);
    tree.insert(50.3, nullptr);
    tree.insert(51.5, nullptr);
    tree.insert(52.9, nullptr);
    tree.insert(53.1, nullptr);
    tree.insert(54.4, nullptr);
    tree.insert(55.6, nullptr);
    tree.insert(56.2, nullptr);
    tree.insert(57.8, nullptr);
    tree.insert(58.9, nullptr);
    tree.insert(59.0, nullptr);
    tree.insert(60.1, nullptr);
    tree.insert(61.3, nullptr);
    tree.insert(62.4, nullptr);

    tree.getRootValue();
    std::cout << "Number of Levels: " << tree.getNumberOfLevels() << std::endl;
    std::cout << "Number of Nodes: " << tree.getNumberOfNodes() << std::endl;

    tree.printTree();
    tree.remove(1.5);
    tree.remove(2.3);
    tree.remove(3.7);
    tree.remove(4.9);
    tree.remove(7.4);
    tree.remove(8.6);
    tree.remove(9.1);
    tree.remove(13.2);
    tree.remove(14.8);
    tree.remove(16.3);
    tree.remove(17.4);
    tree.remove(18.7);
    tree.remove(21.9);
    tree.remove(22.5);
    tree.remove(23.3);
    tree.remove(24.2);
    tree.remove(29.6);
    tree.remove(30.1);
    tree.remove(31.3);
    tree.remove(32.5);


    std::cout<<"after removal" <<std::endl;
    tree.printTree();
    tree.getRootValue();
    std::cout << "Number of Levels: " << tree.getNumberOfLevels() << std::endl;
    std::cout << "Number of Nodes: " << tree.getNumberOfNodes() << std::endl;

}


/*
TEST_CASE("Unit Test 5 - BPlusTree removing range") { //Something seems wrong with the function not the
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
    tree.removeRange(6.0, 15.0);
    std::cout<<"after removal 6 to 15 inclusive" <<std::endl;
    tree.printTree();
}*/
