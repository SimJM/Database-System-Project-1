//
// Created by Esther Teo on 16/9/23.
//

#ifndef ADDRESS_H
#define ADDRESS_H

#include <string>

class Address
{
private:
    int blockID;
    int offset;

public:
    Address(int blockID, int offset);

    int getBlockID() const;
    int getOffset() const;

    std::string toString() const;
};

#endif // ADDRESS_H
