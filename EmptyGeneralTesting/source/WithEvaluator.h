#include "PKB.h"
#include "QNode.h"
#include "QueryResult.h"

class WithEvaluator {
 private:
  PKB* pkb;
  bool isConst(QNode* node) const;
 public:
  WithEvaluator(PKB* pkb);
  QueryResult evaluate(QNode* node) const;
  vector<pair<int, string> > getAllOfType(QNode* node) const;
  TType synonymToTType(QNodeType type) const;
};