#pragma once

#include <map>
#include <vector>

#include "BitTable.h"
#include "GlobalType.h"
#include "TNode.h"

class Sibling {
private:
  BitTable leftToRightSibling;
  BitTable rightToLeftSibling;

public:
  void setSibling(STMTLINE left, STMTLINE right);
  bool isSibling(STMTLINE first, STMTLINE second);
  bool isSiblingNode(TNode* first, TNode* second);
  vector<STMTLINE> getSiblings(STMTLINE child);
};
