#include "Storage.h"
#include <iostream>

// constructor of the Disk to initialise it
Storage::Storage():numOfRecords(0){
    // resize the array of blocks to max no of blocks that can fit in
    blocks.resize(diskCapacity/blockSize);
    availableBlocks.clear();
    filledBlocks.clear();

    for (int i = 0; i < blocks.size(); i++) {
        blocks[i] = Block(blockSize);
        availableBlocks.insert(i);
    }
}

Address Storage::writeRecordToStorage(const Record& record) {
    numOfRecords++;
    int blockPtr = getFirstAvailableBlockId();
    Address addressOfRecord = insertRecordIntoBlock(blockPtr, record);
    return addressOfRecord;
}

int Storage::getNumOfRecords() const {
    return numOfRecords;
}

int Storage::getNumOfBlocksUsed() const {
    return filledBlocks.size();
}

// get the record stored at the address
Record Storage::getRecord(const Address& add) const {
    Block block = getBlock(add.getBlockID());
    return block.getRecord(add.getOffset());
}

int Storage::getFirstAvailableBlockId() {
    if (availableBlocks.empty()) {
        return -1;
    }
    return *(availableBlocks.begin());
}

Address Storage::insertRecordIntoBlock(int blockPtr, const Record& rec) {
    if (blockPtr == -1) {
        // Handle the case where no available block is found (similar to returning null)
        return Address(-1, -1); // Assuming Address constructor takes block ID and offset
    }

    // Assuming blocks is a vector<Block>
    int offset = blocks[blockPtr].addRecordInBlock(rec);
    filledBlocks.insert(blockPtr);

    // Remove the block from availableBlocks if it's no longer available
    if (!blocks[blockPtr].isFull()) {
        availableBlocks.erase(blockPtr);
    }

    return Address(blockPtr, offset);
}


// dk how to retrieve the block from the disk
Block Storage::getBlock(int blockNumber) {

    if (block == nullptr && blockNumber >= 0) {
        block = blocks[blockNumber];
        blockAccesses++;

    }
    return block;
}