#include "ProcTable.h"

//constructor
ProcTable::ProcTable(void)
{
}

PROCINDEX insertProc(PROCNAME procName)
{
	return -1;
}

PROCINDEX getProcIndex(PROCNAME procName)
{
	return -1;
}

PROCNAME getProcName(PROCINDEX procIndex)
{
	return "";
}

vector<PROCNAME> getAllProc()
{
	vector<PROCNAME> procNameList;
	return procNameList;
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

bool addModified(PROCINDEX proc, VARINDEX var)
{
	return false;
}

bool addUsed(PROCINDEX proc, VARINDEX var)
{
	return false;
}

vector<VARINDEX> getModified(PROCINDEX proc)
{
	vector<VARINDEX> varIndexList;
	return varIndexList;
}

vector<VARINDEX> getUsed(PROCINDEX proc)
{
	vector<VARINDEX> varIndexList;
	return varIndexList;
}

//destructor
ProcTable::~ProcTable(void)
{

}
