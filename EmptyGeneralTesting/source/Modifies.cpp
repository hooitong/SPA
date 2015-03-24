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
	VarTable::addModifiedBy(varIndex, stmt);
	stmt2VarMap.insert(std::pair<STMTLINE, VARINDEX>(stmt, varIndex));
	return true;
}

vector<VARINDEX> Modifies::getModifiedByStmt(STMTLINE stmtLine) {
	vector<STMTLINE> varList;
	ret = stmt2VarMap.equal_range(stmtLine);
	for(it = ret.first; it != ret.second; ++it) {
		varList.push_back((*it).second);
	}
	return varList;
}

vector<STMTLINE> Modifies::getModifies(VARINDEX varIndex){
	return VarTable::getModifiedBy(varIndex);
}

vector<VARINDEX> Modifies:: getModifiedByStmtWildCard(){
	vector<VARINDEX> varList;
	for(it = stmt2VarMap.begin(); it != stmt2VarMap.end(); ++it) {
		varList.push_back((*it).second);
	}
	return varList;
}

vector<STMTLINE> Modifies:: getModifesWildCard(){
	vector<STMTLINE> stmtList;
	for(it = stmt2VarMap.begin(); it != stmt2VarMap.end(); ++it) {
		stmtList.push_back((*it).first);
	}
}