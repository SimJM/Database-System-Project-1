//
// Created by Jia Ming Sim on 14/9/23.
//

#include "Record.h"

Record::Record(std::string date, long long team_id, int pts, double fg_pct, double ft_pct,
               double fg3_pct, int ast, int reb, bool home_team_wins)
        : GAME_DATE_EST(date), TEAM_ID_home(team_id), PTS_home(pts),
          FG_PCT_home(fg_pct), FT_PCT_home(ft_pct), FG3_PCT_home(fg3_pct),
          AST_home(ast), REB_home(reb), HOME_TEAM_WINS(home_team_wins) {
}

size_t Record::getSize() const {
    return sizeof(*this);
}
