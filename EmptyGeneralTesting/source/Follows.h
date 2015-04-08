#pragma once

#include <vector>
#include <map>

#include "GlobalType.h"

class Follows {
  private:
    std::map<STMTLINE, STMTLINE> rightSiblingMap;
    std::map<STMTLINE, STMTLINE> leftSiblingMap;
    std::map<STMTLINE,STMTLINE>::iterator it;

    std::multimap<STMTLINE, STMTLINE> rightSiblingsMap;
    std::multimap<STMTLINE, STMTLINE> leftSiblingsMap;
    std::multimap<STMTLINE,STMTLINE>::iterator it2;
    std::pair<std::multimap<STMTLINE,STMTLINE>::iterator, std::multimap<STMTLINE,STMTLINE>::iterator> ret;

  public:
    Follows(void);
    ~Follows(void);

    void setFollows(STMTLINE first, STMTLINE second);
    void setFollowsStar(STMTLINE first, STMTLINE second);
    bool isFollows(STMTLINE first, STMTLINE second);
    bool isFollowsStar(STMTLINE first, STMTLINE second);
    STMTLINE getFollowedBy(STMTLINE currentLine);
    STMTLINE getFollowsFrom(STMTLINE currentLine);
    vector<STMTLINE> getFollowedByStar(STMTLINE currentLine);
    vector<STMTLINE> getFollowsFromStar(STMTLINE currentLine);
};
