#include <cppunit/config/SourcePrefix.h>

#include "WithEvaluatorTest.h"
#include "WithEvaluator.h"

CPPUNIT_TEST_SUITE_REGISTRATION(WithEvaluatorTest);

QNode* WithEvaluatorTest::createConstConstNode(string left, string right) {
    QNode* leftConst = new QNode(VAR, left);
    QNode* rightConst = new QNode(CONST, right);
    QNode* withNode = new QNode(WITH, "");
    withNode->addChild(leftConst);
    withNode->addChild(rightConst);
    return withNode;
}

QNode* WithEvaluatorTest::createConstAttrNode(string left,
    QNodeType typeRight,
    string synonymRight,
    string attrRight) {
    QNode* leftConst = new QNode(CONST, left);
    QNode* rightNode = new QNode(typeRight, synonymRight);
    QNode* rightAttrNode = new QNode(ATTRIBUTE, attrRight);
    QNode* withNode = new QNode(WITH, "");
    withNode->addChild(leftConst);
    withNode->addChild(rightNode);
    rightNode->addChild(rightAttrNode);
    return withNode;
}

QNode* WithEvaluatorTest::createAttrConstNode(QNodeType typeLeft,
    string synonymLeft,
    string attrLeft,
    string right) {
    QNode* leftNode = new QNode(typeLeft, synonymLeft);
    QNode* leftAttrNode = new QNode(ATTRIBUTE, attrLeft);
    QNode* rightConst = new QNode(CONST, right);
    QNode* withNode = new QNode(WITH, "");
    withNode->addChild(leftNode);
    withNode->addChild(rightConst);
    leftNode->addChild(leftAttrNode);
    return withNode;
}

QNode* WithEvaluatorTest::createAttrAttrNode(QNodeType typeLeft,
    string synonymLeft,
    string attrLeft,
    QNodeType typeRight,
    string synonymRight,
    string attrRight) {
    QNode* leftNode = new QNode(typeLeft, synonymLeft);
    QNode* leftAttrNode = new QNode(ATTRIBUTE, attrLeft);
    QNode* rightNode = new QNode(typeRight, synonymRight);
    QNode* rightAttrNode = new QNode(ATTRIBUTE, attrRight);
    QNode* withNode = new QNode(WITH, "");
    withNode->addChild(leftNode);
    withNode->addChild(rightNode);
    leftNode->addChild(leftAttrNode);
    rightNode->addChild(rightAttrNode);
    return withNode;
}

void WithEvaluatorTest::testConstConst() {
    PKB* pkb = new PKB();
    WithEvaluator eval(pkb);
    QNode* node = createConstConstNode("a", "b");
    QueryResult result = eval.evaluate(node);

    QueryResult expected(false);
    CPPUNIT_ASSERT(result == expected);

    node = createConstConstNode("a", "a");
    result = eval.evaluate(node);

    expected = QueryResult(true);
    CPPUNIT_ASSERT(result == expected);
}

void WithEvaluatorTest::testAttrConst() {
    PKB* pkb = new PKB();
    int a = pkb->getProcTable()->insertProc("A");
    int b = pkb->getProcTable()->insertProc("B");
    int c = pkb->getProcTable()->insertProc("C");

    WithEvaluator eval(pkb);
    QNode* node = createAttrConstNode(PROCEDURESYNONYM, "p", "procName", "A");
    QueryResult result = eval.evaluate(node);

    vector <string> synonyms;
    synonyms.push_back("p");
    QueryResult expected(synonyms);
    
    vector <int> onlyResult;
    onlyResult.push_back(a);
    expected.addSolution(onlyResult);

    CPPUNIT_ASSERT(result == expected);

    node = createAttrConstNode(PROCEDURESYNONYM, "p", "procName", "Z");
    result = eval.evaluate(node);

    synonyms.clear();
    synonyms.push_back("p");
    expected = QueryResult(synonyms);

    CPPUNIT_ASSERT(result == expected);
}

void WithEvaluatorTest::testConstAttr() {
    PKB* pkb = new PKB();
    int a = pkb->getProcTable()->insertProc("A");
    int b = pkb->getProcTable()->insertProc("B");
    int c = pkb->getProcTable()->insertProc("C");

    WithEvaluator eval(pkb);
    QNode* node = createConstAttrNode("A", PROCEDURESYNONYM, "p", "procName");
    QueryResult result = eval.evaluate(node);

    vector <string> synonyms;
    synonyms.push_back("p");
    QueryResult expected(synonyms);
    
    vector <int> onlyResult;
    onlyResult.push_back(a);
    expected.addSolution(onlyResult);

    CPPUNIT_ASSERT(result == expected);

    node = createConstAttrNode("Z", PROCEDURESYNONYM, "p", "procName");
    result = eval.evaluate(node);

    synonyms.clear();
    synonyms.push_back("p");
    expected = QueryResult(synonyms);

    CPPUNIT_ASSERT(result == expected);
}

void WithEvaluatorTest::setUp() {
}

void WithEvaluatorTest::tearDown() {
}