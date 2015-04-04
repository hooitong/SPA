#include "Follows.h"

/* Constructor & Destructor */
Follows::Follows(void) {
}

Follows::~Follows(void) {
}

bool Follows::setFollows(STMTLINE first, STMTLINE second) {
    rightSiblingMap[first] = second;
    leftSiblingMap[second] = first;
    return true;
}

bool Follows::setFollowsStar(STMTLINE first, STMTLINE second) {
    rightSiblingsMap.insert(std::pair<STMTLINE, STMTLINE>(first, second));
    leftSiblingsMap.insert(std::pair<STMTLINE, STMTLINE>(second, first));
    return true;
}

bool Follows::isFollows(STMTLINE first, STMTLINE second) {
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

bool Follows::isFollowsStar(STMTLINE first, STMTLINE second) {
    ret = rightSiblingsMap.equal_range(first);
    /* If first is not a parent, return false */
    if(ret.first == ret.second) {
        return false;
    } else {
        for(it2 = ret.first; it2 != ret.second; ++it2) {
            if((*it2).second == second) {
                return true;
            }
        }
        /* second is not found, return false */
        return false;
    }
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
    vector<STMTLINE> rightSiblings;
    ret = rightSiblingsMap.equal_range(currentLine);
    for(it2 = ret.first; it2 != ret.second; ++it2) {
        rightSiblings.push_back((*it2).second);
    }
    return rightSiblings;
}

vector<STMTLINE> Follows::getFollowsFromStar(STMTLINE currentLine) {
    vector<STMTLINE> leftSiblings;
    ret = leftSiblingsMap.equal_range(currentLine);
    for(it2 = ret.first; it2 != ret.second; ++it2) {
        leftSiblings.push_back((*it2).second);
    }
    return leftSiblings;
}