#pragma once

#include "BitTable.h"
#include "GlobalType.h"

#include <vector>
#include <map>
#include <stack> 

class NextBip {
private:
  BitTable beforeToNext;
  BitTable nextToBefore;
  BitTable beforeToAfter;
  BitTable afterToBefore;
  BitTable isNextStarCache;
  BitTable notNextStarCache;
  bool isNextStarRecursive(vector<PROGLINE> &processed, stack<PROGLINE> depth, PROGLINE before, PROGLINE next);
  void getNextStarRecursive(vector<PROGLINE> &result, stack<PROGLINE> depth, PROGLINE current);
  void getBeforeStarRecursive(vector<PROGLINE> &result, stack<PROGLINE> depth, PROGLINE current);

public:
  void setNext(PROGLINE before, PROGLINE next);
  bool isNext(PROGLINE before, PROGLINE next);
  bool isNextStar(PROGLINE before, PROGLINE next);
  vector<PROGLINE> getBefore(PROGLINE current);
  vector<PROGLINE> getBeforeStar(PROGLINE current);
  vector<PROGLINE> getNext(PROGLINE current);
  vector<PROGLINE> getNextStar(PROGLINE current);
};