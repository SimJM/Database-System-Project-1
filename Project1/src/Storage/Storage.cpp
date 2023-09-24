#include "Storage.h"

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
    if (blockPtr < 0) {
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