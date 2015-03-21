#include "VarTable.h"

//constructor
VarTable::VarTable(void)
{

}



VarIndex insertVar(VarName VarName)
{
	return -1;
}

VarName getVarName(VarIndex VarIndex){
	return "";
}

VarIndex getVarIndex(VarName VarName){
	return -1;
}

int getSize(){
	return -1;
}

vector<VarIndex> getAllVar(){
	vector<VarIndex> VarIndexList;
	return VarIndexList;
}

bool addModifiedBy(VarIndex var){
	return false;
}

//Need to create TNode Class First
bool addUsedBy(VarIndex var, TNode node){
	return false;
}

vector<TNode> getModifiedBy(VarIndex var){
	vector<TNode> tNodeList;
	return tNodeList;
}

vector<TNode> getUsedBy (VarIndex var){
	vector<TNode> tNodeList;
	return tNodeList;
}

//destructor
VarTable::~VarTable(void)
{

}
