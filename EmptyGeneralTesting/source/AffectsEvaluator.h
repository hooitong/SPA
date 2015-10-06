#pragma once

#include <PKB.h>
#include <QueryResult.h>
#include <QNode.h>

class AffectsEvaluator {
public:
  AffectsEvaluator(PKB* pkb);
  QueryResult evaluate(QNode* node);

private:
  PKB *pkb;
  bool solveConstConst(const int left, const int right);
  vector<int> solveConstSyn(const int left);
  bool solveConstAny(const int left);

  vector<int> solveSynConst(const int right);
  vector<std::pair<int, int>> solveSynSyn();
  vector<int> solveSynAny();

  bool solveAnyConst(const int right);
  vector<int> solveAnySyn();
  bool solveAnyAny();

  bool findPathToNode(STMTLINE current, STMTLINE end, VARINDEX contextVar, vector<STMTLINE> path);

  int getInteger(QNode* node);
  bool isSynonym(QNodeType type);
  bool isConst(QNodeType type);
  TType synonymToTType(QNodeType type);
};