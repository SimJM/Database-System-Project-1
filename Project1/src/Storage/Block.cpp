//
// Created by Jia Ming Sim on 14/9/23.
//

#include "Block.h"

Block::Block() {
    currentNumOfRecords = 0;
    maxCapacity = 400;
    maxNumOfRecords = maxCapacity / sizeof(Record);
    records.reserve(maxNumOfRecords);
 }

Record Block::getRecord(int offset) const {
    return records[offset];
}

int Block::getCurrentNumOfRecords() const {
    return records.size();
}

int Block::getMaxNumOfRecords() const {
    return maxNumOfRecords;
};

int Block::addRecord(const Record& record) {
    if (!isFull()) {
        records.push_back(record);
        int offset = records.size() - 1;
        return offset;
    }
    return -1;
}

size_t Block::getSize() const {
    size_t size = 0;
    for (int i = 0; i < records.size(); i++) {
        size = size + records[i].getSize();
    }
    return size;
}

size_t Block::getMaxCapacity() const {
    return maxCapacity;
}

bool Block::isFull() const {
    return getSize() >= getMaxCapacity();
}

void Block::deleteRecordFromBlock(int offset) {
    // to delete the record
    records.erase(records.begin() + offset);
    currentNumOfRecords--;
}
