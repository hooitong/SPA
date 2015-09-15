#include "Next.h"

void Next::setNext(PROGLINE before, PROGLINE next) {
	beforeToNext.putRelation(before, next);
	nextToBefore.putRelation(next, before);
}

void Next::setNextStar(PROGLINE before, PROGLINE next) {
	beforeToAfter.putRelation(before, next);
	afterToBefore.putRelation(next, before);
}

bool Next::isNext(PROGLINE before, PROGLINE next) {
	return beforeToNext.containsChild(before, next);
}

bool Next::isNextStar(PROGLINE before, PROGLINE next) {
	return beforeToAfter.containsChild(before, next);
}

vector<PROGLINE> Next::getBefore(PROGLINE current) {
	return nextToBefore.toVector(current);
}

vector<PROGLINE> Next::getBeforeStar(PROGLINE current) {
	return afterToBefore.toVector(current);
}

vector<PROGLINE> Next::getNext(PROGLINE current) {
	return beforeToNext.toVector(current);
}

vector<PROGLINE> Next::getNextStar(PROGLINE current) {
	return beforeToAfter.toVector(current);
}