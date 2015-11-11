#include "NextStarEvaluator.h"

NextStarEvaluator::NextStarEvaluator(PKB* pkb) : RelationEvaluator(pkb){}
bool NextStarEvaluator::solveConstConst(const int left, const int right, const QueryResult& result) const
{
    return pkb->getNext()->isNextStar(left, right);
}

vector<int> NextStarEvaluator::solveConstSyn(const int left, const QueryResult& result) const
{
    return pkb->getNext()->getNextStar(left);
}

vector<int> NextStarEvaluator::solveSynConst(const int right, const QueryResult& result) const
{
    return pkb->getNext()->getBeforeStar(right);
}

int NextStarEvaluator::getConstLeft(const QNode* const node) const {
    istringstream iss(node->getChildren()[0]->getString());
    int result;
    iss >> result;
    return result;
}

int NextStarEvaluator::getConstRight(const QNode* const node) const {
    istringstream iss(node->getChildren()[1]->getString());
    int result;
    iss >> result;
    return result;
}

bool NextStarEvaluator::checkLeft(const QNode* const node, const int tested) const {
    return synonymToTType(node->getChildren()[0]->getQType()) == STMTN ||
        synonymToTType(node->getChildren()[0]->getQType()) ==
        pkb->getAst()->getTNode(tested)->getTType();
}

bool NextStarEvaluator::checkRight(const QNode* const node, const int tested) const {
    return synonymToTType(node->getChildren()[1]->getQType()) == STMTN ||
        synonymToTType(node->getChildren()[1]->getQType()) ==
        pkb->getAst()->getTNode(tested)->getTType();
}

vector <int> NextStarEvaluator::getAllLeft(const QNode* const node, 
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

vector <int> NextStarEvaluator::getAllRight(const QNode* const node, 
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