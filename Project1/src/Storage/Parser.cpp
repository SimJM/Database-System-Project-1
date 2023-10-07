//
// Created by Jia Ming Sim on 15/9/23.
//

#include "Parser.h"
#include <fstream>
#include <sstream>
#include <iostream>

Parser::Parser() {}

std::vector<Record> Parser::parse(const std::string &filename)
{
    std::vector<Record> records;

    std::ifstream inputFile(filename);

    if (!inputFile.is_open())
    {
        std::cerr << "Failed to open the input file: " << filename << std::endl;
        return records;
    }

    // Read and discard the header line
    std::string header;
    std::getline(inputFile, header);

    std::string line;
    while (std::getline(inputFile, line))
    {
        std::istringstream iss(line);
        std::string gameDate = "";
        long long teamId = 0;
        int pts = 0;
        double fgPct = 0.0;
        double ftPct = 0.0;
        double fg3Pct = 0.0;
        int ast = 0;
        int reb = 0;
        bool homeTeamWins = false;

        iss >> gameDate;
        iss >> teamId;
        iss >> pts;
        iss >> fgPct;
        iss >> ftPct;
        iss >> fg3Pct;
        iss >> ast;
        iss >> reb;
        iss >> homeTeamWins;
        Record record(gameDate, teamId, pts, fgPct, ftPct, fg3Pct, ast, reb, homeTeamWins);
        records.push_back(record);
    }

    inputFile.close();
    std::cout << "Parsed Successfully" << std::endl;
    return records;
}
