#pragma once
#include <vector>
#include "TNode.h"

using namespace std;

typedef int STMTLine;

class Follows
{
public:
	Follows(void);
	~Follows(void);

	TNode setFollows(STMTLine stmtLineFirst, STMTLine stmtLineSecond);
	bool isFollow(STMTLine stmtLineFirst, STMTLine stmtLineSecond);
	bool isFollowStar(STMTLine stmtLineFirst, STMTLine stmtLineSecond);
	vector<TNode> getFollowedByStar(STMTLine currentLine);
	vector<TNode> getFollowsFromStar(STMTLine currentLine);
};

