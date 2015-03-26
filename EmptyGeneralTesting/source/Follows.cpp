#include "Follows.h"

/* Constructor & Destructor */
Follows::Follows(void) {
}

Follows::~Follows(void) {
}

bool Follows::setFollows(STMTLINE first, STMTLINE second) {
    leftSiblingMap[first] = second;
    rightSiblingMap[second] = first;
    return true;
}

bool Follows::isFollow(STMTLINE first, STMTLINE second) {
    it = rightSiblingMap.find(first);
    if(it == rightSiblingMap.end()) {
        return false;
    } else {
        if(it->second != second) {
            return false;
        } else {
            return true;
        }
    }
}

bool Follows::isFollowStar(STMTLINE first, STMTLINE second) {
    STMTLINE current = first;
    do {
        it = rightSiblingMap.find(current);
        if(it == rightSiblingMap.end()) {
            return false;
        } else {
            current = it->second;
        }
    } while(current != second);
    return true;
}

STMTLINE Follows::getFollowedBy(STMTLINE currentLine) {
    it = rightSiblingMap.find(currentLine);
    if(it == rightSiblingMap.end()) {
        return -1;
    } else {
        return it->second;
    }
}

STMTLINE Follows::getFollowsFrom(STMTLINE currentLine) {
    it = leftSiblingMap.find(currentLine);
    if(it == leftSiblingMap.end()) {
        return -1;
    } else {
        return it->second;
    }
}

vector<STMTLINE> Follows::getFollowedByStar(STMTLINE currentLine) {
    vector<STMTLINE> followedByList;
    STMTLINE current = currentLine;
    while((it = rightSiblingMap.find(current)) != rightSiblingMap.end()) {
        followedByList.push_back(it->second);
        current = it->second;
    }
    return followedByList;
}

vector<STMTLINE> Follows::getFollowsFromStar(STMTLINE currentLine) {
    vector<STMTLINE> followedFromList;
    STMTLINE current = currentLine;
    while((it = leftSiblingMap.find(current)) != leftSiblingMap.end()) {
        followedFromList.push_back(it->second);
        current = it->second;
    }
    return followedFromList;
}