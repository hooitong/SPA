#include "ProcTable.h"

/* Constructor & Destructor */
ProcTable::ProcTable(void) {
    currentMapIndex = 0;
}

ProcTable::~ProcTable(void) {
}

PROCINDEX ProcTable::insertProc(PROCNAME procName) {
    PROCINDEX p = getProcIndex(procName);
    /* if procName already exist in procTable, return index */
    if(p != -1) {
        return p;
    }

    /* Create new procInfo and insert into both index and name maps */
    procInfo * procedure = new procInfo;
    procedure->proc_name = procName;
    procedure->proc_index = currentMapIndex;
    procIndexMap[currentMapIndex] = procedure;
    procNameMap[procName] = procedure;

    /* Increment the static index */
    PROCINDEX newIndex = currentMapIndex++;
    return newIndex;
}

PROCNAME ProcTable::getProcName(PROCINDEX procIndex) {
    /* Check if procIndex is valid */
    if(procIndex < 0 || procIndex >= currentMapIndex) {
        return "!Invalid!";
    } else {
        return procIndexMap[procIndex]->proc_name;
    }
}

PROCINDEX ProcTable::getProcIndex(PROCNAME procName) {
    map<PROCNAME, procInfo*>::iterator itr = procNameMap.find(procName);
    if(itr != procNameMap.end()) {
        return itr->second->proc_index;
    } else {
        return -1;
    }
}

vector<PROCINDEX> ProcTable::getAllProcIndex() {
    vector<PROCINDEX> listOfProcIndex;
    for(int i = 0; i < currentMapIndex; i++) {
        listOfProcIndex.push_back(i);
    }
    return listOfProcIndex;
}

vector<PROCNAME> ProcTable::getAllProcName() {
    vector<PROCNAME> listOfProcName;
    for(int i = 0; i < currentMapIndex; i++) {
        listOfProcName.push_back(procIndexMap[i]->proc_name);
    }
    return listOfProcName;
}

int ProcTable::getSize() {
	return currentMapIndex;
}

void ProcTable::setTRoot(PROCINDEX index, TNode * node) {
	procIndexMap[index]->astRoot = node;
}

TNode* ProcTable::getTRoot(PROCINDEX index) {
	return procIndexMap[index]->astRoot;
}