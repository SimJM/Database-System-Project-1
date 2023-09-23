//
// Created by Jia Ming Sim on 14/9/23.
//

#ifndef PROJECT1_BLOCK_H
#define PROJECT1_BLOCK_H

#include <vector>
#include "Record.h"

class Block {
public:
    Block();

    Record getRecord(int offset) const;
    int getCurrentNumOfRecords() const;
    int getMaxNumOfRecords() const;
    int addRecord(const Record& record);
    size_t getSize() const;
    size_t getMaxCapacity() const;
    bool isFull() const;

private:
    int currentNumOfRecords;
    int maxNumOfRecords;
    std::vector<Record> records;
    size_t maxCapacity; // Maximum block size in bytes
};

#endif //PROJECT1_BLOCK_H
