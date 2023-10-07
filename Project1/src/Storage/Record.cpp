//
// Created by Jia Ming Sim on 14/9/23.
//

#include "Record.h"

Record::Record(std::string date, int team_id, int pts, float fg_pct, float ft_pct,
               float fg3_pct, int ast, int reb, bool home_team_wins)
    : GAME_DATE_EST(date), TEAM_ID_home(team_id), PTS_home(pts),
      FG_PCT_home(fg_pct), FT_PCT_home(ft_pct), FG3_PCT_home(fg3_pct),
      AST_home(ast), REB_home(reb), HOME_TEAM_WINS(home_team_wins)
{
    isDeleted = false;
}

size_t Record::getSize() const
{
    return sizeof(*this);
}

bool Record::isRecordDeleted() const
{
    return isDeleted;
}

void Record::deleteRecord()
{
    isDeleted = true;
}

float Record::getFgPctHome() const
{
    return FG_PCT_home;
}

float Record::getFg3PctHome() const
{
    return FG3_PCT_home;
}

std::string Record::toString() const
{
    std::string result;
    result += std::string("GAME_DATE_EST: ") + GAME_DATE_EST + "\n";
    result += std::string("TEAM_ID_home: ") + std::to_string(TEAM_ID_home) + "\n";
    result += std::string("PTS_home: ") + std::to_string(PTS_home) + "\n";
    result += std::string("FG_PCT_home: ") + std::to_string(FG_PCT_home) + "\n";
    result += std::string("FT_PCT_home: ") + std::to_string(FT_PCT_home) + "\n";
    result += std::string("FG3_PCT_home: ") + std::to_string(FG3_PCT_home) + "\n";
    result += std::string("AST_home: ") + std::to_string(AST_home) + "\n";
    result += std::string("REB_home: ") + std::to_string(REB_home) + "\n";
    result += std::string("HOME_TEAM_WINS: ") + (HOME_TEAM_WINS ? "true" : "false") + "\n";
    return result;
}
