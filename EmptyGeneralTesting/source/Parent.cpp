#include "Parent.h"
#include <iostream>

/* Constructor & Destructor */
Parent::Parent(void) {
}

Parent::~Parent(void) {
}

void Parent::setParent(STMTLINE parent, STMTLINE child) {
    parentToChild.putRelation(parent, child);
	childToParent[child] = parent;
}

void Parent::setParentStar(STMTLINE parent, STMTLINE child) {
	parentToChildStar.putRelation(parent, child);
    childToParentStar.putRelation(child, parent);
}

bool Parent::isParent(STMTLINE first, STMTLINE second) {
    return parentToChild.containsChild(first, second);
}
bool Parent::isParentStar(STMTLINE first, STMTLINE second) {
    return parentToChildStar.containsChild(first, second);
}

STMTLINE Parent::getParent(STMTLINE child) {
	int parent = childToParent[child];
	return parent == 0 ? -1 : parent;
}

vector<STMTLINE> Parent::getParentStar(STMTLINE child) {
    return childToParentStar.toVector(child);
}

vector<STMTLINE> Parent::getChildOf(STMTLINE parent) {
    return parentToChild.toVector(parent);
}

vector<STMTLINE> Parent::getChildOfStar(STMTLINE parent) {
    return parentToChildStar.toVector(parent);
}