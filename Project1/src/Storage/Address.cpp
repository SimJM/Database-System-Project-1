//
// Created by Esther Teo on 16/9/23.
//

#include "Address.h"

using namespace std;

Address::Address(int blockID, int offset): blockID(blockID), offset(offset){}

int Address::getBlockID() const {
    return blockID;
}

int Address::getOffset() const{
    return offset;
}

bool operator<(const Address& a1, const Address& a2) {
    return a1.getBlockID() < a2.getBlockID();
}

string Address::toString() const {
    return "The record is located at block " + to_string(blockID) + " with offset " + to_string(offset);
}


