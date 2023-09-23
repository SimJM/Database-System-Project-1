#ifndef PROJECT1_STORAGE_H
#define PROJECT1_STORAGE_H

#include <unordered_set>
#include "Block.h"
#include "Record.h"
#include "Address.h"

class Storage {
public:
    Storage();

    Address writeRecordToStorage(const Record& rec);

    Address insertRecordIntoBlock(int blockPtr, const Record& rec);

    int getNumOfRecords() const;

    int getNumOfBlocksUsed() const;

    Record getRecord(const Address& add) const;

private:
    std::vector<Block> blocks;
    std::unordered_set<int> availableBlocks;
    std::unordered_set<int> filledBlocks;
    static const int diskCapacity = 500*1024*1024;
    static const int blockSize = 400;
    int numOfRecords;
};

#endif //PROJECT1_STORAGE_H
