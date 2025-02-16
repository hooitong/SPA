#pragma once

#include <vector>
#include <map>

#include "GlobalType.h"

class TNode;
class GNode;

struct procInfo {
  PROCINDEX proc_index;
  PROCNAME proc_name;
  TNode * astRoot;
};

class ProcTable {
private:
  map<PROCINDEX, procInfo*> procIndexMap;
  map<PROCNAME, procInfo*> procNameMap;
  PROCINDEX currentMapIndex;

public:
  ProcTable(void);
  ~ProcTable(void);

  PROCINDEX insertProc(PROCNAME procName);
  PROCNAME getProcName(PROCINDEX procIndex);
  PROCINDEX getProcIndex(PROCNAME procName);
  vector<VARINDEX> getAllProcIndex();
  vector<VARNAME> getAllProcName();
  int getSize();
  void setTRoot(PROCINDEX index, TNode * node);
  TNode* getTRoot(PROCINDEX index);
  vector<TNode*> getAllTRoot();
};
