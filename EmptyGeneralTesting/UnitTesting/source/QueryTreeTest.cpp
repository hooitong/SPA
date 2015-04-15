#include <cppunit/config/SourcePrefix.h>

#include "QueryTreeTest.h"

#include <vector>
#include <string>

#include "QueryTree.h"
#include "GlobalType.h"
#include "QNode.h"

CPPUNIT_TEST_SUITE_REGISTRATION(QueryTreeTest);

QueryTreeTest::QueryTreeTest() {
    queryTree = new QueryTree();
}

void QueryTreeTest::testCreateQNode() {
    QNode* node = queryTree->createNode(VAR, "x");
    CPPUNIT_ASSERT(node->getQType() == VAR);
    CPPUNIT_ASSERT(node->getString() == "x");
}

void QueryTreeTest::testSetAsRoot() {
    QNode* node = queryTree->createNode(EXPRESSION,"x + y");
    queryTree->setAsRoot(node);
    CPPUNIT_ASSERT(queryTree->getRoot()->getQType() == EXPRESSION);
    CPPUNIT_ASSERT(queryTree->getRoot()->getString() == "x + y");
}

void QueryTreeTest::testAddChild() {
    QNode* patternNode = queryTree->createNode(PATTERN,"");
    QNode* assignNode = queryTree->createNode(ASSIGNSYNONYM,"a");
    QNode* varNode = queryTree->createNode(VARIABLESYNONYM,"x");
    QNode* expressionNode = queryTree->createNode(EXPRESSION,"x + y");
    queryTree->addChild(patternNode,assignNode);
    queryTree->addChild(patternNode,varNode);
    queryTree->addChild(patternNode,expressionNode);
    vector<QNode*> children = queryTree->getChildren(patternNode);
    CPPUNIT_ASSERT((int)children.size() == 3);
    CPPUNIT_ASSERT(children[0] == assignNode);
    CPPUNIT_ASSERT(children[1] == varNode);
    CPPUNIT_ASSERT(children[2] == expressionNode);
}
