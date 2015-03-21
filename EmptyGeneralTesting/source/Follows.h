#pragma once
#include <vector>
#include "GlobalTypedef.h"
#include "TNode.h"

using namespace std;


class Follows
{
public:
	Follows(void);
	~Follows(void);

	TNode setFollows(STMTLINE STMTLINEFirst, STMTLINE STMTLINESecond);
	bool isFollow(STMTLINE STMTLINEFirst, STMTLINE STMTLINESecond);
	bool isFollowStar(STMTLINE STMTLINEFirst, STMTLINE STMTLINESecond);
	vector<TNode> getFollowedByStar(STMTLINE currentLine);
	vector<TNode> getFollowsFromStar(STMTLINE currentLine);
};

