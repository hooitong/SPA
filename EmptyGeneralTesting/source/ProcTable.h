#pragma once

#include <vector>
#include <map>

#include "GlobalType.h"

struct procInfo {
    PROCINDEX proc_index;
    PROCNAME proc_name;
};

class ProcTable {
  private:
    map<PROCINDEX, procInfo> procIndexMap;
    map<PROCNAME, procInfo> procNameMap;
    PROCINDEX currentMapIndex;

  public:
    ProcTable(void);
    ~ProcTable(void);

    PROCINDEX insertProc(PROCNAME procName);
    PROCNAME getProcName(PROCINDEX procIndex);
    PROCINDEX getProcIndex(PROCNAME procName);
    int getSize();
    vector<VARINDEX> getAllProcIndex();
    vector<VARNAME> getAllProcName();

	void setGRoot(PROCINDEX index, GNode node);
};
