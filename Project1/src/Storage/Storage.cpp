#include "Storage.h"
#include <vector>
#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

Storage::Storage()
{
    currentNumOfRecords = 0;
    int blockSize = 400;
    int numOfBlocks = DISK_CAPACITY / blockSize;
    blocks.resize(numOfBlocks);
    availableBlocks.clear();
    filledBlocks.clear();

    for (int i = 0; i < numOfBlocks; i++)
    {
        blocks[i] = Block();
        availableBlocks.push_back(i);
    }
}

Address Storage::insertRecordIntoBlock(int blockPtr, const Record &rec)
{
    int offset = blocks[blockPtr].addRecord(rec);

    if (blocks[blockPtr].isFull())
    {
        availableBlocks.erase(availableBlocks.begin());
        filledBlocks.push_back(blockPtr);
    }

    return Address(blockPtr, offset);
}

Address Storage::writeRecordToStorage(const Record &record)
{
    currentNumOfRecords++;
    int blockPtr = getFirstAvailableBlockId();
    Address addressOfRecord = insertRecordIntoBlock(blockPtr, record);
    return addressOfRecord;
}

int Storage::getFirstAvailableBlockId()
{
    if (availableBlocks.empty())
    {
        return -1;
    }
    return *(availableBlocks.begin());
}

int Storage::getCurrentNumOfRecords() const
{
    return currentNumOfRecords;
}

int Storage::getNumOfFullBlocks() const
{
    return filledBlocks.size();
}

Block Storage::getBlock(int blockPtr) const
{
    Block block = blocks[blockPtr];
    return block;
}

Record Storage::getRecord(const Address &add) const
{
    int blockId = add.getBlockID();
    int offset = add.getOffset();
    Block block = getBlock(blockId);
    return block.getRecord(offset);
}

void Storage::deleteRecord(vector<Address *> addList)
{
    auto startTime = high_resolution_clock::now();
    for (const Address *add : addList)
    {
        int blockId = add->getBlockID();
        int offset = add->getOffset();
        Block block = getBlock(blockId);
        block.deleteRecordFromBlock(offset);

        if (containsFilledBlock(blockId))
        {
            removeFilledBlock(blockId);
            addAvailableBlock(blockId);
        }
    }
    auto endTime = high_resolution_clock::now();
    long long duration = duration_cast<nanoseconds>(endTime - startTime).count();
    std::cout << "Time taken to delete list of records: " + std::to_string(duration) + " nanoseconds" << std::endl;
}

int Storage::getDataBlockAccessCount(vector<Address *> addresses) const
{
    unordered_set<int> blockAccessed;
    int len = addresses.size();
    for (int i = 0; i < len; i++)
    {
        int blockId = addresses[i]->getBlockID();
        blockAccessed.insert(blockId);
    };
    int numOfBlockAccessed = blockAccessed.size();
    return numOfBlockAccessed;
}

long long Storage::timeTakenToRetrieveRecords(vector<Address *> addresses) const
{
    auto startTime = high_resolution_clock::now();

    int len = addresses.size();
    for (int i = 0; i < len; i++)
    {
        Record r = getRecord(*addresses[i]);
    }

    auto endTime = high_resolution_clock::now();
    long long duration = duration_cast<nanoseconds>(endTime - startTime).count();
    return duration;
}

double Storage::getAverageOfFg3PctHome(vector<Address *> addresses) const
{
    double total;
    int len = addresses.size();
    for (int i = 0; i < len; i++)
    {
        Record r = getRecord(*addresses[i]);
        double fg3PctHome = r.getFg3PctHome();
        total = total + fg3PctHome;
    }
    double average = total / len;
    return average;
}

int Storage::runBruteForceSearchQuery(double FG_PCT_home) const
{
    double FG_PCT_home_value;
    int countDataBlockAccess = 0;
    vector<Record> resultOfSearchQuery;

    auto startTime = high_resolution_clock::now();

    for (int blockPtr : filledBlocks)
    {
        countDataBlockAccess++;
        Block block = getBlock(blockPtr);
        int curNumOfRecordsInBlock = block.getCurrentNumOfRecords();

        for (int i = 0; i < curNumOfRecordsInBlock; i++)
        {
            Record rec = block.getRecord(i);
            FG_PCT_home_value = rec.getFgPctHome();
            if (FG_PCT_home_value == FG_PCT_home)
            {
                resultOfSearchQuery.push_back(rec);
            }
        }
    }

    auto endTime = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(endTime - startTime);
    cout << "Running time of the brute-force linear scan method for Search Query: " << duration.count() << " nanoseconds" << endl;

    return countDataBlockAccess;
}

int Storage::runBruteForceRangeQuery(double FG_PCT_home_lower_val, double FG_PCT_home_upper_val) const
{
    double FG_PCT_home_value;
    int countDataBlockAccess = 0;
    vector<Record> resultOfSearchQuery;

    auto startTiming = high_resolution_clock::now();

    for (int blockPtr : filledBlocks)
    {
        countDataBlockAccess++;
        Block block = getBlock(blockPtr);

        int curNumOfRecordsInBlock = block.getCurrentNumOfRecords();
        for (int i = 0; i < curNumOfRecordsInBlock; i++)
        {
            Record rec = block.getRecord(i);
            FG_PCT_home_value = rec.getFgPctHome();
            if (FG_PCT_home_value >= FG_PCT_home_lower_val && FG_PCT_home_value <= FG_PCT_home_upper_val)
            {
                resultOfSearchQuery.push_back(rec);
            }
        }
    }

    auto endTiming = high_resolution_clock::now();
    auto durationTime = duration_cast<nanoseconds>(endTiming - startTiming);
    cout << "Running time of the brute-force linear scan method for Range Query: " << durationTime.count() << " nanoseconds" << endl;

    return countDataBlockAccess;
}

int Storage::runBruteForceRangeDelete(double FG_PCT_home_lower_val, double FG_PCT_home_upper_val) const
{
    double FG_PCT_home_value;
    int countDataBlockAccess = 0;
    vector<Record> resultOfSearchQuery;

    auto startTiming = high_resolution_clock::now();

    for (int blockPtr : filledBlocks)
    {
        countDataBlockAccess++;
        Block block = getBlock(blockPtr);

        int curNumOfRecordsInBlock = block.getCurrentNumOfRecords();
        for (int i = 0; i < curNumOfRecordsInBlock; i++)
        {
            Record rec = block.getRecord(i);
            FG_PCT_home_value = rec.getFgPctHome();
            if (FG_PCT_home_value >= FG_PCT_home_lower_val && FG_PCT_home_value <= FG_PCT_home_upper_val)
            {
                block.deleteRecordFromBlock(i);
            }
        }
    }

    auto endTiming = high_resolution_clock::now();
    auto durationTime = duration_cast<nanoseconds>(endTiming - startTiming);
    cout << "Running time of the brute-force linear scan method for Range Delete: " << durationTime.count() << " nanoseconds" << endl;

    return countDataBlockAccess;
}

bool Storage::containsFilledBlock(int blockId) const
{
    return find(filledBlocks.begin(), filledBlocks.end(), blockId) != filledBlocks.end();
}

int Storage::removeFilledBlock(int blockId)
{
    filledBlocks.erase(remove(filledBlocks.begin(), filledBlocks.end(), blockId), filledBlocks.end());
    return 0;
}

int Storage::addAvailableBlock(int blockId)
{
    availableBlocks.push_back(blockId);
    return 0;
}
