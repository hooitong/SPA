#pragma once
#include <map>
#include <vector>
#include "GlobalTypedef.h"
#include "TNode.h"


class Parent
{
private:
	static std::multimap<STMTLINE, STMTLINE> parent2ChildMap;
	static std::map<STMTLINE, STMTLINE> child2ParentMap;
	static std::multimap<STMTLINE, STMTLINE> parent2ChildMapStar;
	static std::multimap<STMTLINE, STMTLINE> child2ParentMapStar;
	static std::multimap<STMTLINE,STMTLINE>::iterator it;
	static std::map<STMTLINE,STMTLINE>::iterator it2;
	static std::pair <std::multimap<STMTLINE,STMTLINE>::iterator, std::multimap<STMTLINE,STMTLINE>::iterator> ret;

public:
	Parent(void);
	~Parent(void);
	static bool setParent(STMTLINE parent, STMTLINE child);
	static bool setParentStar(STMTLINE parent, STMTLINE child);
	static bool isParent(STMTLINE first, STMTLINE second);
	static bool isParentStar(STMTLINE first, STMTLINE second);
	static STMTLINE getParent(STMTLINE child);
	static vector<STMTLINE> getParentStar(STMTLINE child);
	static vector<STMTLINE> getChildOf(STMTLINE parent);
	static vector<STMTLINE> getChildOfStar(STMTLINE parent);
};

