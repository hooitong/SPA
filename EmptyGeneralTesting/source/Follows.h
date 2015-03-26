#pragma once

#include <vector>
#include <map>

#include "GlobalType.h"

class Follows {
  private:
    std::map<STMTLINE, STMTLINE> rightSiblingMap;
    std::map<STMTLINE, STMTLINE> leftSiblingMap;
    std::map<STMTLINE,STMTLINE>::iterator it;

  public:
    Follows(void);
    ~Follows(void);

    bool setFollows(STMTLINE first, STMTLINE second);
    bool setFollowsStar(STMTLINE first, STMTLINE second);
    bool isFollow(STMTLINE first, STMTLINE second);
    bool isFollowStar(STMTLINE first, STMTLINE second);
    STMTLINE getFollowedBy(STMTLINE currentLine);
    STMTLINE getFollowsFrom(STMTLINE currentLine);
    vector<STMTLINE> getFollowedByStar(STMTLINE currentLine);
    vector<STMTLINE> getFollowsFromStar(STMTLINE currentLine);
};
