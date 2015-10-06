#include "ConstTable.h"

#include <algorithm>

/* Constructor & Destructor */
ConstTable::ConstTable() {
}

ConstTable::~ConstTable() {
}

void ConstTable::insertConst(CONSTVALUE constValue) {
  constTable.push_back(constValue);
}

bool ConstTable::isContains(CONSTVALUE constValue) {
  return std::find(constTable.begin(), constTable.end(), constValue) != constTable.end();
}

vector<CONSTVALUE> ConstTable::getAllConstValue() {
  return constTable;
}