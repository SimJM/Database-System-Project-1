//
// Created by Jia Ming Sim on 14/9/23.
//

#include "Record.h"
#include "Block.h"

Block::Block(int id) : blockId(id) {
    blockId = id;
    maxCapacity = 400;
    maxRecordCount = maxCapacity / sizeof(Record);
    records.reserve(maxRecordCount);
}

void Block::addRecord(const Record& record) {
    if (!isFull()) {
        records.push_back(record);
    }
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

int Block::getId() const {
    return blockId;
}

