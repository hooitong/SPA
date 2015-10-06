#pragma once

#include <PKB.h>
#include <QueryResult.h>
#include <QNode.h>
#include "RelationEvaluator.h"

class AffectsEvaluator : public RelationEvaluator {
public:
  AffectsEvaluator(PKB* pkb);
  QueryResult evaluate(QNode* node, const QueryResult& result);

private:
  bool solveConstConst(const int left, const int right, const QueryResult& result);
  vector<int> solveConstSyn(const int left, const QueryResult& result);
  bool solveConstAny(const int left, const QueryResult& result);

  vector<int> solveSynConst(const int right, const QueryResult& result);
  vector<std::pair<int, int>> solveSynSyn(const QueryResult& result);
  vector<int> solveSynAny(const QueryResult& result);

  bool solveAnyConst(const int right, const QueryResult& result);
  vector<int> solveAnySyn(const QueryResult& result);
  bool solveAnyAny(const QueryResult& result);

  bool findPathToNode(STMTLINE current, STMTLINE end, VARINDEX contextVar, vector<STMTLINE> path);
};