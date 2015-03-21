#pragma once

#include "TNode.h"
#include <vector>
typedef int STMTLine;

class Follows
{
public:
	Follows(void);
	~Follows(void);

	TNode setFollows(STMTLine stmtLineFirst, STMTLine stmtLineSecond);
	bool isFollow(STMTLine stmtLineFirst, STMTLine second);
	bool isFollowStar(STMTLine stmtLineFirst, STMTLine second);
	vector<TNode> getFollowedByStar(STMTLine line);
	vector<TNode> getFollowsFromStar(STMTLine line);
};

