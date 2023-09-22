//
// Created by Jia Ming Sim on 14/9/23.
//

#ifndef PROJECT1_RECORD_H
#define PROJECT1_RECORD_H

#include <string>

class Record {
public:
    Record(std::string date, long long team_id, int pts, double fg_pct, double ft_pct, double fg3_pct, int ast, int reb, bool home_team_wins);

    size_t getSize() const;
    std::string toString() const;

    std::string GAME_DATE_EST;
    long long TEAM_ID_home;
    int PTS_home;
    double FG_PCT_home;
    double FT_PCT_home;
    double FG3_PCT_home;
    int AST_home;
    int REB_home;
    bool HOME_TEAM_WINS;
};

#endif //PROJECT1_RECORD_H
