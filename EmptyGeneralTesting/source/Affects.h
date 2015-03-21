#pragma once
#include <vector>
#include "GlobalTypedef.h"
#include "TNode.h"

using namespace std;


class Affects
{
public:
	Affects(void);
	~Affects(void);

	bool isAffects(STMTLINE first, STMTLINE second);
	bool isAffectsStar(STMTLINE first, STMTLINE Second);
	vector<TNode> getAffectedBy(STMTLINE current);
	vector<TNode> getAffectedByStar(STMTLINE current);
	vector<TNode> getAffects(STMTLINE current);
	vector<TNode> getAffectsStar(STMTLINE current); 
	
};

