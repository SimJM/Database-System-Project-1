#ifndef PROJECT1_STORAGE_H
#define PROJECT1_STORAGE_H

#include <unordered_set>
#include "Block.h"
#include "Record.h"
#include "Address.h"

using namespace std;

class Storage {
public:
    Storage();

    Address insertRecordIntoBlock(int blockPtr, const Record& rec);
    Address writeRecordToStorage(const Record& rec);

    int getFirstAvailableBlockId();
    int getCurrentNumOfRecords() const;
    int getNumOfFullBlocks() const;
    Block getBlock(int blockPtr) const;
    Record getRecord(const Address& add) const;
    int getDataBlockAccessCount(vector<Address*> addresses) const;
    long long timeTakenToRetrieveRecords(vector<Address*> addresses) const;
    double getAverageOfFg3PctHome(vector<Address*> addresses) const;
    int runBruteForceSearchQuery(double FG_PCT_home) const;
    int runBruteForceRangeQuery(double FG_PCT_home_lower_val, double FG_PCT_home_upper_val) const;
    int runBruteForceRangeDelete(double FG_PCT_home_lower_val, double FG_PCT_home_upper_val) const;
    void deleteRecord(vector<Address*> addList);
    bool containsFilledBlock(int blockId) const;
    int removeFilledBlock(int blockId);
    int addAvailableBlock(int blockId);

private:
    vector<Block> blocks;
    vector<int> availableBlocks;
    vector<int> filledBlocks;
    const int diskCapacity = 500*1024*1024;
    int currentNumOfRecords;
};

#endif //PROJECT1_STORAGE_H
