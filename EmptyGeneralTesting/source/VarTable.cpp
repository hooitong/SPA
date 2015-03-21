#include "VarTable.h"

//constructor
VarTable::VarTable(void)
{

}



VARINDEX insertVar(VARNAME varName)
{
	return -1;
}

VARNAME getVarName(VARINDEX varIndex){
	return "";
}

VARINDEX getVarIndex(VARNAME varName){
	return -1;
}

int getSize(){
	return -1;
}

vector<VARINDEX> getAllVar(){
	vector<VARINDEX> varIndexList;
	return varIndexList;
}

bool addModifiedBy(VARINDEX var){
	return false;
}

//Need to create TNode Class First
bool addUsedBy(VARINDEX var, TNode node){
	return false;
}

vector<TNode> getModifiedBy(VARINDEX var){
	vector<TNode> tNodeList;
	return tNodeList;
}

vector<TNode> getUsedBy (VARINDEX var){
	vector<TNode> tNodeList;
	return tNodeList;
}

//destructor
VarTable::~VarTable(void)
{

}
