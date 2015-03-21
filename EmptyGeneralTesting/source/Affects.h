#pragma once
#include <vector>
#include "TNode.h"

using namespace std;

typedef STMTLine;

class Affects
{
public:
	Affects(void);
	~Affects(void);

	bool isAffects(STMTLine first, STMTLine second);
	bool isAffectsStar(STMTLine first, STMTLine Second);
	vector<TNode> getAffectedBy(STMTLine current);
	vector<TNode> getAffectedByStar(STMTLine current);
	vector<TNode> getAffects(STMTLine current);
	vector<TNode> getAffectsStar(STMTLine current); 
	
};

