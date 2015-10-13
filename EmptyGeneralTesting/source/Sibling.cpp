#include "Sibling.h"
#include <iostream>
#include <algorithm>

void Sibling::setSibling(STMTLINE left, STMTLINE right){
	leftToRightSibling.putRelation(left, right);
	rightToLeftSibling.putRelation(right, left);
}

bool Sibling::isSibling(STMTLINE first, STMTLINE second) {
	return (leftToRightSibling.containsChild(first,second) || leftToRightSibling.containsChild(second, first));
}


vector<STMTLINE> Sibling::getSiblings(STMTLINE child) {
	vector<STMTLINE> result1;
	vector<STMTLINE> result2;

	result1 = leftToRightSibling.toVector(child);
	result2 = rightToLeftSibling.toVector(child);

	for(int i = 0; i< result2.size(); i++){
		if(find(result1.begin(), result1.end(), result2[i]) == result1.end()){
			result1.push_back(result2[i]);
		}
	}

	return result1;
}
