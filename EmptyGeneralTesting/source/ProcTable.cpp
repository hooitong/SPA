#include "PROCTable.h"

//constructor
PROCTable::PROCTable(void)
{
}

PROCINDEX insertPROC(PROCNAME PROCName)
{
	return -1;
}

PROCINDEX getPROCINDEX(PROCNAME PROCName)
{
	return -1;
}

PROCNAME getPROCName(PROCINDEX PROCINDEX)
{
	return "";
}

vector<PROCNAME> getAllPROC()
{
	vector<PROCNAME> PROCNameList;
	return PROCNameList;
}

bool setTRoot(PROCINDEX index, TNode node)
{
	return false;
}

bool setGRoot(PROCINDEX index, GNode node)
{
	return false;
}

TNode getTRoot(PROCINDEX index)
{
	return TNode();
}

GNode getGNode(PROCINDEX index)
{
	return GNode();
}

bool addModified(PROCINDEX PROC, VARINDEX var)
{
	return false;
}

bool addUsed(PROCINDEX PROC, VARINDEX var)
{
	return false;
}

vector<VARINDEX> getModified(PROCINDEX PROC)
{
	vector<VARINDEX> VARINDEXList;
	return VARINDEXList;
}

vector<VARINDEX> getUsed(PROCINDEX PROC)
{
	vector<VARINDEX> VARINDEXList;
	return VARINDEXList;
}

//destructor
PROCTable::~PROCTable(void)
{
}