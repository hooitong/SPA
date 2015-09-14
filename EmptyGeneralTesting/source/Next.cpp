#include "Next.h"

void Next::setNext(PROGLINE before, PROGLINE next) {
	beforeToNext[before] = next;
	nextToBefore[next] = before;
}

void Next::setNextStar(PROGLINE before, PROGLINE next) {
	beforeToAfter.putRelation(before, next);
	afterToBefore.putRelation(next, before);
}

bool Next::isNext(PROGLINE before, PROGLINE next) {
	return beforeToNext[before] == next;
}

bool Next::isNextStar(PROGLINE before, PROGLINE next) {
	return beforeToAfter.containsChild(before, next);
}

PROGLINE Next::getBefore(PROGLINE current) {
	int before = nextToBefore[current];
	return before == 0 ? -1 : before;
}

vector<PROGLINE> Next::getBeforeStar(PROGLINE current) {
	return afterToBefore.toVector(current);
}

PROGLINE Next::getNext(PROGLINE current) {
	int next = beforeToNext[current];
	return next == 0 ? -1 : next;
}

vector<PROGLINE> Next::getNextStar(PROGLINE current) {
	return beforeToAfter.toVector(current);
}