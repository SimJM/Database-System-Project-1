//
// Created by Jia Ming Sim on 14/9/23.
//

#include "Record.h"
#include "Block.h"

Block::Block(int BLOCK_SIZE) : curRecords(0){
    maxRecordCount = maxCapacity / sizeof(Record);
    records.reserve(maxRecordCount);
 }

const Record* Block::getRecordFromBlock(int recordPos) const {
    if (recordPos >= 0 && recordPos < records.size()) {
        return &records[recordPos];
    }
    return nullptr;
}

int Block::getCurNumRecords() const {
    return records.size();
}

//Block::Block(int id) : blockId(id) {
//    blockId = id;
//    maxCapacity = 400;
//    maxRecordCount = maxCapacity / sizeof(Record);
//    records.reserve(maxRecordCount);
//}

int Block::addRecordInBlock(const Record& record) {
    if (!isFull()) {
        records.push_back(record);
        return static_cast<int>(records.size()) - 1;
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
//
//int Block::getId() const {
//    return blockId;
//}

const Record*Block::getRecord(int offset) const {
    return &records[offset];
}
