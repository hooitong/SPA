#include "BitTable.h"

bool BitTable::containsChild(int parent, int child) {
  std::vector<bool> children = vectorList[parent]; 
  if(vectorList.size() <= child) {
    int diff = child - vectorList.size();
    padVector(children, diff);
    return false;
  } else {
    return children.at(child);
  }
}

std::vector<bool>* BitTable::getChildren(int parent) {
  return &vectorList[parent];
}

void BitTable::putRelation(int parent, int child) {
  std::vector<bool> children = vectorList[parent];
  if(vectorList.size() <= child) {
    int diff = child - vectorList.size();
    padVector(children, diff);
  }
  children[child] = true;
}

/* Pad false values into vector by provided length */
void BitTable::padVector(std::vector<bool> vector, int length) {
  for(int i = 0; i < length; i++) {
    vector.push_back(false);
  }
}

