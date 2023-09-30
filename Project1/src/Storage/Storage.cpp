#include "Storage.h"
#include <vector>
#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

Storage::Storage() {
    currentNumOfRecords = 0;
    int blockSize = 400; // reference to maxCapacity in Block
    int numOfBlocks = diskCapacity/blockSize;
    blocks.resize(numOfBlocks);
    availableBlocks.clear();
    filledBlocks.clear();

    for (int i = 0; i < numOfBlocks; i++) {
        blocks[i] = Block();
        availableBlocks.push_back(i);
    }
}

int Storage::getFirstAvailableBlockId() {
    if (availableBlocks.empty()) {
        return -1;
    }
    return *(availableBlocks.begin());
}

Address Storage::insertRecordIntoBlock(int blockPtr, const Record& rec) {
    if (blockPtr == -1) {
        // throw error
    }

    int offset = blocks[blockPtr].addRecord(rec);

    if (blocks[blockPtr].isFull()) {
        availableBlocks.erase(availableBlocks.begin());
        filledBlocks.push_back(blockPtr);
    }

    return Address(blockPtr, offset);
}

Address Storage::writeRecordToStorage(const Record& record) {
    currentNumOfRecords++;
    int blockPtr = getFirstAvailableBlockId();
    Address addressOfRecord = insertRecordIntoBlock(blockPtr, record);
    return addressOfRecord;
}

int Storage::getCurrentNumOfRecords() const {
    return currentNumOfRecords;
}

int Storage::getNumOfFullBlocks() const {
    return filledBlocks.size();
}

Block Storage::getBlock(int blockPtr) const {
    if (blockPtr == -1) {
        // throw error
    }
    Block block = blocks[blockPtr];
    return block;
}

Record Storage::getRecord(const Address& add) const {
    int blockId = add.getBlockID();
    int offset = add.getOffset();
    Block block = getBlock(blockId);
    return block.getRecord(offset);
}

// Todo: take in a list of address and generate this count.
int Storage::getDataBlockAccessCount(vector<Address*> addresses) const {
    unordered_set<int> blockAccessed;
    int len = addresses.size();
    for (int i = 0; i < len; i++) {
        int blockId = addresses[i]->getBlockID();
        blockAccessed.insert(blockId);
    };
    int numOfBlockAccessed = blockAccessed.size();
    return numOfBlockAccessed;
}

double Storage::getAverageOfFg3PctHome(vector<Address*> addresses) const {
    auto startTime = high_resolution_clock::now();
    std::sort(addresses.begin(), addresses.end());
    double total;
    int len = addresses.size();

    for (int i = 0; i < len; i++) {
        Record r = getRecord(*addresses[i]);
        double fg3PctHome = r.getFgPctHome();
        total = total + fg3PctHome;
    }

    auto endTime = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(endTime - startTime);
    cout << "Total duration for getAverageOfFg3PctHome: " << duration.count() << " milliseconds" << endl;

    double average = total/len;
    return average;
}

int Storage::getNumOfBlocksSearchQuery(double FG_PCT_home) const {
    return runBruteForceSearchQuery(FG_PCT_home);
}

// pass in the value FG_PCT_home=0.5
int Storage::runBruteForceSearchQuery(double FG_PCT_home) const {
    double FG_PCT_home_value;
    int countDataBlockAccess = 0;
    vector<Record> resultOfSearchQuery;     // store all records where FG_PCT_home=0.5

    // iterate through all the filled blocks
    // count countDataBlockAccess
    // for each filled block, want to get the block and get current size of the block (cur num of records stored in the block)

    // loop through these records, for these records check FG_PCT_home value
    // if they match, push the record into resultOfSearchQuery vector

    // Measure the start time
    auto startTime = high_resolution_clock::now();

    for(int blockPtr : filledBlocks){
        countDataBlockAccess++;
        Block block = getBlock(blockPtr);
        int curNumOfRecordsInBlock = block.getCurrentNumOfRecords();

        for (int i=0; i<curNumOfRecordsInBlock; i++){
            Record rec = block.getRecord(i);
            FG_PCT_home_value = rec.getFgPctHome();
            if(FG_PCT_home_value == FG_PCT_home){
                resultOfSearchQuery.push_back(rec);
            }
        }
    }

    // Measure the end time
    auto endTime = high_resolution_clock::now();

    // Running time of the brute-force linear scan method
    auto duration = duration_cast<milliseconds>(endTime - startTime);

    cout << "Running time of the brute-force linear scan method for Search Query: " << duration.count() << " milliseconds" << endl;

    if(resultOfSearchQuery.empty()){
        cout << "Movies with the FG_PCT_home equal to 0.5 not found in database" << endl;
    }

    for (const Record& rec : resultOfSearchQuery){
        cout << "Found records where FG_PCT_home equal to 0.5 (brute force scan): [" << rec.toString() << "]" << endl;
    }

    return countDataBlockAccess;
}

int Storage::getNumOfBlocksRangeQuery(double FG_PCT_home_lower, double FG_PCT_home_higher) const {
    return runBruteForceRangeQuery(FG_PCT_home_lower, FG_PCT_home_higher);
}

// pass in the range for FG_PCT_home=0.6 to FG_PCT_home=1
int Storage::runBruteForceRangeQuery(double FG_PCT_home_lower_val, double FG_PCT_home_upper_val) const {
    double FG_PCT_home_value;
    int countDataBlockAccess = 0;
    vector<Record> resultOfSearchQuery;     // store all records where FG_PCT_home=0.5

    // iterate through all the filled blocks
    // count countDataBlockAccess
    // for each filled block, want to get the block and get current size of the block (cur num of records stored in the block)

    // loop through these records, for these records check FG_PCT_home value
    // if they fit in the range, push the record into resultOfSearchQuery vector

    auto startTiming = high_resolution_clock::now();

    for(int blockPtr : filledBlocks){
        countDataBlockAccess++;
        Block block = getBlock(blockPtr);

        int curNumOfRecordsInBlock = block.getCurrentNumOfRecords();
        for (int i=0; i<curNumOfRecordsInBlock; i++){
            Record rec = block.getRecord(i);
            FG_PCT_home_value = rec.getFgPctHome();
            if(FG_PCT_home_value >= FG_PCT_home_lower_val && FG_PCT_home_value <= FG_PCT_home_upper_val){
                resultOfSearchQuery.push_back(rec);
            }
        }
    }

    auto endTiming = high_resolution_clock::now();

    // Running time of the brute-force linear scan method
    auto durationTime = duration_cast<milliseconds>(endTiming - startTiming);

    cout << "Running time of the brute-force linear scan method for Range Query: " << durationTime.count() << " milliseconds" << endl;

    if(resultOfSearchQuery.empty()){
        cout << "Movies with the FG_PCT_home equal to 0.5 not found in database" << endl;
    }

    for (const Record& rec : resultOfSearchQuery){
        cout << "Found records where FG_PCT_home equal to 0.5 (brute force scan): [" << rec.toString() << "]" << endl;
    }

    return countDataBlockAccess;
}