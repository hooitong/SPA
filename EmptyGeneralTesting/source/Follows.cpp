#include "Follows.h"

/* Constructor & Destructor */
Follows::Follows(void) {
}

Follows::~Follows(void) {
}

void Follows::setFollows(STMTLINE first, STMTLINE second) {
  rightSiblingMap[first] = second;
  leftSiblingMap[second] = first;
}

void Follows::setFollowsStar(STMTLINE first, STMTLINE second) {
  rightSiblingsMap.putRelation(first, second);
  leftSiblingsMap.putRelation(second, first);
}

bool Follows::isFollows(STMTLINE first, STMTLINE second) {
  it = rightSiblingMap.find(first);
  if (it == rightSiblingMap.end()) {
    return false;
  }
  else {
    if (it->second != second) {
      return false;
    }
    else {
      return true;
    }
  }
}

bool Follows::isFollowsStar(STMTLINE first, STMTLINE second) {
  return rightSiblingsMap.containsChild(first, second);
}

STMTLINE Follows::getFollowedBy(STMTLINE currentLine) {
  it = rightSiblingMap.find(currentLine);
  if (it == rightSiblingMap.end()) {
    return -1;
  }
  else {
    return it->second;
  }
}

STMTLINE Follows::getFollowsFrom(STMTLINE currentLine) {
  it = leftSiblingMap.find(currentLine);
  if (it == leftSiblingMap.end()) {
    return -1;
  }
  else {
    return it->second;
  }
}

vector<STMTLINE> Follows::getFollowedByStar(STMTLINE currentLine) {
  return rightSiblingsMap.toVector(currentLine);
}

vector<STMTLINE> Follows::getFollowsFromStar(STMTLINE currentLine) {
  return leftSiblingsMap.toVector(currentLine);
}