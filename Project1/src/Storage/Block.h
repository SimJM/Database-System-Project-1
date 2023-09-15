//
// Created by Jia Ming Sim on 14/9/23.
//

#ifndef PROJECT1_BLOCK_H
#define PROJECT1_BLOCK_H

#include <vector>
#include "Record.h"

class Block {
public:
    Block(int id);

    void addRecord(const Record& record);
    size_t getSize() const;
    size_t getMaxCapacity() const;
    bool isFull() const;
    int getId() const;

private:
    int blockId;
    std::vector<Record> records;
    size_t maxCapacity;          // Maximum block size in bytes
    size_t maxRecordCount;       // Maximum number of records that can fit in the block
};

#endif //PROJECT1_BLOCK_H
