#include "Modifies.h"


Modifies::Modifies(void)
{
}


bool setModifiesInPROC(PROCINDEX PROCINDEX, VARINDEX VARINDEX){

	return true;
}
bool setModifiesInStmt(STMTLINE stmt, VARINDEX VARINDEX){
	return true;
}
vector<VARINDEX> getModifiedByPROC(PROCINDEX PROCINDEX){
	vector<int> a;
	return a;
}
vector<VARINDEX> getModifiedByStmt(STMTLINE STMTLINE){
vector<int> a;
	return a;
	
}
vector<TNode> getModifies(VARINDEX VARINDEX){
vector<TNode> a;
	return a;

}

Modifies::~Modifies(void)
{
}
