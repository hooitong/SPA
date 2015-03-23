#include "Uses.h"
#include "VarTable.h"

/* Constructor & Destructor */
Uses::Uses(void)
{
}

Uses::~Uses(void)
{
}

bool Uses::setUsesStmt(VARINDEX varIndex, STMTLINE stmt){
	//TODO Implement Validation
	VarTable::addUsedBy(varIndex, stmt);
	stmt2VarMap.insert(std::pair<STMTLINE, VARINDEX>(stmt, varIndex));
	return true;
}

vector<VARINDEX> Uses::getUsedByStmt(STMTLINE stmtLine) {
	vector<STMTLINE> varList;
	ret = stmt2VarMap.equal_range(stmtLine);
	for(it = ret.first; it != ret.second; ++it) {
		varList.push_back((*it).second);
	}
	return varList;
}

vector<STMTLINE> Uses::getUses(VARINDEX varIndex){
	return VarTable::getUsedBy(varIndex);
}