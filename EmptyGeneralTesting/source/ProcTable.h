#pragma once
#include <vector>
#include "TNode.h"
#include "GNode.h"

using namespace std;

typedef int ProcIndex, VarIndex;
typedef string ProcName;

class ProcTable
{
public:
	ProcTable(void);
	~ProcTable(void);

	ProcIndex insertProc(ProcName ProcName);
	ProcIndex getProcIndex(ProcName ProcName);
	ProcName getProcName(ProcIndex ProcIndex);
	vector<ProcName> getAllProc();
	bool setTRoot(ProcIndex index, TNode node);
	bool setGRoot(ProcIndex index, GNode node);
	TNode getTRoot(ProcIndex index);
	GNode getGNode(ProcIndex index);
	bool addModified(ProcIndex proc, VarIndex var);
	bool addUsed(ProcIndex proc, VarIndex var);
	vector<VarIndex> getModified(ProcIndex proc);
	vector<VarIndex> getUsed(ProcIndex proc);
};

