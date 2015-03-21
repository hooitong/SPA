#include "Modifies.h"


Modifies::Modifies(void)
{
}


bool setModifiesInProc(ProcIndex ProcIndex, VarIndex VarIndex){
}
bool setModifiesInStmt(STMTLine stmt, VarIndex VarIndex){
}
vector<VarIndex> getModifiedByProc(ProcIndex ProcIndex){
}
vector<VarIndex> getModifiedByStmt(STMTLine stmtLine){
}
vector<TNode> getModifies(VarIndex VarIndex){
}

Modifies::~Modifies(void)
{
}
