#include <ParentEvaluator.h>

ParentEvaluator::ParentEvaluator(PKB* pkb) : RelationEvaluator(pkb){}
bool ParentEvaluator::solveConstConst(const int left, const int right, const QueryResult& result) const
{
    return pkb->getParent()->isParent(left, right);
}

vector<int> ParentEvaluator::solveConstSyn(const int left, const QueryResult& result) const
{
    return pkb->getParent()->getChildOf(left);
}

vector<int> ParentEvaluator::solveSynConst(const int right, const QueryResult& result) const
{
    int newResult = pkb->getParent()->getParent(right);
    if (newResult < 0) {
        return vector<int>();
    } else {
        return vector<int>(1, newResult);
    }
}

int ParentEvaluator::getConstLeft(const QNode* const node) const {
    istringstream iss(node->getChildren()[0]->getString());
    int result;
    iss >> result;
    return result;
}

int ParentEvaluator::getConstRight(const QNode* const node) const {
    istringstream iss(node->getChildren()[1]->getString());
    int result;
    iss >> result;
    return result;
}

bool ParentEvaluator::checkLeft(const QNode* const node, const int tested) const {
    return synonymToTType(node->getChildren()[0]->getQType()) == STMTN ||
        synonymToTType(node->getChildren()[0]->getQType()) ==
        pkb->getAst()->getTNode(tested)->getTType();
}

bool ParentEvaluator::checkRight(const QNode* const node, const int tested) const {
    return synonymToTType(node->getChildren()[1]->getQType()) == STMTN ||
        synonymToTType(node->getChildren()[1]->getQType()) ==
        pkb->getAst()->getTNode(tested)->getTType();
}

vector <int> ParentEvaluator::getAllLeft(const QNode* const node, 
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

vector <int> ParentEvaluator::getAllRight(const QNode* const node, 
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