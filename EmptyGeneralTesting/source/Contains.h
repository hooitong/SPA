#pragma once

#include <map>
#include <vector>

#include "Parent.h"
#include "BitTable.h"
#include "GlobalType.h"

class Contains : public Parent {
private:

public:

  void setContains(STMTLINE parent, STMTLINE child);
  void setContainsStar(STMTLINE parent, STMTLINE child);
  bool isContains(STMTLINE first, STMTLINE second);
  bool isContainsStar(STMTLINE first, STMTLINE second);
  STMTLINE getContainParent(STMTLINE child);
  vector<STMTLINE> getContainParentStar(STMTLINE child);
  vector<STMTLINE> getContains(STMTLINE parent);
  vector<STMTLINE> getContainsStar(STMTLINE parent);
};
