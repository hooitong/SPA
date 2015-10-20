#include <FollowsStarEvaluator.h>

FollowsStarEvaluator::FollowsStarEvaluator(PKB* pkb) : RelationEvaluator(pkb){}
bool FollowsStarEvaluator::solveConstConst(const int left, const int right, const QueryResult& result) const
{
    return pkb->getFollows()->isFollowsStar(left, right);
}

vector<int> FollowsStarEvaluator::solveConstSyn(const int left, const QueryResult& result) const
{
    return pkb->getFollows()->getFollowedByStar(left);
}

vector<int> FollowsStarEvaluator::solveSynConst(const int right, const QueryResult& result) const
{
    return pkb->getFollows()->getFollowsFromStar(right);
}

int FollowsStarEvaluator::getConstLeft(const QNode* const node) const {
    istringstream iss(node->getChildren()[0]->getString());
    int result;
    iss >> result;
    return result;
}

int FollowsStarEvaluator::getConstRight(const QNode* const node) const {
    istringstream iss(node->getChildren()[1]->getString());
    int result;
    iss >> result;
    return result;
}

bool FollowsStarEvaluator::checkLeft(const QNode* const node, const int tested) const {
    return node->getChildren()[0]->getQType() == STMTSYNONYM ||
        synonymToTType(node->getChildren()[0]->getQType()) ==
        pkb->getAst()->getTNode(tested)->getTType();
}

bool FollowsStarEvaluator::checkRight(const QNode* const node, const int tested) const {
    return node->getChildren()[1]->getQType() == STMTSYNONYM ||
        synonymToTType(node->getChildren()[1]->getQType()) ==
        pkb->getAst()->getTNode(tested)->getTType();
}

vector <int> FollowsStarEvaluator::getAllLeft(const QNode* const node, 
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

vector <int> FollowsStarEvaluator::getAllRight(const QNode* const node, 
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