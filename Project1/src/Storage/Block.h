//
// Created by Jia Ming Sim on 14/9/23.
//

#ifndef PROJECT1_BLOCK_H
#define PROJECT1_BLOCK_H

#include <vector>
#include "Record.h"

class Block {
public:
    Block(int BLOCK_SIZE);      // is BLOCK_SIZE defined in parser?
    ~Block();       // destructor to free memory

    int addRecordInBlock(const Record& record);   // adds the record to the block and returns the offset
    size_t getSize() const;
    size_t getMaxCapacity() const;
    bool isFull() const;
    int getId() const;

    const Record* getRecordFromBlock(int recordIndex) const;  // retrieves record from the block based on its offset
    const Record* getRecord(int offset) const;
    int getCurNumRecords() const;     // get current number of records stored in the block
    static int getTotalRecords();
    // haven't included deleting record part yet

private:
    int blockId;
    int curRecords;             // no of records in the block currently
//    static const int totalRecords;    // total no of records in one block
    // will the value of totalRecords change during runtime?
    std::vector<Record> records;
    size_t maxCapacity;          // Maximum block size in bytes
    size_t maxRecordCount;       // Maximum number of records that can fit in the block
};

#endif //PROJECT1_BLOCK_H
