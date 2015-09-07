#include "BitTable.h"
#include <iostream>

bool BitTable::containsChild(int parent, int child) {
  std::vector<bool> *children = &vectorList[parent]; 
  if(children->size() <= child) {
    int diff = child - (children->size() - 1);
    padVector(children, diff);
    return false;
  } else {
    return children->at(child);
  }
}

std::vector<bool>* BitTable::getChildren(int parent) {
  return &vectorList[parent];
}

void BitTable::putRelation(int parent, int child) {
  std::vector<bool> *children = &vectorList[parent];
  if(children->size() <= child) {
    int diff = child - (children->size() - 1);
    padVector(children, diff);
  }
  children->at(child) = true;
}

/* Pad false values into vector by provided length */
void BitTable::padVector(std::vector<bool> *vector, int length) {
  for(int i = 0; i < length; i++) {
    vector->push_back(false);
  }
}

std::vector<int> BitTable::toVector(int parent) {
  /* Naive O(n) implementation */
  std::vector<int> converted;
  std::vector<bool> children = vectorList[parent];
  for (std::vector<bool>::iterator it = children.begin() ; it != children.end(); ++it) {
     if(*it) converted.push_back(it - children.begin());
  }
  return converted;
}