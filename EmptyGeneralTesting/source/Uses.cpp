#include "Uses.h"

/* Constructor & Destructor */
Uses::Uses(void)
{
}

Uses::~Uses(void)
{
}

bool Uses::setUsesStmt(VARINDEX varIndex, STMTLINE stmt){
	//TODO Implement Validation
	var2StmtMap.insert(std::pair<VARINDEX, STMTLINE>(varIndex, stmt));
	stmt2VarMap.insert(std::pair<STMTLINE, VARINDEX>(stmt, varIndex));
	return true;
}

vector<VARINDEX> Uses::getUsedByStmt(STMTLINE stmtLine) {
	vector<VARINDEX> varList;
	stmtRet = stmt2VarMap.equal_range(stmtLine);
	for(stmtIt = stmtRet.first; stmtIt != stmtRet.second; ++stmtIt) {
		varList.push_back((*stmtIt).second);
	}
	return varList;
}

vector<STMTLINE> Uses::getUses(VARINDEX varIndex){
	vector<STMTLINE> stmtList;
	varRet = stmt2VarMap.equal_range(varIndex);
	for(varIt = varRet.first; varIt != varRet.second; ++varIt) {
		stmtList.push_back((*varIt).second);
	}
	return stmtList;
}