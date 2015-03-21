#pragma once
#include <vector>
#include "TNode.h"

typedef int ProcIndex;

class Calls
{
public:
	Calls(void);
	~Calls(void);

	bool setCalls(ProcIndex caller, ProcIndex called);
	bool isCall(ProcIndex caller, ProcIndex called);
	bool isCallStar(ProcIndex caller, ProcIndex called);
	vector<TNode> getCalledBy(ProcIndex caller);
	vector<TNode> getCalledByStar(ProcIndex called);
	vector<TNode> getCallsToStar(ProcIndex called);

};

