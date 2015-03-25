#pragma once

#include <map>
#include <vector>

#include "GlobalType.h"

class Parent
{
private:
	std::multimap<STMTLINE, STMTLINE> parent2ChildMap;
	std::map<STMTLINE, STMTLINE> child2ParentMap;
	std::multimap<STMTLINE, STMTLINE> parent2ChildMapStar;
	std::multimap<STMTLINE, STMTLINE> child2ParentMapStar;
	std::multimap<STMTLINE,STMTLINE>::iterator it;
	std::map<STMTLINE,STMTLINE>::iterator it2;
	std::pair <std::multimap<STMTLINE,STMTLINE>::iterator, std::multimap<STMTLINE,STMTLINE>::iterator> ret;

public:
	Parent(void);
	~Parent(void);
	bool setParent(STMTLINE parent, STMTLINE child);
	bool setParentStar(STMTLINE parent, STMTLINE child);
	bool isParent(STMTLINE first, STMTLINE second);
	bool isParentStar(STMTLINE first, STMTLINE second);
	STMTLINE getParent(STMTLINE child);
	vector<STMTLINE> getParentStar(STMTLINE child);
	vector<STMTLINE> getChildOf(STMTLINE parent);
	vector<STMTLINE> getChildOfStar(STMTLINE parent);
};
