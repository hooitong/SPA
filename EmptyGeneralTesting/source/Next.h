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

public:
	void setNext(PROGLINE before, PROGLINE next);
	void setNextStar(PROGLINE before, PROGLINE next);
	bool isNext(PROGLINE before, PROGLINE next);
	bool isNextStar(PROGLINE before, PROGLINE next);
	vector<PROGLINE> getBefore(PROGLINE current);
	vector<PROGLINE> getBeforeStar(PROGLINE current);
	vector<PROGLINE> getNext(PROGLINE current);
	vector<PROGLINE> getNextStar(PROGLINE current);
};
