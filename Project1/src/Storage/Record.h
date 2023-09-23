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
    bool isRecordDeleted() const;
    void deleteRecord();
    std::string toString() const;

    std::string GAME_DATE_EST; // 24 Bytes
    long long TEAM_ID_home; //8 Bytes
    int PTS_home; //4 Bytes
    double FG_PCT_home; // 8 Bytes
    double FT_PCT_home; // 8 Bytes
    double FG3_PCT_home; // 8 Bytes
    int AST_home; //4 Bytes
    int REB_home; //4 Bytes
    bool HOME_TEAM_WINS; // 1 Byte
    bool isDeleted; // 1 Byte
};

#endif //PROJECT1_RECORD_H
