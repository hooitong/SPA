#include "Modifies.h"


Modifies::Modifies(void)
{
}


bool setModifiesInProc(PROCINDEX procIndex, VARINDEX varIndex){
}
bool setModifiesInStmt(STMTLine stmt, VARINDEX varIndex){
}
vector<VARINDEX> getModifiedByProc(PROCINDEX procIndex){
}
vector<VARINDEX> getModifiedByStmt(STMTLine stmtLine){
}
vector<TNode> getModifies(VARINDEX varIndex){
}

Modifies::~Modifies(void)
{
}
