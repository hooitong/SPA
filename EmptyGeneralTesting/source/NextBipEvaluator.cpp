#include "NextBipEvaluator.h"

NextBipEvaluator::NextBipEvaluator(PKB* pkb) : RelationEvaluator(pkb){}
bool NextBipEvaluator::solveConstConst(const int left, const int right, const QueryResult& result) const
{
    return pkb->getNextBip()->isNext(left, right);
}

vector<int> NextBipEvaluator::solveConstSyn(const int left, const QueryResult& result) const
{
    return pkb->getNextBip()->getNext(left);
}

vector<int> NextBipEvaluator::solveSynConst(const int right, const QueryResult& result) const
{
    return pkb->getNextBip()->getBefore(right);
}

int NextBipEvaluator::getConstLeft(const QNode* const node) const {
    istringstream iss(node->getChildren()[0]->getString());
    int result;
    iss >> result;
    return result;
}

int NextBipEvaluator::getConstRight(const QNode* const node) const {
    istringstream iss(node->getChildren()[1]->getString());
    int result;
    iss >> result;
    return result;
}

bool NextBipEvaluator::checkLeft(const QNode* const node, const int tested) const {
    return synonymToTType(node->getChildren()[0]->getQType()) == STMTN ||
        synonymToTType(node->getChildren()[0]->getQType()) ==
        pkb->getAst()->getTNode(tested)->getTType();
}

bool NextBipEvaluator::checkRight(const QNode* const node, const int tested) const {
    return synonymToTType(node->getChildren()[1]->getQType()) == STMTN ||
        synonymToTType(node->getChildren()[1]->getQType()) ==
        pkb->getAst()->getTNode(tested)->getTType();
}

vector <int> NextBipEvaluator::getAllLeft(const QNode* const node, 
    const QueryResult &result) const {
    if (node->getChildren()[0]->getQType()== ANY) {
        return pkb->getAst()->getStmtLines(STMTN);
    }
    set<int> possibleValues = result.getPossibleValues(node->getChildren()[0]->getString());
    if (possibleValues.size() > 0) {
        return vector<int>(possibleValues.begin(), possibleValues.end());
    }
    return pkb->getAst()->getStmtLines(
        synonymToTType(node->getChildren()[0]->getQType()));
}

vector <int> NextBipEvaluator::getAllRight(const QNode* const node, 
    const QueryResult &result) const {
    if (node->getChildren()[1]->getQType()== ANY) {
        return pkb->getAst()->getStmtLines(STMTN);
    }
    set<int> possibleValues = result.getPossibleValues(node->getChildren()[1]->getString());
    if (possibleValues.size() > 0) {
        return vector<int>(possibleValues.begin(), possibleValues.end());
    }
    return pkb->getAst()->getStmtLines(
        synonymToTType(node->getChildren()[1]->getQType()));
}