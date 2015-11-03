#include <AffectsBipStarEvaluator.h>
#include <stack>
#include <set>
#include <map>

AffectsBipStarEvaluator::AffectsBipStarEvaluator(PKB* p) { pkb = p; }

bool AffectsBipStarEvaluator::affectsFromStmtToAny(STMTLINE stmt) {
    stack<pair<STMTLINE, VARINDEX> > st;
    pair<STMTLINE, VARINDEX> original = make_pair(stmt, pkb->getModifies()->getModifiedByStmt(stmt)[0]);
    st.push(original);
    set <pair<STMTLINE, VARINDEX> > visited;
    visited.insert(original);
    while (!st.empty()) {
        pair<int, int> current = st.top();
        st.pop();
        vector <int> possibleNext = pkb->getNextBip()->getNext(current.first);
        for (vector<int>::iterator it = possibleNext.begin();
            it != possibleNext.end();
            it++) {
            if (pkb->getAst()->getTNode(*it)->getTType() == ASSIGNN) {
                if (pkb->getUses()->isUsesForStmt(*it, current.second)) {
                    return true;
                }
            }
            bool isAssignOrCall = pkb->getAst()->getTNode(*it)->getTType() == ASSIGNN &&
                pkb->getAst()->getTNode(*it)->getTType() == CALLN;

            if (!isAssignOrCall || pkb->getUses()->isUsesForStmt(*it, current.second)) {
                if (visited.find(make_pair(*it, current.second)) == visited.end()) {
                    visited.insert(make_pair(*it, current.second));
                    st.push(make_pair(*it, current.second));
                }
            }
        }
    }
    return false;
}

bool AffectsBipStarEvaluator::affectsFromAnyToStmt(STMTLINE stmt) {
    stack<pair<STMTLINE, VARINDEX> > st;
    set <pair<STMTLINE, VARINDEX> > visited;
    vector <int> possibleUses = pkb->getUses()->getUsedByStmt(stmt);
    for (vector<int>::iterator it = possibleUses.begin();
        it != possibleUses.end();
        it++) {
        pair<STMTLINE, VARINDEX> original = make_pair(stmt, *it);
        st.push(original);
        visited.insert(original);
    }
    while (!st.empty()) {
        pair<int, int> current = st.top();
        st.pop();
        vector <int> possibleBefore = pkb->getNextBip()->getBefore(current.first);
        for (vector<int>::iterator it = possibleBefore.begin();
            it != possibleBefore.end();
            it++) {
            if (pkb->getAst()->getTNode(*it)->getTType() == ASSIGNN) {
                if (pkb->getModifies()->isModifiesForStmt(*it, current.second)) {
                    return true;
                }
            }
            bool isAssignOrCall = pkb->getAst()->getTNode(*it)->getTType() == ASSIGNN &&
                pkb->getAst()->getTNode(*it)->getTType() == CALLN;

            if (!isAssignOrCall || pkb->getModifies()->isModifiesForStmt(*it, current.second)) {
                if (visited.find(make_pair(*it, current.second)) == visited.end()) {
                    visited.insert(make_pair(*it, current.second));
                    st.push(make_pair(*it, current.second));
                }
            }
        }
    }
    return false;
}


set<int> AffectsBipStarEvaluator::affectsFromStmtToSyn(STMTLINE stmt) {
    set<int> result;
    stack<pair<STMTLINE, VARINDEX> > st;
    pair<STMTLINE, VARINDEX> original = make_pair(stmt, pkb->getModifies()->getModifiedByStmt(stmt)[0]);
    st.push(original);
    set <pair<STMTLINE, VARINDEX> > visited;
    visited.insert(original);
    while (!st.empty()) {
        pair<int, int> current = st.top();
        st.pop();
        vector <int> possibleNext = pkb->getNextBip()->getNext(current.first);
        for (vector<int>::iterator it = possibleNext.begin();
            it != possibleNext.end();
            it++) {
            if (pkb->getAst()->getTNode(*it)->getTType() == ASSIGNN) {
                if (pkb->getUses()->isUsesForStmt(*it, current.second)) {
                    result.insert(*it);
                    vector <int> possibleModifies = pkb->getModifies()->getModifiedByStmt(*it);
                    for (vector<int>::iterator it2 = possibleModifies.begin();
                        it2 != possibleModifies.end();
                        it2++) {
                        if (*it2 != current.second && 
                            visited.find(make_pair(*it, *it2)) == visited.end()) {
                            visited.insert(make_pair(*it, *it2));
                            st.push(make_pair(*it, *it2));
                        }
                    }
                    continue;
                }
            }
            bool isAssignOrCall = pkb->getAst()->getTNode(*it)->getTType() == ASSIGNN &&
                pkb->getAst()->getTNode(*it)->getTType() == CALLN;

            if (!isAssignOrCall || pkb->getUses()->isUsesForStmt(*it, current.second)) {
                if (visited.find(make_pair(*it, current.second)) == visited.end()) {
                    visited.insert(make_pair(*it, current.second));
                    st.push(make_pair(*it, current.second));
                }
            }
        }
    }
    return result;
}

set<int> AffectsBipStarEvaluator::affectsFromSynToStmt(STMTLINE stmt) {
    stack<pair<STMTLINE, VARINDEX> > st;
    set<int> result;
    set <pair<STMTLINE, VARINDEX> > visited;
    vector <int> possibleUses = pkb->getUses()->getUsedByStmt(stmt);
    for (vector<int>::iterator it = possibleUses.begin();
        it != possibleUses.end();
        it++) {
        pair<STMTLINE, VARINDEX> original = make_pair(stmt, *it);
        st.push(original);
        visited.insert(original);
    }
    while (!st.empty()) {
        pair<int, int> current = st.top();
        st.pop();
        vector <int> possibleBefore = pkb->getNextBip()->getBefore(current.first);
        for (vector<int>::iterator it = possibleBefore.begin();
            it != possibleBefore.end();
            it++) {
            if (pkb->getAst()->getTNode(*it)->getTType() == ASSIGNN) {
                if (pkb->getModifies()->isModifiesForStmt(*it, current.second)) {
                    result.insert(*it);
                    vector <int> possibleUses = pkb->getUses()->getUsedByStmt(*it);
                    for (vector<int>::iterator it2 = possibleUses.begin();
                        it2 != possibleUses.end();
                        it2++) {
                        if (*it2 != current.second && 
                            visited.find(make_pair(*it, *it2)) == visited.end()) {
                            visited.insert(make_pair(*it, *it2));
                            st.push(make_pair(*it, *it2));
                        }
                    }
                }
            }
            bool isAssignOrCall = pkb->getAst()->getTNode(*it)->getTType() == ASSIGNN &&
                pkb->getAst()->getTNode(*it)->getTType() == CALLN;

            if (!isAssignOrCall || pkb->getModifies()->isModifiesForStmt(*it, current.second)) {
                if (visited.find(make_pair(*it, current.second)) == visited.end()) {
                    visited.insert(make_pair(*it, current.second));
                    st.push(make_pair(*it, current.second));
                }
            }
        }
    }
    return result;
}

QueryResult AffectsBipStarEvaluator::solveAnyAny(QNode* node) {
    vector <int> possibleResult = pkb->getAst()->getStmtLines(ASSIGNN);
    for (vector<int>::iterator it = possibleResult.begin();
        it != possibleResult.end();
        it++) {
        if (affectsFromStmtToAny(*it)) {
            return QueryResult(true);
        }
    }
    return QueryResult(false);
}

QueryResult AffectsBipStarEvaluator::solveAnyConst(QNode* node) {
    int rightConst;
    istringstream iss(node->getChildren()[1]->getString());
    iss >> rightConst;
    return QueryResult(affectsFromAnyToStmt(rightConst));
}

QueryResult AffectsBipStarEvaluator::solveAnySyn(QNode* node) {
    vector <int> possibleResult = pkb->getAst()->getStmtLines(ASSIGNN);
    set <int> result;
    for (vector<int>::iterator it = possibleResult.begin();
        it != possibleResult.end();
        it++) {
        set<int> current = affectsFromStmtToSyn(*it);
        result.insert(current.begin(), current.end());
    }
    vector<int> result_vector(result.begin(), result.end());
    QueryResult queryResult(result_vector, node->getChildren()[1]->getString());
    return queryResult;
}

QueryResult AffectsBipStarEvaluator::solveConstAny(QNode* node) {
    int leftConst;
    istringstream iss(node->getChildren()[0]->getString());
    iss >> leftConst;
    return QueryResult(affectsFromStmtToAny(leftConst));
}
QueryResult AffectsBipStarEvaluator::solveConstConst(QNode* node) {
    int leftConst;
    int rightConst;
    istringstream issl(node->getChildren()[0]->getString());
    istringstream issr(node->getChildren()[1]->getString());;
    issl >> leftConst;
    issr >> rightConst;
    set<int> result = affectsFromStmtToSyn(leftConst);
    return result.find(rightConst) != result.end();
}
QueryResult AffectsBipStarEvaluator::solveConstSyn(QNode* node) {
    int leftConst;
    istringstream issl(node->getChildren()[0]->getString());
    issl >> leftConst;
    set<int> result = affectsFromStmtToSyn(leftConst);
    vector<int> resultVector(result.begin(), result.end());
    QueryResult queryResult(resultVector, node->getChildren()[1]->getString());
    return queryResult;
}
QueryResult AffectsBipStarEvaluator::solveSynAny(QNode* node) {
    vector <int> possibleResult = pkb->getAst()->getStmtLines(ASSIGNN);
    set <int> result;
    for (vector<int>::iterator it = possibleResult.begin();
        it != possibleResult.end();
        it++) {
        set<int> current = affectsFromSynToStmt(*it);
        result.insert(current.begin(), current.end());
    }
    vector<int> result_vector(result.begin(), result.end());
    QueryResult queryResult(result_vector, node->getChildren()[0]->getString());
    return queryResult;
}
QueryResult AffectsBipStarEvaluator::solveSynConst(QNode* node) {
    int rightConst;
    istringstream issr(node->getChildren()[1]->getString());
    issr >> rightConst;
    set<int> result = affectsFromSynToStmt(rightConst);
    vector<int> resultVector(result.begin(), result.end());
    QueryResult queryResult(resultVector, node->getChildren()[0]->getString());
    return queryResult;
}

QueryResult AffectsBipStarEvaluator::solveSynSyn(QNode* node) {
    vector <int> possibleResult = pkb->getAst()->getStmtLines(ASSIGNN);
    set <pair<STMTLINE, STMTLINE> > result;
    for (vector<int>::iterator it = possibleResult.begin();
        it != possibleResult.end();
        it++) {
        set<int> current = affectsFromStmtToSyn(*it);
        for (set<int>::iterator it2 = current.begin();
            it2 != current.end();
            it2++) {
            result.insert(make_pair(*it, *it2));
        }
    }
    vector<pair<int,int> > resultVector(result.begin(), result.end());
    QueryResult queryResult(resultVector,
        node->getChildren()[0]->getString(),
        node->getChildren()[1]->getString());
    return queryResult;
}

bool AffectsBipStarEvaluator::isSynonym(QNodeType type) {
    return type == WHILESYNONYM ||
           type == ASSIGNSYNONYM ||
           type == VARIABLESYNONYM ||
           type == PROCEDURESYNONYM ||
           type == CONSTSYNONYM ||
           type == PROGLINESYNONYM ||
           type == IFSYNONYM ||
           type == STMTSYNONYM;
}

bool AffectsBipStarEvaluator::isConst(QNodeType type) {
    return type == CONST ||
           type == VAR;
}


QueryResult AffectsBipStarEvaluator::evaluate(QNode* node) {
    if (node->getChildren()[0]->getQType() == ANY && 
        node->getChildren()[1]->getQType() == ANY) {
        return solveAnyAny(node);
    } else if (node->getChildren()[0]->getQType() == ANY && 
        isConst(node->getChildren()[1]->getQType())) {
        return solveAnyConst(node);
    } else if (node->getChildren()[0]->getQType() == ANY &&
        isSynonym(node->getChildren()[1]->getQType())) {
        return solveAnySyn(node);
    } else if (isConst(node->getChildren()[0]->getQType()) &&
        node->getChildren()[1]->getQType() == ANY) {
        return solveConstAny(node);
    } else if (isConst(node->getChildren()[0]->getQType()) &&
        isConst(node->getChildren()[1]->getQType())) {
        return solveConstConst(node);
    } else if (isConst(node->getChildren()[0]->getQType()) &&
        isSynonym(node->getChildren()[1]->getQType())) {
        return solveConstSyn(node);
    } else if (isSynonym(node->getChildren()[0]->getQType()) &&
        node->getChildren()[1]->getQType() == ANY) {
        return solveSynAny(node);
    } else if (isSynonym(node->getChildren()[0]->getQType()) &&
        isConst(node->getChildren()[1]->getQType())) {
        return solveSynConst(node);
    } else if (isSynonym(node->getChildren()[0]->getQType()) &&
        isSynonym(node->getChildren()[1]->getQType())) {
        return solveSynSyn(node);
    }
}