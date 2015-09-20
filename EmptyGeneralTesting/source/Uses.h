#pragma once

#include <vector>

#include "BitTable.h"
#include "GlobalType.h"

class Uses {
private:
  BitTable varToStmt;
  BitTable stmtToVar;

  BitTable procToVar;
  BitTable varToProc;

public:
  Uses(void);
  ~Uses(void);

  void setUsesStmt(VARINDEX varIndex, STMTLINE stmt);
  void setUsesProc(PROCINDEX procIndex, STMTLINE stmt);
  bool isUsesForStmt(STMTLINE stmt, VARINDEX varIndex);
  bool isUsesForProc(PROCINDEX proc, VARINDEX varIndex);
  vector<VARINDEX> getUsedByStmt(STMTLINE stmt);
  vector<PROCINDEX> getUsedByProc(PROCINDEX proc);
  vector<STMTLINE> getUsesForStmt(VARINDEX varIndex);
  vector<PROCINDEX> getUsesForProc(VARINDEX varIndex);
};
