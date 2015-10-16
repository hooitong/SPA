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

  /* Helper recursive methods to confirm Affects relations */
  bool findConstToConst(STMTLINE current, STMTLINE end, VARINDEX contextVar, vector<STMTLINE> path);
  bool findSynonymFromConst(STMTLINE current, VARINDEX contextVar, set<STMTLINE> *candidates, vector<STMTLINE> path, bool takeAny);
  bool findSynonymToConst(STMTLINE current, VARINDEX contextVar, set<STMTLINE> *candidates, vector<STMTLINE> path, bool takeAny);

  int getInteger(QNode* node);
  bool isSynonym(QNodeType type);
  bool isConst(QNodeType type);
  bool isValidAssign(STMTLINE current, VARINDEX contextVar, bool isLeft);
  vector<int>* removeDuplicate(vector<int> *v);
};