//
// Created by Jia Ming Sim on 7/10/23.
//

using namespace std;

#ifndef PROJECT1_MAIN_H
#define PROJECT1_MAIN_H

#include <iostream>
#include <vector>
#include "Storage/Record.h"
#include "Storage/Storage.h"
#include "Indexing/BPlusTree.h"

void print();
void print(std::string str);
void experiment1(std::vector<Record> records, Storage storage);
void experiment2(Storage storage, BPlusTree bPlusTree, std::vector<Address> addresses);
void experiment3(Storage storage, BPlusTree bPlusTree);
void experiment4(Storage storage, BPlusTree bPlusTree);
void experiment5(Storage storage, BPlusTree bPlusTree, bool isBruteForce);

#endif //PROJECT1_MAIN_H
