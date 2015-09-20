#pragma once

#include "BitTable.h"
#include "GlobalType.h"
class Calls {
private:
  BitTable callerToCalled;
  BitTable calledToCaller;
  BitTable callerToCalledStar;
  BitTable calledToCallerStar;

public:
  Calls(void);
  ~Calls(void);

  void setCalls(PROCINDEX caller, PROCINDEX called);
  void setCallsStar(PROCINDEX caller, PROCINDEX called);
  bool isCall(PROCINDEX caller, PROCINDEX called);
  bool isCallStar(PROCINDEX caller, PROCINDEX called);
  vector<PROCINDEX> getCalledBy(PROCINDEX caller);
  vector<PROCINDEX> getCalledByStar(PROCINDEX caller);
  vector<PROCINDEX> getCallsTo(PROCINDEX called);
  vector<PROCINDEX> getCallsToStar(PROCINDEX called);
};
