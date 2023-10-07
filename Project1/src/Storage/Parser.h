//
// Created by Jia Ming Sim on 15/9/23.
//

#ifndef PROJECT1_PARSER_H
#define PROJECT1_PARSER_H

#include <string>
#include <vector>
#include "Record.h"

class Parser
{
public:
    Parser();

    std::vector<Record> parse(const std::string &filename);
};

#endif // PROJECT1_PARSER_H
