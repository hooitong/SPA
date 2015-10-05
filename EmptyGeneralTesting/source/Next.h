#pragma once

#include "BitTable.h"
#include "GlobalType.h"

#include <vector>

class Next {
private:
  BitTable beforeToNext;
  BitTable nextToBefore;
  BitTable beforeToAfter;
  BitTable afterToBefore;
  bool isNextStarRecursive(vector<PROGLINE> &processed, PROGLINE before, PROGLINE next);
  void getNextStarRecursive(vector<PROGLINE> &result, PROGLINE current);
  void getBeforeStarRecursive(vector<PROGLINE> &result, PROGLINE current);

public:
  void setNext(PROGLINE before, PROGLINE next);
  bool isNext(PROGLINE before, PROGLINE next);
  bool isNextStar(PROGLINE before, PROGLINE next);
  vector<PROGLINE> getBefore(PROGLINE current);
  vector<PROGLINE> getBeforeStar(PROGLINE current);
  vector<PROGLINE> getNext(PROGLINE current);
  vector<PROGLINE> getNextStar(PROGLINE current);
};