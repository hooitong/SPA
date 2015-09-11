#pragma once
#include "GlobalType.h"
#include <vector>

class Next {
public:
	bool isNext(PROGLINE first, PROGLINE second);
	bool isNextStar(PROGLINE first, PROGLINE second);
	vector<PROGLINE> getBefore(PROGLINE current);
	vector<PROGLINE> getBeforeStar(PROGLINE current);
	vector<PROGLINE> getNext(PROGLINE current);
	vector<PROGLINE> getNextStar(PROGLINE current);
};
