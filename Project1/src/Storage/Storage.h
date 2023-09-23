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

private:
    std::vector<Block> blocks;
    std::unordered_set<int> availableBlocks;
    std::unordered_set<int> filledBlocks;
    const int diskCapacity = 500*1024*1024;
    int currentNumOfRecords;
};

#endif //PROJECT1_STORAGE_H
