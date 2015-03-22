#include "Parent.h"


/* Constructor & Destructor */
Parent::Parent(void){
}

Parent::~Parent(void)
{
}

bool Parent::setParent(STMTLINE parent, STMTLINE child){
	parent2ChildMap.insert(std::pair<STMTLINE, STMTLINE>(parent, child));
	child2ParentMap.insert(child, parent);
	parent2ChildMapStar.insert(std::pair<STMTLINE, STMTLINE>(parent, child));
	child2ParentMapStar.insert(std::pair<STMTLINE, STMTLINE>(child, parent));
	return true;
}

bool Parent::setParentStar(STMTLINE parent, STMTLINE child){
	parent2ChildMapStar.insert(std::pair<STMTLINE, STMTLINE>(parent, child));
	child2ParentMapStar.insert(std::pair<STMTLINE, STMTLINE>(child, parent));
	return true;
}

bool Parent::isParent(STMTLINE first, STMTLINE second){
	ret = parent2ChildMap.equal_range(first); 
	/* If first is not a parent, return false */
	if(ret.first == ret.second) {
		return false;
	} else {
		for(it = ret.first; it != ret.second; ++it) {
			if((*it).second == second) {
				return true;
			}
		}
		/* second is not found, return false */
		return false;
	}
}
bool Parent::isParentStar(STMTLINE first, STMTLINE second){
	ret = parent2ChildMapStar.equal_range(first); 
	/* If first is not a parent, return false */
	if(ret.first == ret.second) {
		return false;
	} else {
		for(it = ret.first; it != ret.second; ++it) {
			if((*it).second == second) {
				return true;
			}
		}
		/* second is not found, return false */
		return false;
	}
}

STMTLINE Parent::getParent(STMTLINE child){
	it2 = child2ParentMap.find(child);
	if(it2 == child2ParentMap.end()){
		return -1;
	} else {
		return it2->second;
	}
}

vector<STMTLINE> Parent::getParentStar(STMTLINE child){
	vector<STMTLINE> parentList;
	ret = child2ParentMap.equal_range(child);
	for(it = ret.first; it != ret.second; ++it) {
		parentList.push_back((*it).second);
	}
	return parentList;
}

vector<STMTLINE> Parent::getChildOf(STMTLINE parent){
	vector<STMTLINE> childList;
	ret = parent2ChildMap.equal_range(parent);
	for(it = ret.first; it != ret.second; ++it) {
		childList.push_back((*it).second);
	}
	return childList;
}

vector<STMTLINE> Parent::getChildOfStar(STMTLINE parent){
	vector<STMTLINE> childList;
	ret = parent2ChildMapStar.equal_range(parent);
	for(it = ret.first; it != ret.second; ++it) {
		childList.push_back((*it).second);
	}
	return childList;
}

