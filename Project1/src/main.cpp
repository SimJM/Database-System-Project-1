#include <iostream>
#include "main.h"
#include "Storage/Record.h"
#include "Storage/Parser.h"
#include "Storage/Storage.h"
#include "Indexing/BPlusTree.h"

using namespace std;

int main()
{
    print("Database System Principles - Group 48");
    print();

    Parser parser;
    Storage storage;
    BPlusTree bPlusTree;

    vector<Record> records = parser.parse("../assets/games.txt");
    print();

    vector<Address> addresses;

    for (const Record &record : records)
    {
        Address addr = storage.writeRecordToStorage(record);
        addresses.push_back(addr);
    }

    experiment1(records, storage);

    experiment2(storage, bPlusTree, addresses);

    experiment3(storage, bPlusTree);

    experiment4(storage, bPlusTree);

    bool isBruteForce = true;
    experiment5(storage, bPlusTree, isBruteForce);

    return 0;
}

void experiment1(vector<Record> records, Storage storage)
{
    print("Experiment 1");
    // Part 1
    print("Number of records: " + to_string(records.size()));

    // Part 2
    print("Record size: " + to_string(records[0].getSize()));

    // Part 3
    int noOfRecordsPerBlock = storage.getBlock(0).getSize() / records[0].getSize();
    print("Number of records in a block: " + to_string(noOfRecordsPerBlock));

    // Part 4
    int noOfFullBlocks = storage.getNumOfFullBlocks();
    print("Number of blocks in Storage: " + to_string(noOfFullBlocks));

    print();
}

void experiment2(Storage storage, BPlusTree bPlusTree, vector<Address> addresses)
{
    print("Experiment 2");

    int noOfAddresses = addresses.size();
    for (int i = 0; i < noOfAddresses; i++)
    {
        Record rec = storage.getRecord(addresses[i]);
        float fgPctHome = rec.getFgPctHome();
        Address *addrPointer = const_cast<Address *>(&addresses[i]);
        bPlusTree.insert(fgPctHome, addrPointer);
    }

    // Part 1
    print("n value: " + to_string(22));

    // Part 2
    print("Number of nodes in B+ tree: " + to_string(bPlusTree.getNumberOfNodes()));

    // Part 3
    print("Number of levels in B+ tree: " + to_string(bPlusTree.getNumberOfLevels()));

    // Part 4
    bPlusTree.getRootValue(); // prints the content of root

    print();
}

void experiment3(Storage storage, BPlusTree bPlusTree) {
    print("Experiment 3");

    int rangeIndexNodesAccessed = 0;
    vector<Address *> listOfAddresses3 = bPlusTree.retrieveRange(0.5, 0.5, rangeIndexNodesAccessed);

    // Part 1
    print("Number of index nodes the process accesses: " + to_string(bPlusTree.getNumOfIndexNodeAccessed(0.5, 0.5)));

    // Part 2
    print("Number of data blocks the process accesses: " + to_string(storage.getDataBlockAccessCount(listOfAddresses3)));

    // Part 3
    print("Average of “FG3_PCT_home” of the records that are returned: " + to_string(storage.getAverageOfFg3PctHome(listOfAddresses3)));

    // Part 4
    long long timeTakenForRetrieval = bPlusTree.timeTakenToRetrieveRecords(0.5, 0.5, rangeIndexNodesAccessed) + storage.timeTakenToRetrieveRecords(listOfAddresses3);
    print("Running time of the retrieval process: " + to_string(timeTakenForRetrieval) + " nanoseconds");

    // Part 5
    int noOfDataBlocksAccessed3 = storage.runBruteForceSearchQuery(0.5); // prints the running time of this process
    print("Number of data blocks that would be accessed by a brute-force linear scan method: " + to_string(noOfDataBlocksAccessed3));

    print();
}

void experiment4(Storage storage, BPlusTree bPlusTree) {
    print("Experiment 4");

    int rangeIndexNodesAccessed = 0;
    vector<Address *> listOfAddresses4 = bPlusTree.retrieveRange(0.6, 1.0, rangeIndexNodesAccessed);

    // Part 1
    print("Number of index nodes the process accesses: " + to_string(bPlusTree.getNumOfIndexNodeAccessed(0.6, 1.0)));

    // Part 2
    print("Number of data blocks the process accesses: " + to_string(storage.getDataBlockAccessCount(listOfAddresses4)));

    // Part 3
    print("Average of “FG3_PCT_home” of the records that are returned: " + to_string(storage.getAverageOfFg3PctHome(listOfAddresses4)));

    // Part 4
    long long timeTakenForRetrieval = bPlusTree.timeTakenToRetrieveRecords(0.6, 1.0, rangeIndexNodesAccessed)
                                      + storage.timeTakenToRetrieveRecords(listOfAddresses4);
    print("Running time of the retrieval process: " + to_string(timeTakenForRetrieval) + " nanoseconds");

    // Part 5
    int noOfDataBlocksAccessed4 = storage.runBruteForceRangeQuery(0.6, 1.0); // prints the running time of this process
    print("Number of data blocks that would be accessed by a brute-force linear scan method: " + to_string(noOfDataBlocksAccessed4));

    print();
}

void experiment5(Storage storage, BPlusTree bPlusTree, bool isBruteForce) {
    print("Experiment 5");
    int rangeIndexNodesAccessed = 0;
    vector<Address *> listOfAddresses5 = bPlusTree.retrieveRange(0, 0.35, rangeIndexNodesAccessed);

    // Part 4 + 5
    bPlusTree.removeLessThanOrEqual(0.35); // prints the running time of this process

    // Part 1
    print("Number of nodes of the updated B+ tree: " + to_string(bPlusTree.getNumberOfNodes()));

    // Part 2
    print("Number of levels of the updated B+ tree: " + to_string(bPlusTree.getNumberOfLevels()));

    // Part 3
    bPlusTree.getRootValue(); // prints the content of root

    if (!isBruteForce) {
        // Part 4
        storage.deleteRecord(listOfAddresses5); // prints the running time of this process
    } else {
        // Part 5
        int noOfDataBlocksAccessed5 = storage.runBruteForceRangeDelete(0, 0.35); // prints the running time of this process
        print("Number of data blocks that would be accessed by a brute-force linear scan method: " + to_string(noOfDataBlocksAccessed5));
    }
}

void print()
{
    cout << "" << endl;
}

void print(string str)
{
    cout << str << endl;
}




