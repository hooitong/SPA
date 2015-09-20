#include <FollowsEvaluator.h>

FollowsEvaluator::FollowsEvaluator(PKB* pkb) : RelationEvaluator(pkb){}
bool FollowsEvaluator::solveConstConst(const int left, const int right, const QueryResult& result) const
{
    return pkb->getFollows()->isFollows(left, right);
}

vector<int> FollowsEvaluator::solveConstSyn(const int left, const QueryResult& result) const
{
    int newResult = pkb->getFollows()->getFollowedBy(left);
    if (newResult < 0) {
        return vector<int>();
    } else {
        return vector<int>(1, newResult);
    }
}

vector<int> FollowsEvaluator::solveSynConst(const int right, const QueryResult& result) const
{
    int newResult = pkb->getFollows()->getFollowsFrom(right);
    if (newResult < 0) {
        return vector<int>();
    } else {
        return vector<int>(1, newResult);
    }
}

int FollowsEvaluator::getConstLeft(const QNode* const node) const {
    istringstream iss(node->getChildren()[0]->getString());
    int result;
    iss >> result;
    return result;
}

int FollowsEvaluator::getConstRight(const QNode* const node) const {
    istringstream iss(node->getChildren()[1]->getString());
    int result;
    iss >> result;
    return result;
}

bool FollowsEvaluator::checkLeft(const QNode* const node, const int tested) const {
    return node->getChildren()[0]->getQType() == STMTSYNONYM ||
        synonymToTType(node->getChildren()[0]->getQType()) ==
        pkb->getAst()->getTNode(tested)->getTType();
}

bool FollowsEvaluator::checkRight(const QNode* const node, const int tested) const {
    return node->getChildren()[1]->getQType() == STMTSYNONYM ||
        synonymToTType(node->getChildren()[1]->getQType()) ==
        pkb->getAst()->getTNode(tested)->getTType();
}

vector <int> FollowsEvaluator::getAllLeft(const QNode* const node, 
    const QueryResult &result) const {
    return pkb->getAst()->getStmtLines(
        synonymToTType(node->getChildren()[0]->getQType()));
}

vector <int> FollowsEvaluator::getAllRight(const QNode* const node, 
    const QueryResult &result) const {
    return pkb->getAst()->getStmtLines(
        synonymToTType(node->getChildren()[1]->getQType()));
}