#ifndef PROJECT1_STORAGE_H
#define PROJECT1_STORAGE_H

#include <unordered_set>
#include "Block.h"
#include "Record.h"
#include "Address.h"

using namespace std;

class Storage
{
public:
    Storage();

    Address insertRecordIntoBlock(int blockPtr, const Record &rec);
    Address writeRecordToStorage(const Record &rec);

    int getFirstAvailableBlockId();
    int getCurrentNumOfRecords() const;
    int getNumOfFullBlocks() const;

    Block getBlock(int blockPtr) const;
    Record getRecord(const Address &add) const;
    void deleteRecord(vector<Address *> addList);

    int getDataBlockAccessCount(vector<Address *> addresses) const;
    long long timeTakenToRetrieveRecords(vector<Address *> addresses) const;
    float getAverageOfFg3PctHome(vector<Address *> addresses) const;

    int runBruteForceSearchQuery(float FG_PCT_home) const;
    int runBruteForceRangeQuery(float FG_PCT_home_lower_val, float FG_PCT_home_upper_val) const;
    int runBruteForceRangeDelete(float FG_PCT_home_lower_val, float FG_PCT_home_upper_val) const;

    bool containsFilledBlock(int blockId) const;
    int removeFilledBlock(int blockId);
    int addAvailableBlock(int blockId);

private:
    const int DISK_CAPACITY = 500 * 1024 * 1024;
    vector<Block> blocks;
    vector<int> availableBlocks;
    vector<int> filledBlocks;
    int currentNumOfRecords;
};

#endif // PROJECT1_STORAGE_H
