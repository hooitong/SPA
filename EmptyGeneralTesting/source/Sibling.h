#pragma once

#include <map>
#include <vector>

#include "BitTable.h"
#include "GlobalType.h"

class Sibling {
private:
  BitTable leftToRightSibling;
  BitTable rightToLeftSibling;

public:
  void setSibling(STMTLINE left, STMTLINE right);
  bool isSibling(STMTLINE first, STMTLINE second);
  vector<STMTLINE> getSiblings(STMTLINE child);
};
