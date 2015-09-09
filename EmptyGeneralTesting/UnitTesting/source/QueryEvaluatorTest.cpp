#include <cppunit/config/SourcePrefix.h>

#include "QueryEvaluatorTest.h"

void QueryEvaluatorTest::setUp() {
    pkbObj = new PKB;
    setupTestData();
}

void QueryEvaluatorTest::tearDown() {
    delete pkbObj;
}

// setup sample data in the PKB for testing
// Based on the following SIMPLE program
/*
procedure Daisy {
1. a = 10;
2. c = a + 4;
3. i = 14 + a;
4. b = x + a * c;
5. while i {
6.   b = c - t;
7.   while a {
8.     t = t + a;
9.     i = t + 1;
10.    c = t + a;
11.    i = i - 17; }
12.  c = t + a; }

procedure Rose {
1. z = 10;
2. y = a + z;
}
*/
void QueryEvaluatorTest::setupTestData() {
    Follows* fObj = pkbObj->getFollows();
    fObj->setFollows(1, 2);
    fObj->setFollows(2, 3);
    fObj->setFollows(3, 4);
    fObj->setFollows(4, 5);
    fObj->setFollows(6, 7);
    fObj->setFollows(7, 12);
    fObj->setFollows(8, 9);
    fObj->setFollows(9, 10);
    fObj->setFollows(10, 11);
    fObj->setFollowsStar(1, 2);
    fObj->setFollowsStar(1, 3);
    fObj->setFollowsStar(1, 4);
    fObj->setFollowsStar(1, 5);
    fObj->setFollowsStar(2, 3);
    fObj->setFollowsStar(2, 4);
    fObj->setFollowsStar(2, 5);
    fObj->setFollowsStar(3, 4);
    fObj->setFollowsStar(3, 5);
    fObj->setFollowsStar(4, 5);
    fObj->setFollowsStar(6, 7);
    fObj->setFollowsStar(6, 12);
    fObj->setFollowsStar(7, 12);

    fObj->setFollowsStar(8, 9);
    fObj->setFollowsStar(8, 10);
    fObj->setFollowsStar(8, 11);
    fObj->setFollowsStar(9, 10);
    fObj->setFollowsStar(9, 11);
    fObj->setFollowsStar(10, 11);

    Parent* pObj = pkbObj->getParent();
    pObj->setParent(5, 6);
    pObj->setParent(5, 7);
    pObj->setParent(5, 12);
    pObj->setParent(7, 8);
    pObj->setParent(7, 9);
    pObj->setParent(7, 10);
    pObj->setParent(7, 11);
    pObj->setParentStar(5, 6);
    pObj->setParentStar(5, 7);
    pObj->setParentStar(5, 12);
    pObj->setParentStar(5, 8);
    pObj->setParentStar(5, 9);
    pObj->setParentStar(5, 10);
    pObj->setParentStar(5, 11);
    pObj->setParentStar(7, 8);
    pObj->setParentStar(7, 9);
    pObj->setParentStar(7, 10);
    pObj->setParentStar(7, 11);

    VarTable* vObj = pkbObj->getVarTable();
    int a = vObj->insertVar("a");
    int b = vObj->insertVar("b");
    int c = vObj->insertVar("c");
    int i = vObj->insertVar("i");
    int t = vObj->insertVar("t");
    int x = vObj->insertVar("x");

    Modifies* mObj = pkbObj->getModifies();
    mObj->setModifiesStmt(a, 1);
    mObj->setModifiesStmt(c, 2);
    mObj->setModifiesStmt(i, 3);
    mObj->setModifiesStmt(b, 4);
    mObj->setModifiesStmt(b, 5);
    mObj->setModifiesStmt(c, 5);
    mObj->setModifiesStmt(i, 5);
    mObj->setModifiesStmt(t, 5);
    mObj->setModifiesStmt(b, 6);
    mObj->setModifiesStmt(c, 7);
    mObj->setModifiesStmt(i, 7);
    mObj->setModifiesStmt(t, 7);
    mObj->setModifiesStmt(t, 8);
    mObj->setModifiesStmt(i, 9);
    mObj->setModifiesStmt(c, 10);
    mObj->setModifiesStmt(i, 11);
    mObj->setModifiesStmt(c, 12);

    Uses* uObj = pkbObj->getUses();
    uObj->setUsesStmt(a, 2);
    uObj->setUsesStmt(a, 3);
    uObj->setUsesStmt(a, 4);
    uObj->setUsesStmt(c, 4);
    uObj->setUsesStmt(x, 4);
    uObj->setUsesStmt(a, 5);
    uObj->setUsesStmt(c, 5);
    uObj->setUsesStmt(i, 5);
    uObj->setUsesStmt(t, 5);
    uObj->setUsesStmt(c, 6);
    uObj->setUsesStmt(t, 6);
    uObj->setUsesStmt(a, 7);
    uObj->setUsesStmt(i, 7);
    uObj->setUsesStmt(t, 7);
    uObj->setUsesStmt(a, 8);
    uObj->setUsesStmt(t, 8);
    uObj->setUsesStmt(t, 9);
    uObj->setUsesStmt(a, 10);
    uObj->setUsesStmt(t, 10);
    uObj->setUsesStmt(i, 11);
    uObj->setUsesStmt(a, 12);
    uObj->setUsesStmt(t, 12);


    AST* aObject = pkbObj->getAst();
    aObject->addToStmtLineMap(ASSIGNN, 1);
    aObject->setStmtLine(aObject->createTNode(ASSIGNN, ""), 1);
    aObject->addToStmtLineMap(ASSIGNN, 2);
    aObject->setStmtLine(aObject->createTNode(ASSIGNN, ""), 2);
    aObject->addToStmtLineMap(ASSIGNN, 3);
    aObject->setStmtLine(aObject->createTNode(ASSIGNN, ""), 3);
    aObject->addToStmtLineMap(ASSIGNN, 4);
    aObject->setStmtLine(aObject->createTNode(ASSIGNN, ""), 4);
    aObject->addToStmtLineMap(WHILEN, 5);
    aObject->setStmtLine(aObject->createTNode(WHILEN, ""), 5);
    aObject->addToStmtLineMap(ASSIGNN, 6);
    aObject->setStmtLine(aObject->createTNode(ASSIGNN, ""), 6);
    aObject->addToStmtLineMap(WHILEN, 7);
    aObject->setStmtLine(aObject->createTNode(WHILEN, ""), 7);
    aObject->addToStmtLineMap(ASSIGNN, 8);
    aObject->setStmtLine(aObject->createTNode(ASSIGNN, ""), 8);
    aObject->addToStmtLineMap(ASSIGNN, 9);
    aObject->setStmtLine(aObject->createTNode(ASSIGNN, ""), 9);
    aObject->addToStmtLineMap(ASSIGNN, 10);
    aObject->setStmtLine(aObject->createTNode(ASSIGNN, ""), 10);
    aObject->addToStmtLineMap(ASSIGNN, 11);
    aObject->setStmtLine(aObject->createTNode(ASSIGNN, ""), 11);
    aObject->addToStmtLineMap(ASSIGNN, 12);
    aObject->setStmtLine(aObject->createTNode(ASSIGNN, ""), 12);
}


CPPUNIT_TEST_SUITE_REGISTRATION(QueryEvaluatorTest);

QueryTree* QueryEvaluatorTest::createTree(
    QNodeType typeResult,
    string resultString,
    string relationString,
    QNodeType type1,
    string s1,
    QNodeType type2,
    string s2) {
    QueryTree* tree = new QueryTree();
    QNode* query = tree->createNode(QUERY, "");
    QNode* resultList = tree->createNode(RESULTLIST, "");
    QNode* result1 = tree->createNode(typeResult, resultString);
    QNode* suchThatList = tree->createNode(CONDITIONLIST, "");
    QNode* relation = tree->createNode(RELATION, relationString);
    QNode* arg1 = tree->createNode(type1, s1);
    QNode* arg2 = tree->createNode(type2, s2);


    tree->setAsRoot(query);
    tree->addChild(query, resultList);
    tree->addChild(query, suchThatList);
    tree->addChild(resultList, result1);
    tree->addChild(suchThatList, relation);
    tree->addChild(relation, arg1);
    tree->addChild(relation, arg2);
    return tree;
}

void QueryEvaluatorTest::testFollowsLeft() {
    QueryTree* tree;
    QueryEvaluator evaluator(pkbObj);
    list<string> result;
    list<string> expected;
    tree = createTree(STMTSYNONYM, "s", "Follows", STMTSYNONYM, "s", CONST, "2");

    expected.clear();
    expected.push_back("1");
    result = evaluator.evaluate(tree);
    CPPUNIT_ASSERT(result == expected);
    delete tree;
    tree = createTree(WHILESYNONYM, "w", "Follows", STMTSYNONYM, "w", CONST, "12");

    expected.clear();
    expected.push_back("7");
    result = evaluator.evaluate(tree);
    CPPUNIT_ASSERT(result == expected);
    delete tree;

    tree = createTree(WHILESYNONYM, "w", "Follows", STMTSYNONYM, "s", CONST, "1");

    expected.clear();
    result = evaluator.evaluate(tree);
    CPPUNIT_ASSERT(result == expected);
    delete tree;

    tree = createTree(WHILESYNONYM, "w", "Follows", STMTSYNONYM, "s", CONST, "2");

    expected.clear();
    expected.push_back("5");
    expected.push_back("7");
    result = evaluator.evaluate(tree);
    CPPUNIT_ASSERT(result == expected);
    delete tree;

    tree = createTree(WHILESYNONYM, "w", "Follows", WHILESYNONYM, "w", ANY, "");

    expected.clear();
    expected.push_back("7");
    result = evaluator.evaluate(tree);
    CPPUNIT_ASSERT(result == expected);
    delete tree;
}

void QueryEvaluatorTest::testFollowsRight() {
    QueryTree* tree;
    QueryEvaluator evaluator(pkbObj);
    list<string> result;
    list<string> expected;
    tree = createTree(STMTSYNONYM, "s", "Follows", CONST, "2", STMTSYNONYM, "s");

    expected.clear();
    expected.push_back("3");
    result = evaluator.evaluate(tree);
    CPPUNIT_ASSERT(result == expected);
    delete tree;

    tree = createTree(STMTSYNONYM, "s", "Follows", CONST, "7", STMTSYNONYM, "s");

    expected.clear();
    expected.push_back("12");
    result = evaluator.evaluate(tree);
    CPPUNIT_ASSERT(result == expected);
    delete tree;

    tree = createTree(ASSIGNSYNONYM, "a", "Follows", CONST, "6", ASSIGNSYNONYM, "a");

    expected.clear();
    result = evaluator.evaluate(tree);
    CPPUNIT_ASSERT(result == expected);
    delete tree;


    tree = createTree(WHILESYNONYM, "w", "Follows", CONST, "6", WHILESYNONYM, "w");

    expected.clear();
    expected.push_back("7");
    result = evaluator.evaluate(tree);
    CPPUNIT_ASSERT(result == expected);
    delete tree;

    tree = createTree(WHILESYNONYM, "w", "Follows", ANY, "", WHILESYNONYM, "w");

    expected.clear();
    expected.push_back("5");
    expected.push_back("7");
    result = evaluator.evaluate(tree);
    CPPUNIT_ASSERT(result == expected);
    delete tree;
}

void QueryEvaluatorTest::testFollowsBoth() {
    QueryTree* tree;
    QueryEvaluator evaluator(pkbObj);
    list<string> result;
    list<string> expected;
    tree = createTree(STMTSYNONYM, "s", "Follows", STMTSYNONYM, "s", WHILESYNONYM, "w");

    expected.clear();
    expected.push_back("4");
    expected.push_back("6");
    result = evaluator.evaluate(tree);
    CPPUNIT_ASSERT(result == expected);
    delete tree;

    tree = createTree(STMTSYNONYM, "a1", "Follows", ASSIGNSYNONYM, "a1", ASSIGNSYNONYM, "a2");

    expected.clear();
    expected.push_back("1");
    expected.push_back("2");
    expected.push_back("3");
    expected.push_back("8");
    expected.push_back("9");
    expected.push_back("10");
    result = evaluator.evaluate(tree);
    CPPUNIT_ASSERT(result == expected);
    delete tree;
}

void QueryEvaluatorTest::testFollowsNone() {
    QueryTree* tree;
    QueryEvaluator evaluator(pkbObj);
    list<string> result;
    list<string> expected;
    tree = createTree(STMTSYNONYM, "s", "Follows", CONST, "1", CONST, "3");

    expected.clear();
    result = evaluator.evaluate(tree);
    CPPUNIT_ASSERT(result == expected);
    delete tree;

    tree = createTree(WHILESYNONYM, "fasdf", "Follows", CONST, "7", CONST, "12");

    expected.clear();
    expected.push_back("5");
    expected.push_back("7");
    result = evaluator.evaluate(tree);
    CPPUNIT_ASSERT(result == expected);
    delete tree;

    tree = createTree(WHILESYNONYM, "w", "Follows", ANY, "", CONST, "12");

    expected.clear();
    expected.push_back("5");
    expected.push_back("7");
    result = evaluator.evaluate(tree);
    CPPUNIT_ASSERT(result == expected);
    delete tree;

    tree = createTree(WHILESYNONYM, "w", "Follows", CONST, "5", ANY, "");

    expected.clear();
    result = evaluator.evaluate(tree);
    CPPUNIT_ASSERT(result == expected);
    delete tree;

    tree = createTree(WHILESYNONYM, "s", "Follows", CONST, "5", ANY, "");

    expected.clear();
    result = evaluator.evaluate(tree);
    CPPUNIT_ASSERT(result == expected);
    delete tree;
}

void QueryEvaluatorTest::testFollowsStarLeft() {
    QueryTree* tree;
    QueryEvaluator evaluator(pkbObj);
    list<string> result;
    list<string> expected;
    tree = createTree(STMTSYNONYM, "s", "Follows*", STMTSYNONYM, "s", CONST, "2");

    expected.clear();
    expected.push_back("1");
    result = evaluator.evaluate(tree);
    CPPUNIT_ASSERT(result == expected);
    delete tree;

    tree = createTree(STMTSYNONYM, "s", "Follows*", STMTSYNONYM, "s", CONST, "5");

    expected.clear();
    expected.push_back("1");
    expected.push_back("2");
    expected.push_back("3");
    expected.push_back("4");
    result = evaluator.evaluate(tree);
    CPPUNIT_ASSERT(result == expected);
    delete tree;
    tree = createTree(WHILESYNONYM, "w", "Follows*", STMTSYNONYM, "w", CONST, "12");

    expected.clear();
    expected.push_back("7");
    result = evaluator.evaluate(tree);
    CPPUNIT_ASSERT(result == expected);
    delete tree;

    tree = createTree(WHILESYNONYM, "w", "Follows*", STMTSYNONYM, "s", CONST, "1");

    expected.clear();
    result = evaluator.evaluate(tree);
    CPPUNIT_ASSERT(result == expected);
    delete tree;

    tree = createTree(WHILESYNONYM, "w", "Follows*", STMTSYNONYM, "s", CONST, "2");

    expected.clear();
    expected.push_back("5");
    expected.push_back("7");
    result = evaluator.evaluate(tree);
    CPPUNIT_ASSERT(result == expected);
    delete tree;

    tree = createTree(WHILESYNONYM, "w", "Follows*", WHILESYNONYM, "w", ANY, "");

    expected.clear();
    expected.push_back("7");
    result = evaluator.evaluate(tree);
    CPPUNIT_ASSERT(result == expected);
    delete tree;
}

void QueryEvaluatorTest::testFollowsStarRight() {
    QueryTree* tree;
    QueryEvaluator evaluator(pkbObj);
    list<string> result;
    list<string> expected;
    tree = createTree(STMTSYNONYM, "s", "Follows*", CONST, "2", STMTSYNONYM, "s");

    expected.clear();
    expected.push_back("3");
    expected.push_back("4");
    expected.push_back("5");
    result = evaluator.evaluate(tree);
    CPPUNIT_ASSERT(result == expected);
    delete tree;

    tree = createTree(STMTSYNONYM, "s", "Follows*", CONST, "7", STMTSYNONYM, "s");

    expected.clear();
    expected.push_back("12");
    result = evaluator.evaluate(tree);
    CPPUNIT_ASSERT(result == expected);
    delete tree;

    tree = createTree(ASSIGNSYNONYM, "a", "Follows*", CONST, "6", ASSIGNSYNONYM, "a");

    expected.clear();
    expected.push_back("12");
    result = evaluator.evaluate(tree);
    CPPUNIT_ASSERT(result == expected);
    delete tree;


    tree = createTree(WHILESYNONYM, "w", "Follows*", CONST, "6", WHILESYNONYM, "w");

    expected.clear();
    expected.push_back("7");
    result = evaluator.evaluate(tree);
    CPPUNIT_ASSERT(result == expected);
    delete tree;

    tree = createTree(WHILESYNONYM, "w", "Follows*", ANY, "", WHILESYNONYM, "w");

    expected.clear();
    expected.push_back("5");
    expected.push_back("7");
    result = evaluator.evaluate(tree);
    CPPUNIT_ASSERT(result == expected);
    delete tree;
}

void QueryEvaluatorTest::testFollowsStarBoth() {
    QueryTree* tree;
    QueryEvaluator evaluator(pkbObj);
    list<string> result;
    list<string> expected;
    tree = createTree(STMTSYNONYM, "s", "Follows*", STMTSYNONYM, "s", WHILESYNONYM, "w");

    expected.clear();
    expected.push_back("1");
    expected.push_back("2");
    expected.push_back("3");
    expected.push_back("4");
    expected.push_back("6");
    result = evaluator.evaluate(tree);
    CPPUNIT_ASSERT(result == expected);
    delete tree;

    tree = createTree(STMTSYNONYM, "a1", "Follows*", ASSIGNSYNONYM, "a1", ASSIGNSYNONYM, "a2");

    expected.clear();
    expected.push_back("1");
    expected.push_back("2");
    expected.push_back("3");
    expected.push_back("6");
    expected.push_back("8");
    expected.push_back("9");
    expected.push_back("10");
    result = evaluator.evaluate(tree);
    CPPUNIT_ASSERT(result == expected);
    delete tree;
}

void QueryEvaluatorTest::testFollowsStarNone() {
    QueryTree* tree;
    QueryEvaluator evaluator(pkbObj);
    list<string> result;
    list<string> expected;
    tree = createTree(STMTSYNONYM, "s", "Follows*", CONST, "1", CONST, "3");

    expected.clear();
    expected.push_back("1");
    expected.push_back("2");
    expected.push_back("3");
    expected.push_back("4");
    expected.push_back("5");
    expected.push_back("6");
    expected.push_back("7");
    expected.push_back("8");
    expected.push_back("9");
    expected.push_back("10");
    expected.push_back("11");
    expected.push_back("12");
    result = evaluator.evaluate(tree);
    CPPUNIT_ASSERT(result == expected);
    delete tree;

    tree = createTree(WHILESYNONYM, "fasdf", "Follows*", CONST, "7", CONST, "12");

    expected.clear();
    expected.push_back("5");
    expected.push_back("7");
    result = evaluator.evaluate(tree);
    CPPUNIT_ASSERT(result == expected);
    delete tree;

    tree = createTree(WHILESYNONYM, "w", "Follows*", ANY, "", CONST, "12");

    expected.clear();
    expected.push_back("5");
    expected.push_back("7");
    result = evaluator.evaluate(tree);
    CPPUNIT_ASSERT(result == expected);
    delete tree;

    tree = createTree(WHILESYNONYM, "w", "Follows*", CONST, "5", ANY, "");

    expected.clear();
    result = evaluator.evaluate(tree);
    CPPUNIT_ASSERT(result == expected);
    delete tree;
}

void QueryEvaluatorTest::testParentLeft() {
    QueryTree* tree;
    QueryEvaluator evaluator(pkbObj);
    list<string> result;
    list<string> expected;

    tree = createTree(STMTSYNONYM, "s", "Parent", STMTSYNONYM, "s", CONST, "2");

    expected.clear();
    result = evaluator.evaluate(tree);
    CPPUNIT_ASSERT(result == expected);
    delete tree;

    tree = createTree(WHILESYNONYM, "wwww", "Parent", WHILESYNONYM, "wwww", CONST, "8");

    expected.clear();
    expected.push_back("7");
    result = evaluator.evaluate(tree);
    CPPUNIT_ASSERT(result == expected);
    delete tree;

    tree = createTree(ASSIGNSYNONYM, "aAaAa", "Parent", ASSIGNSYNONYM, "aAaAa", CONST, "6");

    expected.clear();
    result = evaluator.evaluate(tree);
    CPPUNIT_ASSERT(result == expected);
    delete tree;

    tree = createTree(WHILESYNONYM, "w", "Parent", WHILESYNONYM, "w", ANY, "");

    expected.clear();
    expected.push_back("5");
    expected.push_back("7");
    result = evaluator.evaluate(tree);
    CPPUNIT_ASSERT(result == expected);
    delete tree;
}

void QueryEvaluatorTest::testParentRight() {
    QueryTree* tree;
    QueryEvaluator evaluator(pkbObj);
    list<string> result;
    list<string> expected;

    tree = createTree(STMTSYNONYM, "ad", "Parent", CONST, "5", STMTSYNONYM, "ad");

    expected.clear();
    expected.push_back("6");
    expected.push_back("7");
    expected.push_back("12");
    result = evaluator.evaluate(tree);
    CPPUNIT_ASSERT(result == expected);
    delete tree;

    tree = createTree(WHILESYNONYM, "wwww", "Parent", CONST, "5", WHILESYNONYM, "wwww");

    expected.clear();
    expected.push_back("7");
    result = evaluator.evaluate(tree);
    CPPUNIT_ASSERT(result == expected);
    delete tree;

    tree = createTree(ASSIGNSYNONYM, "aAaAa", "Parent", CONST, "7", ASSIGNSYNONYM, "aAaAa");

    expected.clear();
    expected.push_back("8");
    expected.push_back("9");
    expected.push_back("10");
    expected.push_back("11");
    result = evaluator.evaluate(tree);
    CPPUNIT_ASSERT(result == expected);
    delete tree;

    tree = createTree(WHILESYNONYM, "w", "Parent", ANY, "", WHILESYNONYM, "w");

    expected.clear();
    expected.push_back("7");
    result = evaluator.evaluate(tree);
    CPPUNIT_ASSERT(result == expected);
    delete tree;
}

void QueryEvaluatorTest::testParentBoth() {
    QueryTree* tree;
    QueryEvaluator evaluator(pkbObj);
    list<string> result;
    list<string> expected;
    tree = createTree(STMTSYNONYM, "s", "Parent", STMTSYNONYM, "s", WHILESYNONYM, "w");

    expected.clear();
    expected.push_back("5");
    result = evaluator.evaluate(tree);
    CPPUNIT_ASSERT(result == expected);
    delete tree;

    tree = createTree(WHILESYNONYM, "w", "Parent", WHILESYNONYM, "w", ASSIGNSYNONYM, "a");

    expected.clear();
    expected.push_back("5");
    expected.push_back("7");
    result = evaluator.evaluate(tree);
    CPPUNIT_ASSERT(result == expected);
    delete tree;
}

void QueryEvaluatorTest::testParentNone() {
    QueryTree* tree;
    QueryEvaluator evaluator(pkbObj);
    list<string> result;
    list<string> expected;
    tree = createTree(STMTSYNONYM, "s", "Parent", CONST, "5", CONST, "1");

    expected.clear();
    result = evaluator.evaluate(tree);
    CPPUNIT_ASSERT(result == expected);
    delete tree;

    tree = createTree(WHILESYNONYM, "fasdf", "Parent", CONST, "5", CONST, "7");

    expected.clear();
    expected.push_back("5");
    expected.push_back("7");
    result = evaluator.evaluate(tree);
    CPPUNIT_ASSERT(result == expected);
    delete tree;

    tree = createTree(WHILESYNONYM, "w", "Parent", ANY, "", CONST, "5");

    expected.clear();
    result = evaluator.evaluate(tree);
    CPPUNIT_ASSERT(result == expected);
    delete tree;

    tree = createTree(WHILESYNONYM, "w", "Parent", CONST, "5", ANY, "");

    expected.clear();
    expected.push_back("5");
    expected.push_back("7");
    result = evaluator.evaluate(tree);
    CPPUNIT_ASSERT(result == expected);
    delete tree;

    tree = createTree(WHILESYNONYM, "w", "Parent", ANY, "", ANY, "");

    expected.clear();
    expected.push_back("5");
    expected.push_back("7");
    result = evaluator.evaluate(tree);
    CPPUNIT_ASSERT(result == expected);
    delete tree;
}

void QueryEvaluatorTest::testParentStarLeft() {
    QueryTree* tree;
    QueryEvaluator evaluator(pkbObj);
    list<string> result;
    list<string> expected;
    tree = createTree(STMTSYNONYM, "s", "Parent*", STMTSYNONYM, "s", CONST, "8");

    expected.clear();
    expected.push_back("5");
    expected.push_back("7");
    result = evaluator.evaluate(tree);
    CPPUNIT_ASSERT(result == expected);
    delete tree;

    tree = createTree(ASSIGNSYNONYM, "a", "Parent*", ASSIGNSYNONYM, "a", CONST, "8");

    expected.clear();
    result = evaluator.evaluate(tree);
    CPPUNIT_ASSERT(result == expected);
    delete tree;
    tree = createTree(WHILESYNONYM, "w", "Parent*", WHILESYNONYM, "w", CONST, "5");

    expected.clear();
    result = evaluator.evaluate(tree);
    CPPUNIT_ASSERT(result == expected);
    delete tree;

    tree = createTree(WHILESYNONYM, "w", "Parent*", WHILESYNONYM, "w", ANY, "");

    expected.clear();
    expected.push_back("5");
    expected.push_back("7");
    result = evaluator.evaluate(tree);
    CPPUNIT_ASSERT(result == expected);
    delete tree;
}

void QueryEvaluatorTest::testParentStarRight() {
    QueryTree* tree;
    QueryEvaluator evaluator(pkbObj);
    list<string> result;
    list<string> expected;
    tree = createTree(STMTSYNONYM, "s", "Parent*", CONST, "5", STMTSYNONYM, "s");

    expected.clear();
    expected.push_back("6");
    expected.push_back("7");
    expected.push_back("8");
    expected.push_back("9");
    expected.push_back("10");
    expected.push_back("11");
    expected.push_back("12");
    result = evaluator.evaluate(tree);
    CPPUNIT_ASSERT(result == expected);
    delete tree;

    tree = createTree(STMTSYNONYM, "s", "Parent*", CONST, "5", WHILESYNONYM, "s");

    expected.clear();
    expected.push_back("7");
    result = evaluator.evaluate(tree);
    CPPUNIT_ASSERT(result == expected);
    delete tree;

    tree = createTree(WHILESYNONYM, "w", "Parent*", ANY, "", WHILESYNONYM, "w");

    expected.clear();
    expected.push_back("7");
    result = evaluator.evaluate(tree);
    CPPUNIT_ASSERT(result == expected);
    delete tree;
}

void QueryEvaluatorTest::testParentStarBoth() {
    QueryTree* tree;
    QueryEvaluator evaluator(pkbObj);
    list<string> result;
    list<string> expected;
    tree = createTree(STMTSYNONYM, "s", "Parent*", STMTSYNONYM, "s", WHILESYNONYM, "w");

    expected.clear();
    expected.push_back("5");
    result = evaluator.evaluate(tree);
    CPPUNIT_ASSERT(result == expected);
    delete tree;

    tree = createTree(WHILESYNONYM, "w1", "Parent*", WHILESYNONYM, "w1", WHILESYNONYM, "w2");

    expected.clear();
    expected.push_back("5");
    result = evaluator.evaluate(tree);
    CPPUNIT_ASSERT(result == expected);
    delete tree;
}

void QueryEvaluatorTest::testParentStarNone() {
    QueryTree* tree;
    QueryEvaluator evaluator(pkbObj);
    list<string> result;
    list<string> expected;
    tree = createTree(STMTSYNONYM, "s", "Parent*", CONST, "5", CONST, "7");

    expected.clear();
    expected.push_back("1");
    expected.push_back("2");
    expected.push_back("3");
    expected.push_back("4");
    expected.push_back("5");
    expected.push_back("6");
    expected.push_back("7");
    expected.push_back("8");
    expected.push_back("9");
    expected.push_back("10");
    expected.push_back("11");
    expected.push_back("12");
    result = evaluator.evaluate(tree);
    CPPUNIT_ASSERT(result == expected);
    delete tree;

    tree = createTree(WHILESYNONYM, "fasdf", "Parent*", CONST, "3", CONST, "5");

    expected.clear();
    result = evaluator.evaluate(tree);
    CPPUNIT_ASSERT(result == expected);
    delete tree;

    tree = createTree(WHILESYNONYM, "w", "Parent*", ANY, "", CONST, "4");

    expected.clear();
    result = evaluator.evaluate(tree);
    CPPUNIT_ASSERT(result == expected);
    delete tree;

    tree = createTree(WHILESYNONYM, "w", "Parent*", CONST, "5", ANY, "");

    expected.clear();
    expected.push_back("5");
    expected.push_back("7");
    result = evaluator.evaluate(tree);
    CPPUNIT_ASSERT(result == expected);
    delete tree;
}

void QueryEvaluatorTest::testModifiesLeft() {
    QueryTree* tree;
    QueryEvaluator evaluator(pkbObj);
    list<string> result;
    list<string> expected;

    tree = createTree(STMTSYNONYM, "s", "Modifies", STMTSYNONYM, "s", VAR, "b");

    expected.clear();
    expected.push_back("4");
    expected.push_back("5");
    expected.push_back("6");
    result = evaluator.evaluate(tree);
    CPPUNIT_ASSERT(result == expected);
    delete tree;

    tree = createTree(WHILESYNONYM, "w", "Modifies", WHILESYNONYM, "w", VAR, "b");

    expected.clear();
    expected.push_back("5");
    result = evaluator.evaluate(tree);
    CPPUNIT_ASSERT(result == expected);
    delete tree;

    tree = createTree(WHILESYNONYM, "w", "Modifies", WHILESYNONYM, "w", ANY, "");

    expected.clear();
    expected.push_back("5");
    expected.push_back("7");
    result = evaluator.evaluate(tree);
    CPPUNIT_ASSERT(result == expected);
    delete tree;
}

void QueryEvaluatorTest::testModifiesRight() {
    QueryTree* tree;
    QueryEvaluator evaluator(pkbObj);
    list<string> result;
    list<string> expected;

    tree = createTree(VARIABLESYNONYM, "v", "Modifies", CONST, "6", VARIABLESYNONYM, "v");

    expected.clear();
    expected.push_back("b");
    result = evaluator.evaluate(tree);
    CPPUNIT_ASSERT(result == expected);
    delete tree;


    tree = createTree(VARIABLESYNONYM, "v", "Modifies", CONST, "7", VARIABLESYNONYM, "v");

    expected.clear();
    expected.push_back("c");
    expected.push_back("i");
    expected.push_back("t");
    result = evaluator.evaluate(tree);
    CPPUNIT_ASSERT(result == expected);
    delete tree;

    tree = createTree(VARIABLESYNONYM, "v", "Modifies", ANY, "", VARIABLESYNONYM, "v");

    expected.clear();
    expected.push_back("a");
    expected.push_back("b");
    expected.push_back("c");
    expected.push_back("i");
    expected.push_back("t");
    result = evaluator.evaluate(tree);
    CPPUNIT_ASSERT(result == expected);
    delete tree;
}

void QueryEvaluatorTest::testModifiesBoth() {
    QueryTree* tree;
    QueryEvaluator evaluator(pkbObj);
    list<string> result;
    list<string> expected;

    tree = createTree(VARIABLESYNONYM, "v", "Modifies", STMTSYNONYM, "s", VARIABLESYNONYM, "v");

    expected.clear();
    expected.push_back("a");
    expected.push_back("b");
    expected.push_back("c");
    expected.push_back("i");
    expected.push_back("t");
    result = evaluator.evaluate(tree);
    CPPUNIT_ASSERT(result == expected);
    delete tree;


    tree = createTree(ASSIGNSYNONYM, "a", "Modifies", ASSIGNSYNONYM, "a", VARIABLESYNONYM, "v");

    expected.clear();
    expected.push_back("1");
    expected.push_back("2");
    expected.push_back("3");
    expected.push_back("4");
    expected.push_back("6");
    expected.push_back("8");
    expected.push_back("9");
    expected.push_back("10");
    expected.push_back("11");
    expected.push_back("12");
    result = evaluator.evaluate(tree);
    CPPUNIT_ASSERT(result == expected);
    delete tree;

    tree = createTree(WHILESYNONYM, "w", "Modifies", WHILESYNONYM, "w", VARIABLESYNONYM, "v");

    expected.clear();
    expected.push_back("5");
    expected.push_back("7");
    result = evaluator.evaluate(tree);
    CPPUNIT_ASSERT(result == expected);
    delete tree;
}

void QueryEvaluatorTest::testModifiesNone() {
    QueryTree* tree;
    QueryEvaluator evaluator(pkbObj);
    list<string> result;
    list<string> expected;

    tree = createTree(VARIABLESYNONYM, "v", "Modifies", CONST, "5", VAR, "i");

    expected.clear();
    expected.push_back("a");
    expected.push_back("b");
    expected.push_back("c");
    expected.push_back("i");
    expected.push_back("t");
    expected.push_back("x");
    result = evaluator.evaluate(tree);
    CPPUNIT_ASSERT(result == expected);
    delete tree;


    tree = createTree(VARIABLESYNONYM, "v", "Modifies", CONST, "5", VAR, "x");

    expected.clear();
    result = evaluator.evaluate(tree);
    CPPUNIT_ASSERT(result == expected);
    delete tree;

    tree = createTree(WHILESYNONYM, "w", "Modifies", ANY, "", ANY, "");

    expected.clear();
    expected.push_back("5");
    expected.push_back("7");
    result = evaluator.evaluate(tree);
    CPPUNIT_ASSERT(result == expected);
    delete tree;

    tree = createTree(WHILESYNONYM, "w", "Modifies", ANY, "", VAR, "x");

    expected.clear();
    result = evaluator.evaluate(tree);
    CPPUNIT_ASSERT(result == expected);
    delete tree;

    tree = createTree(WHILESYNONYM, "w", "Modifies", CONST, "5", ANY, "");

    expected.clear();
    expected.push_back("5");
    expected.push_back("7");
    result = evaluator.evaluate(tree);
    CPPUNIT_ASSERT(result == expected);
    delete tree;
}