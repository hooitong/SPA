#pragma once

#include "GlobalType.h"

#include <vector>

class ConstTable {

private:
  vector<CONSTVALUE> constTable;

public:
  ConstTable(void);
  ~ConstTable(void);

  void insertConst(CONSTVALUE constValue);
  bool isContains(CONSTVALUE constValue);
  vector<CONSTVALUE> getAllConstValue();
};