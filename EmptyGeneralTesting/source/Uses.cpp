#include "Uses.h"


Uses::Uses(void)
{
}

bool setUsesInPROC(PROCINDEX PROCINDEX, VARINDEX VARINDEX){

	return true;
}
bool setUsesInStmt(STMTLINE STMTLINE, VARINDEX VARINDEX){
	return true;
}
vector<VARINDEX> getUsedByPROC (PROCINDEX PROCINDEX){
	vector<int> a;
	return a;
}
vector<VARINDEX> getUsedByStmt (STMTLINE STMTLINE){
	vector<int> a;
	return a;
}
vector<TNode> getUses(VARINDEX VARINDEX){
	vector<TNode> a;
	return a;
}


Uses::~Uses(void)
{
}
