#include "ProcTable.h"

//constructor
ProcTable::ProcTable(void)
{
}

ProcIndex insertProc(ProcName ProcName)
{
	return -1;
}

ProcIndex getProcIndex(ProcName ProcName)
{
	return -1;
}

ProcName getProcName(ProcIndex ProcIndex)
{
	return "";
}

vector<ProcName> getAllProc()
{
	vector<ProcName> ProcNameList;
	return ProcNameList;
}

bool setTRoot(ProcIndex index, TNode node)
{
	return false;
}

bool setGRoot(ProcIndex index, GNode node)
{
	return false;
}

TNode getTRoot(ProcIndex index)
{
	return TNode();
}

GNode getGNode(ProcIndex index)
{
	return GNode();
}

bool addModified(ProcIndex proc, VarIndex var)
{
	return false;
}

bool addUsed(ProcIndex proc, VarIndex var)
{
	return false;
}

vector<VarIndex> getModified(ProcIndex proc)
{
	vector<VarIndex> VarIndexList;
	return VarIndexList;
}

vector<VarIndex> getUsed(ProcIndex proc)
{
	vector<VarIndex> VarIndexList;
	return VarIndexList;
}

//destructor
ProcTable::~ProcTable(void)
{

}
