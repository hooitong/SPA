#pragma once
#include <vector>
#include "GlobalType.h"
#include "TNode.h"
#include "GNode.h"

using namespace std;


class PROCTable
{
public:
	PROCTable(void);
	~PROCTable(void);

	PROCINDEX insertPROC(PROCNAME PROCName);
	PROCINDEX getPROCINDEX(PROCNAME PROCName);
	PROCNAME getPROCName(PROCINDEX PROCINDEX);
	vector<PROCNAME> getAllPROC();
	bool setTRoot(PROCINDEX index, TNode node);
	bool setGRoot(PROCINDEX index, GNode node);
	TNode getTRoot(PROCINDEX index);
	GNode getGNode(PROCINDEX index);
	bool addModified(PROCINDEX PROC, VARINDEX var);
	bool addUsed(PROCINDEX PROC, VARINDEX var);
	vector<VARINDEX> getModified(PROCINDEX PROC);
	vector<VARINDEX> getUsed(PROCINDEX PROC);
};

