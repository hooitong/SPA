#pragma once
#include <vector>
#include "TNode.h"
#include "GlobalType.h"

class Calls
{
public:
	Calls(void);
	~Calls(void);

	bool setCalls(PROCINDEX caller, PROCINDEX called);
	bool isCall(PROCINDEX caller, PROCINDEX called);
	bool isCallStar(PROCINDEX caller, PROCINDEX called);
	vector<TNode> getCalledBy(PROCINDEX caller);
	vector<TNode> getCalledByStar(PROCINDEX called);
	vector<TNode> getCallsToStar(PROCINDEX called);

};

