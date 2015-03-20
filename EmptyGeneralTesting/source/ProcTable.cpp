#include "ProcTable.h"

//constructor
ProcTable::ProcTable(void)
{
}

PROCINDEX insertProc(PROCNAME procName){
}

PROCINDEX getProcINdex(PROCNAME procName){
}
PROCNAME getProcName(PROCINDEX procIndex){
}
vector<PROCNAME> getAllProc(){
}
bool setTRoot(PROCINDEX index, TNode node){
}
bool setGRoot(PROCINDEX index, GNode node){
}
TNode getTRoot(PROCINDEX index){
}
GNode getGNode(PROCINDEX index){
}
bool addModified(PROCINDEX proc, VARINDEX var){
}
bool addUsed(PROCINDEX proc, VARINDEX var){
}
vector<VARINDEX> getModified(PROCINDEX proc){
}
vector<VARINDEX> getUsed(PROCINDEX proc){
}

//destructor
ProcTable::~ProcTable(void)
{
}
