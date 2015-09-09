#pragma once

#include <vector>

#include "BitTable.h"
#include "GlobalType.h"

class Modifies {
  private:
    BitTable varToStmt;
    BitTable stmtToVar;

	BitTable procToVar;
	BitTable varToProc;

  public:
    Modifies(void);
    ~Modifies(void);

    void setModifiesStmt(VARINDEX varIndex, STMTLINE stmt);
	void setModifiesProc(PROCINDEX procIndex, VARINDEX varIndex);
    vector<VARINDEX> getModifiedByStmt(STMTLINE stmtLine);
	vector<VARINDEX> getModifiedByProc(PROCINDEX procIndex);
    vector<STMTLINE> getModifies(VARINDEX varIndex);
};