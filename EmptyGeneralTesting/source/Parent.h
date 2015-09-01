#pragma once

#include <map>
#include <vector>

#include "BitTable.h"
#include "GlobalType.h"

class Parent {
  private:
    BitTable parentToChild;
    std::map<STMTLINE, STMTLINE> childToParent;
    BitTable parentToChildStar;
    BitTable childToParentStar;

  public:
    Parent(void);
    ~Parent(void);

    void setParent(STMTLINE parent, STMTLINE child);
    void setParentStar(STMTLINE parent, STMTLINE child);
    bool isParent(STMTLINE first, STMTLINE second);
    bool isParentStar(STMTLINE first, STMTLINE second);
    STMTLINE getParent(STMTLINE child);
    vector<STMTLINE> getParentStar(STMTLINE child);
    vector<STMTLINE> getChildOf(STMTLINE parent);
    vector<STMTLINE> getChildOfStar(STMTLINE parent);
};
