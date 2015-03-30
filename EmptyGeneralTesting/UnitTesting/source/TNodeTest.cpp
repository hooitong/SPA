#include <cppunit/config/SourcePrefix.h>
#include "TNodeTest.h"


TNode* node = new TNode(VARN, "x");
TNode* nodePlus = new TNode(PLUSN,"+");//added to assist testing
TNode* nodeParent = new TNode(MINUSN,"-");//added to assist testing

void TNodeTest::setUp() {
	
}

void TNodeTest::tearDown() {
	//delete node;
	//delete nodePlus;
	//delete nodeParent;
}

CPPUNIT_TEST_SUITE_REGISTRATION(TNodeTest);

void TNodeTest::testCreateNode() {
	TType type = (*node).getTType();
	CPPUNIT_ASSERT( type == VARN );
	string value  = (*node).getValue();
	CPPUNIT_ASSERT( value == "x" );
}
void TNodeTest::testIsTType(){
	bool value = (*node).isTType(node, VARN);
	CPPUNIT_ASSERT ( value == true);

	value = (*node).isTType(node, STMTLSTN);
	CPPUNIT_ASSERT ( value == false);
}

void TNodeTest::testSetSiblings(){
	
	bool value = (*node).setLeftSibling(nodePlus);
	CPPUNIT_ASSERT ( value == true );
	value = (*node).setRightSibling(NULL);
	CPPUNIT_ASSERT ( value == true );
}

void TNodeTest::testGetLeftSibling(){
	TNode* nodeLeftSibling = (*node).getLeftSibling();
	CPPUNIT_ASSERT ( nodeLeftSibling == nodePlus);	
}

void TNodeTest::testGetRightSibling(){
	TNode* nodeRightSibling = (*node).getRightSibling();
	CPPUNIT_ASSERT ( nodeRightSibling == NULL);	
}

void TNodeTest::testSetParentNode(){
	bool valueBoolSetParent = (*node).setParentNode(nodeParent);
	CPPUNIT_ASSERT ( valueBoolSetParent == true);
}

void TNodeTest::testGetParentNode(){
	TNode* parent = (*node).getParentNode();
	CPPUNIT_ASSERT ( parent == nodeParent);
}

void TNodeTest::testAddChildren(){
	bool value = (*nodeParent).addChild(node);
	CPPUNIT_ASSERT ( value == true);
	value = (*nodeParent).addChild(nodePlus);
	CPPUNIT_ASSERT ( value == true);
}

void TNodeTest::testGetChildren(){
	vector<TNode*> childrenNodes = (*nodeParent).getChildren();
	vector<TNode*> expectedChildren;
	expectedChildren.push_back(node);
	expectedChildren.push_back(nodePlus );
	CPPUNIT_ASSERT( childrenNodes == expectedChildren );
}

void TNodeTest::testSetStmtLine(){
	bool value = (*node).setStmtLine(1);
	CPPUNIT_ASSERT( value == true );

}

void TNodeTest::testGetStmtLine(){
	STMTLINE s = (*node).getStmtLine();
	CPPUNIT_ASSERT ( s == 1 );
}


