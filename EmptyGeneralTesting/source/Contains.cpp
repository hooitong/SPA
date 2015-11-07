#include "Contains.h"
#include <iostream>

void Contains::setContains(STMTLINE parent, STMTLINE child) {
	this->setParent(parent, child);
}

void Contains::setContainsStar(STMTLINE parent, STMTLINE child) {
	this->setParentStar(parent, child);
}

bool Contains::isContains(STMTLINE first, STMTLINE second) {
  return this->isParent(first, second);
}
bool Contains::isContainsStar(STMTLINE first, STMTLINE second) {
	return this->isParentStar(first, second);
}

STMTLINE Contains::getContainParent(STMTLINE child) {
	return this->getParent(child);
}

vector<STMTLINE> Contains::getContainParentStar(STMTLINE child) {
	return this->getParentStar(child);
}

vector<STMTLINE> Contains::getContains(STMTLINE parent) {
  return this->getChildOf(parent);
}

vector<STMTLINE> Contains::getContainsStar(STMTLINE parent) {
  return this->getChildOfStar(parent);
}

bool Contains::isContainsNode(TNode* parent, TNode* child){
	vector<TNode*> result;
	parent->getAllChildrenIncludeSubByTType(result, child->getTType());
	for(int i =0; i < result.size(); i ++){
		if(result[i]== child){
			return true;
		}
	}
	return false;
}