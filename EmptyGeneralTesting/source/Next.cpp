#include "Next.h"
#include <algorithm>

void Next::setNext(PROGLINE before, PROGLINE next) {
  beforeToNext.putRelation(before, next);
  nextToBefore.putRelation(next, before);
}

bool Next::isNext(PROGLINE before, PROGLINE next) {
  return beforeToNext.containsChild(before, next);
}

bool Next::isNextStar(PROGLINE before, PROGLINE next) {
	vector<PROGLINE> vec;
	bool result = isNextStarRecursive(vec, before, next);
	if(!result) notNextStarCache.putRelation(before, next);
	return result;
}

bool Next::isNextStarRecursive(vector<PROGLINE> &processed, PROGLINE before, PROGLINE next){

	vector<PROGLINE> isNextStarCacheVec = isNextStarCache.toVector(before);
	if(std::find(isNextStarCacheVec.begin(), isNextStarCacheVec.end(), next) != isNextStarCacheVec.end()){
		return true;
	}
	vector<PROGLINE> notNextStarCacheVec = notNextStarCache.toVector(before);
	if(std::find(notNextStarCacheVec.begin(), notNextStarCacheVec.end(), next) != notNextStarCacheVec.end()){
		return false;
	}

	vector<PROGLINE> nextVec = getNext(before);
	for(int i =0; i<nextVec.size(); i ++){
		if(nextVec[i] == next){
			isNextStarCache.putRelation(before, next);
			return true;
		}
		else if(find(processed.begin(), processed.end(), nextVec[i]) != processed.end()){
			continue;
		}
		else{
			processed.push_back(nextVec[i]); //to make sure it won't get processed again, 
											 //that end up infinite looping
			if(isNextStarRecursive(processed, nextVec[i], next)) return true;
		}
	}
	return false;
}

vector<PROGLINE> Next::getBefore(PROGLINE current) {
  return nextToBefore.toVector(current);
}

vector<PROGLINE> Next::getBeforeStar(PROGLINE current) {
   vector<PROGLINE> vec;
   getBeforeStarRecursive(vec, current);
   return vec;
}

void Next::getBeforeStarRecursive(vector<PROGLINE> &result, PROGLINE current){
	vector<PROGLINE> beforeVec = getBefore(current);
	for(int i = 0; i < beforeVec.size(); i++){
		if(find(result.begin(), result.end(), beforeVec[i]) != result.end()){
			continue;
		}
		else{
			result.push_back(beforeVec[i]);
			getBeforeStarRecursive(result, beforeVec[i]);
		}
	}
}

vector<PROGLINE> Next::getNext(PROGLINE current) {
  return beforeToNext.toVector(current);
}

vector<PROGLINE> Next::getNextStar(PROGLINE current) {
   vector<PROGLINE> vec;
   getNextStarRecursive(vec, current);
   return vec;
}

void Next::getNextStarRecursive(vector<PROGLINE> &result, PROGLINE current){
	vector<PROGLINE> nextVec = getNext(current);
	for(int i = 0; i < nextVec.size(); i++){
		if(find(result.begin(), result.end(), nextVec[i]) != result.end()){
			continue;
		}
		else{
			result.push_back(nextVec[i]);
			getNextStarRecursive(result, nextVec[i]);
		}
	}
}
