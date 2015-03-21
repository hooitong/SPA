#pragma once
#include <vector>
#include "GlobalTypedef.h"
#include "TNode.h"
#include "GNode.h"

using namespace std;


class PROCTable
{
public:
	PROCTable(void);
	~PROCTable(void);

	PROCINDEX insertPROC(PROCName PROCName);
	PROCINDEX getPROCINDEX(PROCName PROCName);
	PROCName getPROCName(PROCINDEX PROCINDEX);
	vector<PROCName> getAllPROC();
	bool setTRoot(PROCINDEX index, TNode node);
	bool setGRoot(PROCINDEX index, GNode node);
	TNode getTRoot(PROCINDEX index);
	GNode getGNode(PROCINDEX index);
	bool addModified(PROCINDEX PROC, VARINDEX var);
	bool addUsed(PROCINDEX PROC, VARINDEX var);
	vector<VARINDEX> getModified(PROCINDEX PROC);
	vector<VARINDEX> getUsed(PROCINDEX PROC);
};

