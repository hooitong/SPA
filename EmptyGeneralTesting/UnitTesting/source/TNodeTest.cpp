#include <cppunit/config/SourcePrefix.h>

#include "TNodeTest.h"

void TNodeTest::setUp() {
    node = new TNode(VARN, "x");
    nodePlus = new TNode(PLUSN, "+");//added to assist testing
    nodeParent = new TNode(MINUSN, "-");//added to assist testing
}

void TNodeTest::tearDown() {
    node->getChildren().clear();
    node->setLeftSibling(NULL);
    node->setRightSibling(NULL);
    node->setParentNode(NULL);
    delete node;

    nodePlus->getChildren().clear();
    nodePlus->setLeftSibling(NULL);
    nodePlus->setRightSibling(NULL);
    nodePlus->setParentNode(NULL);
    delete nodePlus;


    nodeParent->getChildren().clear();
    nodeParent->setLeftSibling(NULL);
    nodeParent->setRightSibling(NULL);
    nodeParent->setParentNode(NULL);
    delete nodeParent;
}

CPPUNIT_TEST_SUITE_REGISTRATION(TNodeTest);

void TNodeTest::testCreateNode() {
    TType type = (*node).getTType();
    CPPUNIT_ASSERT(type == VARN);
    string value  = (*node).getValue();
    CPPUNIT_ASSERT(value == "x");

    type = (*nodePlus).getTType();
    CPPUNIT_ASSERT(type == PLUSN);
    value = (*nodePlus).getValue();
    CPPUNIT_ASSERT(value == "+");

    type = (*nodeParent).getTType();
    CPPUNIT_ASSERT(type == MINUSN);
    value = (*nodeParent).getValue();
    CPPUNIT_ASSERT(value == "-");
}

void TNodeTest::testSetSiblings() {
    bool value = (*node).setLeftSibling(nodePlus);
    CPPUNIT_ASSERT (value == true);
    value = (*node).setRightSibling(nodeParent);
    CPPUNIT_ASSERT (value == true);
}

void TNodeTest::testGetLeftSibling() {
    testSetSiblings();
    TNode* nodeLeftSibling = (*node).getLeftSibling();
    CPPUNIT_ASSERT (nodeLeftSibling == nodePlus);
}

void TNodeTest::testGetRightSibling() {
    testSetSiblings();
    TNode* nodeRightSibling = (*node).getRightSibling();
    CPPUNIT_ASSERT (nodeRightSibling == nodeParent);
}

void TNodeTest::testSetParentNode() {
    bool valueBoolSetParent = (*node).setParentNode(nodeParent);
    CPPUNIT_ASSERT (valueBoolSetParent == true);
}

void TNodeTest::testGetParentNode() {
    testSetParentNode();
    TNode* parent = (*node).getParentNode();
    CPPUNIT_ASSERT (parent == nodeParent);
}

void TNodeTest::testAddChildren() {
    bool value = (*nodeParent).addChild(node);
    CPPUNIT_ASSERT (value == true);
    value = (*nodeParent).addChild(nodePlus);
    CPPUNIT_ASSERT (value == true);
}

void TNodeTest::testGetChildren() {
    testAddChildren();
    vector<TNode*> childrenNodes = (*nodeParent).getChildren();
    vector<TNode*> expectedChildren;
    expectedChildren.push_back(node);
    expectedChildren.push_back(nodePlus);
    CPPUNIT_ASSERT(childrenNodes == expectedChildren);
}

void TNodeTest::testSetStmtLine() {
    bool value = (*node).setStmtLine(1);
    CPPUNIT_ASSERT(value == true);

}

void TNodeTest::testGetStmtLine() {
    testSetStmtLine();
    STMTLINE s = (*node).getStmtLine();
    CPPUNIT_ASSERT (s == 1);
}