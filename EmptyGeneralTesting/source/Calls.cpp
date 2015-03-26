#include "Calls.h"

typedef int PROCINDEX;

Calls::Calls(void) {
}

bool setCalls(PROCINDEX caller, PROCINDEX called) {
    return true;
}
bool isCall(PROCINDEX caller, PROCINDEX called) {
    return true;
}
bool isCallStar(PROCINDEX caller, PROCINDEX called) {
    return true;
}
vector<TNode> getCalledBy(PROCINDEX caller) {
    vector<TNode> t;
    return t;
}
vector<TNode> getCalledByStar(PROCINDEX called) {
    vector<TNode> t;
    return t;
}
vector<TNode> getCallsToStar(PROCINDEX called) {
    vector<TNode> t;
    return t;
}

Calls::~Calls(void) {
}