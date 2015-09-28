#include "PKB.h"
#include "QNode.h"
#include "QueryResult.h"

class WithEvaluator {
 private:
  PKB* pkb;
  bool isConst(QNode* node);
 public:
  WithEvaluator(PKB* pkb);
  QueryResult evaluate(QNode* node);
  vector<pair<int, string> > getAllOfType(QNode* node);
};