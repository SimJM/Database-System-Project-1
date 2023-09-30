#ifndef PROJECT1_STORAGE_H
#define PROJECT1_STORAGE_H

#include <unordered_set>
#include "Block.h"
#include "Record.h"
#include "Address.h"

class Storage {
public:
    Storage();

    int getFirstAvailableBlockId();
    Address insertRecordIntoBlock(int blockPtr, const Record& rec);//kiv
    Address writeRecordToStorage(const Record& rec);
    int getCurrentNumOfRecords() const;
    int getNumOfFullBlocks() const;
    Block getBlock(int blockPtr) const;
    Record getRecord(const Address& add) const;
    int getDataBlockAccessCount();
    int getNumOfBlocksSearchQuery(double FG_PCT_home) const;
    int runBruteForceSearchQuery(double FG_PCT_home) const;
    int getNumOfBlocksRangeQuery(double FG_PCT_home_lower, double FG_PCT_home_higher) const;
    int runBruteForceRangeQuery(double FG_PCT_home_lower_val, double FG_PCT_home_upper_val) const;

private:
    std::vector<Block> blocks;
    std::vector<int> availableBlocks;
    std::vector<int> filledBlocks;
    const int diskCapacity = 500*1024*1024;
    int currentNumOfRecords;
};

#endif //PROJECT1_STORAGE_H
