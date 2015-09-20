#include "Calls.h"

Calls::Calls() {

}

Calls::~Calls() {

}

void Calls::setCalls(PROCINDEX caller, PROCINDEX called) {
  callerToCalled.putRelation(caller, called);
  calledToCaller.putRelation(called, caller);
}

void Calls::setCallsStar(PROCINDEX caller, PROCINDEX called) {
  callerToCalledStar.putRelation(caller, called);
  calledToCallerStar.putRelation(called, caller);
}

bool Calls::isCall(PROCINDEX caller, PROCINDEX called) {
  return callerToCalled.containsChild(caller, called);
}

bool Calls::isCallStar(PROCINDEX caller, PROCINDEX called) {
  return callerToCalledStar.containsChild(caller, called);
}

vector<PROCINDEX> Calls::getCalledBy(PROCINDEX caller) {
  return callerToCalled.toVector(caller);
}

vector<PROCINDEX> Calls::getCalledByStar(PROCINDEX caller) {
  return callerToCalledStar.toVector(caller);
}

vector<PROCINDEX> Calls::getCallsTo(PROCINDEX called) {
  return calledToCaller.toVector(called);
}

vector<PROCINDEX> Calls::getCallsToStar(PROCINDEX called) {
  return calledToCallerStar.toVector(called);
}