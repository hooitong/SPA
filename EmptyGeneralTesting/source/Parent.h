#pragma once
#include <vector>
#include "GlobalTypedef.h"
#include "TNode.h"


class Parent
{
public:
	Parent(void);
	~Parent(void);

	bool setParent(STMTLINE parent, STMTLINE child);
	bool isParent(STMTLINE first, STMTLINE second);
	bool isParentStar(STMTLINE first, STMTLINE second);
	TNode getParent(STMTLINE child);
	vector<TNode> getParentStar(STMTLINE child);
	vector<TNode> getChildOf(STMTLINE parent);
	vector<TNode> getChildOfStar(STMTLINE parent);


};

