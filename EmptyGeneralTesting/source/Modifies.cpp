#include "Modifies.h"
#include "VarTable.h"

/* Constructor & Destructor */
Modifies::Modifies(void)
{
}

Modifies::~Modifies(void)
{
}

bool Modifies::setModifiesStmt(VARINDEX varIndex, STMTLINE stmt){
	//TODO Implement Validation
	var2StmtMap.insert(std::pair<VARINDEX, STMTLINE>(varIndex, stmt));
	stmt2VarMap.insert(std::pair<STMTLINE, VARINDEX>(stmt, varIndex));
	return true;
}

vector<VARINDEX> Modifies::getModifiedByStmt(STMTLINE stmtLine) {
	vector<VARINDEX> varList;
	stmtRet = stmt2VarMap.equal_range(stmtLine);
	for(stmtIt = stmtRet.first; stmtIt != stmtRet.second; ++stmtIt) {
		varList.push_back((*stmtIt).second);
	}
	return varList;
}

vector<STMTLINE> Modifies::getModifies(VARINDEX varIndex){
	vector<STMTLINE> stmtList;
	varRet = var2StmtMap.equal_range(varIndex);
	for(varIt = varRet.first; varIt != varRet.second; ++varIt) {
		stmtList.push_back((*varIt).second);
	}
	return stmtList;
}

vector<VARINDEX> Modifies:: getModifiedByStmtWildCard(){
	vector<VARINDEX> varList;
	for(stmtIt = stmt2VarMap.begin(); stmtIt != stmt2VarMap.end(); ++stmtIt) {
		varList.push_back((*stmtIt).second);
	}

	return varList;
}

vector<STMTLINE> Modifies:: getModifiesWildCard(){
	vector<STMTLINE> stmtList;
	for(varIt = var2StmtMap.begin(); varIt != stmt2VarMap.end(); ++varIt) {
		stmtList.push_back((*varIt).first);
	}
	return stmtList;
}
