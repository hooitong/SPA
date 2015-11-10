#include "NextBip.h"
#include "PKB.h"

#include <algorithm>
#include <iostream>

void NextBip::setNext(PROGLINE before, PROGLINE next) {
  beforeToNext.putRelation(before, next);
  nextToBefore.putRelation(next, before);
}

bool NextBip::isNext(PROGLINE before, PROGLINE next) {
  return beforeToNext.containsChild(before, next);
}

bool NextBip::isNextStar(PROGLINE before, PROGLINE next) {
  vector<PROGLINE> vec = getNextStar(before);
  return find(vec.begin(), vec.end(), next) != vec.end();
}

bool NextBip::isNextStarRecursive(vector<PROGLINE> &processed, stack<PROGLINE> depth, PROGLINE before, PROGLINE next) {
  return false;
}

vector<PROGLINE> NextBip::getBefore(PROGLINE current) {
  return nextToBefore.toVector(current);
}

vector<PROGLINE> NextBip::getBeforeStar(PROGLINE current) {
  vector<PROGLINE> vec;
  getBeforeStarRecursive(vec, std::stack<PROGLINE>(), current);
  return vec;
}

void NextBip::getBeforeStarRecursive(vector<PROGLINE> &result, stack<PROGLINE> depth, PROGLINE current) {
  vector<PROGLINE> beforeVec = getBefore(current);
  TType currentType = PKB::getPKB()->getAst()->getTNode(current)->getTType();
  vector<PROGLINE> possibleNormalBefore = PKB::getPKB()->getNext()->getBefore(current);
  bool isStartStatement = possibleNormalBefore.empty();

  if (currentType == CALLN) {
    if (!isStartStatement) depth.push(possibleNormalBefore[0]);
    /* Check Cyclic Trap*/
    if (find(result.begin(), result.end(), beforeVec[0]) == result.end()) {
      result.push_back(beforeVec[0]);
      getNextStarRecursive(result, depth, beforeVec[0]);
    }
  }

  else if (isStartStatement && !depth.empty()) {
    PROGLINE returnIndex = depth.top();
    depth.pop();
    /* Check Cyclic Trap*/
    if (find(result.begin(), result.end(), returnIndex) == result.end()) {
      result.push_back(returnIndex);
      getNextStarRecursive(result, depth, returnIndex);
    }
  }

  else {
    for (int i = 0; i < beforeVec.size(); i++) {
      /* Check Cyclic Trap*/
      if (find(result.begin(), result.end(), beforeVec[i]) != result.end()) {
        continue;
      }
      result.push_back(beforeVec[i]);
      getNextStarRecursive(result, depth, beforeVec[i]) ;
    }
  }
}

vector<PROGLINE> NextBip::getNext(PROGLINE current) {
  return beforeToNext.toVector(current);
}

vector<PROGLINE> NextBip::getNextStar(PROGLINE current) {
  vector<PROGLINE> vec;
  getNextStarRecursive(vec, std::stack<PROGLINE>(), current);
  return vec;
}

void NextBip::getNextStarRecursive(vector<PROGLINE> &result, stack<PROGLINE> depth, PROGLINE current) {
  vector<PROGLINE> nextVec = getNext(current);
  TType currentType = PKB::getPKB()->getAst()->getTNode(current)->getTType();
  vector<PROGLINE> possibleNormalNext = PKB::getPKB()->getNext()->getNext(current);
  bool isEndStatement = possibleNormalNext.empty();

  if (currentType == CALLN) {
    if (!isEndStatement) {
      depth.push(possibleNormalNext[0]);
    }

    /* Check Cyclic Trap*/
    if (find(result.begin(), result.end(), nextVec[0]) == result.end()) {
      result.push_back(nextVec[0]);
      getNextStarRecursive(result, depth, nextVec[0]);
    }
  }

  else if (isEndStatement && !depth.empty()) {
    PROGLINE returnIndex = depth.top();
    depth.pop();
    /* Check Cyclic Trap*/
    if (find(result.begin(), result.end(), returnIndex) == result.end()) {
      result.push_back(returnIndex);
      getNextStarRecursive(result, depth, returnIndex);
    }
  }

  else {
    for (int i = 0; i < nextVec.size(); i++) {
      /* Check Cyclic Trap*/
      if (find(result.begin(), result.end(), nextVec[i]) != result.end()) {
        continue;
      }
      result.push_back(nextVec[i]);
      getNextStarRecursive(result, depth, nextVec[i]);
    }
  }
}
