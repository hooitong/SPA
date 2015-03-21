#include "Modifies.h"


Modifies::Modifies(void)
{
}


bool setModifiesInPROC(PROCINDEX PROCINDEX, VARINDEX VARINDEX){
}
bool setModifiesInStmt(STMTLINE stmt, VARINDEX VARINDEX){
}
vector<VARINDEX> getModifiedByPROC(PROCINDEX PROCINDEX){
}
vector<VARINDEX> getModifiedByStmt(STMTLINE STMTLINE){
}
vector<TNode> getModifies(VARINDEX VARINDEX){
}

Modifies::~Modifies(void)
{
}
