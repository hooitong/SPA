#pragma once

#include <vector>
#include <map>

#include "GlobalType.h"

class Calls {
  private:
	std::multimap<PROCINDEX,PROCINDEX> procCalls;
    std::multimap<PROCINDEX,PROCINDEX>::iterator procIt;//need to check
    std::pair <std::multimap<PROCINDEX,PROCINDEX>::iterator, std::multimap<PROCINDEX,PROCINDEX>::iterator> procRet;//need to check

  public:
    Calls(void);
    ~Calls(void);

	void setProcCalls(PROCINDEX procIndexCalls, PROCINDEX procIndexCalled);
    vector<VARINDEX> getCalledByProc(PROCINDEX procIndex);
    vector<STMTLINE> getCalls(PROCINDEX procIndex);

};
