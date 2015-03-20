#include "VarTable.h"

//constructor
VarTable::VarTable(void)
{

}



VARINDEX insertVar(VARNAME varName)
{
	//return VARINDEX
}

VARNAME getVarName(VARINDEX varIndex){

}

VARINDEX getVarIndex(VARNAME varName){

}

int getSize(){

}

vector<VARINDEX> getAllVar(){

}

bool addModifiedBy(VARINDEX var){

}

//Need to create TNode Class First
bool addUsedBy(VARINDEX var, TNode node){

}

vector<TNode> getModifiedBy(VARINDEX var){

}

vector<TNode> getUsedBy (VARINDEX var){

}



//destructor
VarTable::~VarTable(void)
{

}
