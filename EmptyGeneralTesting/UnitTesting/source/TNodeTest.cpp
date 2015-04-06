#include <cppunit/config/SourcePrefix.h>

#include "TNodeTest.h"
#include "VarTable.h"

void TNodeTest::setUp() {
	vTable = new VarTable;
	VARINDEX vX = (*vTable).insertVar("x");
	stringstream ss;
	ss<<vX;
	node = new TNode(VARN, ss.str()); //need to change to stmt number
    nodePlus = new TNode(PLUSN, "");
    nodeParent = new TNode(MINUSN, "");
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
	VARNAME x = (*vTable).getVarName((atoi(value.c_str()))); //this value should be equal to the x

    CPPUNIT_ASSERT(x == "x");//should be modified to be varindex.

    type = (*nodePlus).getTType();
    CPPUNIT_ASSERT(type == PLUSN);


    type = (*nodeParent).getTType();
    CPPUNIT_ASSERT(type == MINUSN);
    

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