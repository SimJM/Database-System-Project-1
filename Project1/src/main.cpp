#include <iostream>
#include "Storage/Record.h"
#include "Storage/Parser.h"
#include "Storage/Storage.h"
#include "Indexing/BPlusTree.cpp"

using namespace std;

void print(string str)
{
    cout << str << endl;
}

int main()
{
    print("Database System Principles - Group 48");
    print("");

    Parser parser;
    Storage storage;

    vector<Record> records = parser.parse("../assets/games.txt");

    vector<Address> addresses;
    for (const Record &record : records)
    {
        Address addr = storage.writeRecordToStorage(record);
        addresses.push_back(addr);
    }

    // Experiment 1
    print("Experiment 1");
    print("Number of records: " + to_string(records.size()));
    print("Record size: " + to_string(records[0].getSize()));
    int noOfRecordsPerBlock = storage.getBlock(0).getSize() / records[0].getSize();
    print("Number of records in a block: " + to_string(noOfRecordsPerBlock));
    int noOfFullBlocks = storage.getNumOfFullBlocks();
    print("Number of blocks in Storage: " + to_string(noOfFullBlocks));
    print("");

    // Experiment 2
    cout << "Experiment 2" << endl;
    BPlusTree bPlusTree;
    int noOfAddresses = addresses.size();
    for (int i = 0; i < noOfAddresses; i++)
    {
        Record rec = storage.getRecord(addresses[i]);
        double fgPctHome = rec.getFgPctHome();
        Address *addrPointer = const_cast<Address *>(&addresses[i]);
        bPlusTree.insert(fgPctHome, addrPointer);
    }
    print("n value: " + to_string(22));
    print("Number of nodes in B+ tree: " + to_string(bPlusTree.getNumberOfNodes()));
    print("Number of levels in B+ tree: " + to_string(bPlusTree.getNumberOfLevels()));
    bPlusTree.getRootValue(); // prints the content of root
    print("");

    // Experiment 3
    print("Experiment 3");
    print("Number of index nodes the process accesses: " + to_string(bPlusTree.getNumOfIndexNodeAccessed(0.5, 0.5)));
    int rangeIndexNodesAccessed = 0;
    vector<Address *> listOfAddresses = bPlusTree.retrieveRange(0.5, 0.5, rangeIndexNodesAccessed);
    print("Number of data blocks the process accesses: " + to_string(storage.getDataBlockAccessCount(listOfAddresses)));
    print("Average of “FG3_PCT_home” of the records that are returned: " + to_string(storage.getAverageOfFg3PctHome(listOfAddresses)));
    print("Running time of the retrieval process: " + to_string(bPlusTree.timeTakenToRetrieveRecords(0.5, 0.5, rangeIndexNodesAccessed) + storage.timeTakenToRetrieveRecords(listOfAddresses)) + " nanoseconds");
    print("Number of data blocks that would be accessed by a brute-force linear scan method: " + to_string(storage.runBruteForceSearchQuery(0.5)));
    print("");

    // Experiment 4
    print("Experiment 4");
    print("Number of index nodes the process accesses: " + to_string(bPlusTree.getNumOfIndexNodeAccessed(0.6, 1.0)));
    vector<Address *> listOfAddresses4 = bPlusTree.retrieveRange(0.6, 1.0, rangeIndexNodesAccessed);
    print("Number of data blocks the process accesses: " + to_string(storage.getDataBlockAccessCount(listOfAddresses4)));
    print("Average of “FG3_PCT_home” of the records that are returned: " + to_string(storage.getAverageOfFg3PctHome(listOfAddresses4)));
    long long timeTakenForRetrieval = bPlusTree.timeTakenToRetrieveRecords(0.6, 1.0, rangeIndexNodesAccessed) + storage.timeTakenToRetrieveRecords(listOfAddresses4);
    print("Running time of the retrieval process: " + to_string(timeTakenForRetrieval) + " nanoseconds");
    print("Number of data blocks that would be accessed by a brute-force linear scan method: " + to_string(storage.runBruteForceRangeQuery(0.6, 1.0)));
    print("");

    // Experiment 5
    print("Experiment 5");
    vector<Address *> listOfAddresses5 = bPlusTree.retrieveRange(0, 0.35, rangeIndexNodesAccessed);
    bPlusTree.removeLessThanOrEqual(0.35);
    print("Number of nodes of the updated B+ tree: " + to_string(bPlusTree.getNumberOfNodes()));
    print("Number of levels of the updated B+ tree: " + to_string(bPlusTree.getNumberOfLevels()));
    bPlusTree.getRootValue(); // prints the content of root
    storage.deleteRecord(listOfAddresses5);
//    print("Number of data blocks that would be accessed by a brute-force linear scan method: " + to_string(storage.runBruteForceRangeDelete(0, 0.35)));

    return 0;
}
