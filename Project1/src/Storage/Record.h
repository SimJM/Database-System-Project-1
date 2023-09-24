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


    bool operator==(const Record& other) const {
        return (
                GAME_DATE_EST == other.GAME_DATE_EST &&
                TEAM_ID_home == other.TEAM_ID_home &&
                PTS_home == other.PTS_home &&
                FG_PCT_home == other.FG_PCT_home &&
                FT_PCT_home == other.FT_PCT_home &&
                FG3_PCT_home == other.FG3_PCT_home &&
                AST_home == other.AST_home &&
                REB_home == other.REB_home &&
                HOME_TEAM_WINS == other.HOME_TEAM_WINS
        );
    }
};

#endif //PROJECT1_RECORD_H
