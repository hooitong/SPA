#pragma once

#include <vector>
#include <map>

#include "GlobalType.h"

struct varInfo {
  VARINDEX var_index;
  VARNAME var_name;
};

class VarTable {
private:
  map<VARINDEX, varInfo> varIndexMap;
  map<VARNAME, varInfo> varNameMap;
  VARINDEX currentMapIndex;

public:
  VarTable(void);
  ~VarTable(void);

  VARINDEX insertVar(VARNAME varName);
  VARNAME getVarName(VARINDEX varIndex);
  VARINDEX getVarIndex(VARNAME varName);
  int getSize();
  vector<VARINDEX> getAllVarIndex();
  vector<VARNAME> getAllVarName();
};