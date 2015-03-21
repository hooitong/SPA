#include "PROCTable.h"

//constructor
PROCTable::PROCTable(void)
{
}

PROCINDEX insertPROC(PROCName PROCName)
{
	return -1;
}

PROCINDEX getPROCINDEX(PROCName PROCName)
{
	return -1;
}

PROCName getPROCName(PROCINDEX PROCINDEX)
{
	return "";
}

vector<PROCName> getAllPROC()
{
	vector<PROCName> PROCNameList;
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
