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
    vector<VARINDEX> getUsedByStmt(STMTLINE stmtLine);
	vector<PROCINDEX> getUsedByProc(PROCINDEX proc);
    vector<STMTLINE> getUses(VARINDEX varIndex);
};
