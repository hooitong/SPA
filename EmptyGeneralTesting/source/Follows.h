#pragma once
#include <vector>
#include <map>
#include "GlobalTypedef.h"
#include "TNode.h"

class Follows
{
private:
	static std::map<STMTLINE, STMTLINE> rightSiblingMap;
	static std::map<STMTLINE, STMTLINE> leftSiblingMap;
	static std::map<STMTLINE,STMTLINE>::iterator it;

public:
	Follows(void);
	~Follows(void);

	static bool setFollows(STMTLINE first, STMTLINE second);
	static bool setFollowsStar(STMTLINE first, STMTLINE second);
	static bool isFollow(STMTLINE first, STMTLINE second);
	static bool isFollowStar(STMTLINE first, STMTLINE second);
	static STMTLINE getFollowedBy(STMTLINE currentLine);
	static STMTLINE getFollowsFrom(STMTLINE currentLine);
	static vector<STMTLINE> getFollowedByStar(STMTLINE currentLine);
	static vector<STMTLINE> getFollowsFromStar(STMTLINE currentLine);
};

