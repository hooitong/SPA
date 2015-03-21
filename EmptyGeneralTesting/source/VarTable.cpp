#include "VarTable.h"
/* Constructor & Destructor */
VarTable::VarTable(void)
{
	currentMapIndex = 0;
}

VarTable::~VarTable(void)
{

}

VARINDEX VarTable::insertVar(VARNAME varName)
{
	VARINDEX v = getVarIndex(varName);
	/* if varName already exist in varTable, return index */
	if(v != -1){
		return v;
	}
	
	/* Create new varInfo and insert into both index and name maps */
	varInfo variable = {};
	variable.var_name = varName;
	variable.var_index = currentMapIndex;
	varIndexMap[currentMapIndex] = variable;
	varNameMap[varName] = variable;

	/* Increment the static index */
	VARINDEX newIndex = currentMapIndex++;
	return newIndex;
}

VARNAME VarTable::getVarName(VARINDEX varIndex){
	/* Check if varIndex is valid */
	if(varIndex < 0 || varIndex >= currentMapIndex) {
		return NULL;
	} else {
		return varIndexMap[varIndex].var_name;
	}
}

VARINDEX VarTable::getVarIndex(VARNAME varName){
	map<VARNAME, varInfo>::iterator itr = varNameMap.find(varName);
	if(itr != varNameMap.end()) {
		return itr->second.var_index;
	} else {
		return -1;
	}
}

int VarTable::getSize(){
	return currentMapIndex;
}

vector<VARINDEX> VarTable::getAllVarIndex(){
	vector<VARINDEX> listOfVarIndex;
	for(int i = 0; i < currentMapIndex; i++) {
		listOfVarIndex.push_back(i);
	}
	return listOfVarIndex;
}

vector<VARNAME> VarTable::getAllVarName(){
	vector<VARNAME> listOfVarName;
	for(int i = 0; i < currentMapIndex; i++) {
		listOfVarName.push_back(varIndexMap[i].var_name);
	}
	return listOfVarName;
}

bool VarTable::addModifiedBy(VARINDEX varIndex, TNode node){
	if(varIndex < 0 || varIndex >= currentMapIndex) {
		return false;
	} else {
		varIndexMap[varIndex].modified_by.push_back(node);
		return true;
	}
}

bool VarTable::addUsedBy(VARINDEX varIndex, TNode node){
	if(varIndex < 0 || varIndex >= currentMapIndex) {
		return false;
	} else {
		varIndexMap[varIndex].used_by.push_back(node);
		return false;
	}
}

vector<TNode> VarTable::getModifiedBy(VARINDEX varIndex){
	if(varIndex < 0 || varIndex >= currentMapIndex) {
		//return NULL;
	} else {
		return varIndexMap[varIndex].modified_by; 
	}
}

vector<TNode> VarTable::getUsedBy (VARINDEX varIndex){
	if(varIndex < 0 || varIndex >= currentMapIndex) {
		//return NULL;
	} else {
		return varIndexMap[varIndex].used_by; 
	}
}
