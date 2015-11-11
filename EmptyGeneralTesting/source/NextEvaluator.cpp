#include "NextEvaluator.h"

NextEvaluator::NextEvaluator(PKB* pkb) : RelationEvaluator(pkb){}
bool NextEvaluator::solveConstConst(const int left, const int right, const QueryResult& result) const
{
    return pkb->getNext()->isNext(left, right);
}

vector<int> NextEvaluator::solveConstSyn(const int left, const QueryResult& result) const
{
    return pkb->getNext()->getNext(left);
}

vector<int> NextEvaluator::solveSynConst(const int right, const QueryResult& result) const
{
    return pkb->getNext()->getBefore(right);
}

int NextEvaluator::getConstLeft(const QNode* const node) const {
    istringstream iss(node->getChildren()[0]->getString());
    int result;
    iss >> result;
    return result;
}

int NextEvaluator::getConstRight(const QNode* const node) const {
    istringstream iss(node->getChildren()[1]->getString());
    int result;
    iss >> result;
    return result;
}

bool NextEvaluator::checkLeft(const QNode* const node, const int tested) const {
    return synonymToTType(node->getChildren()[0]->getQType()) == STMTN ||
        synonymToTType(node->getChildren()[0]->getQType()) ==
        pkb->getAst()->getTNode(tested)->getTType();
}

bool NextEvaluator::checkRight(const QNode* const node, const int tested) const {
    return synonymToTType(node->getChildren()[1]->getQType()) == STMTN ||
        synonymToTType(node->getChildren()[1]->getQType()) ==
        pkb->getAst()->getTNode(tested)->getTType();
}

vector <int> NextEvaluator::getAllLeft(const QNode* const node, 
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

vector <int> NextEvaluator::getAllRight(const QNode* const node, 
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