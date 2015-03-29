#include <cppunit/config/SourcePrefix.h>
#include "TNodeTest.h"
#include "TNode.h"
	


void TNodeTest::setUp() {
	node = new TNode;
	node = new TNode(VARN, "x");
	nodePlus = new TNode;
	nodePlus = new TNode(PLUSN,"+");
	nodeParent = new TNode;
	nodeParent = new TNode(MINUSN,"-");
	
}

void TNodeTest::tearDown() {
	delete node;
	delete nodePlus;
	delete nodeParent;
	
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
	
	bool value = (*node).setLeftSibling(node);
	CPPUNIT_ASSERT ( value == true );
	value = (*node).setRightSibling(NULL);
	CPPUNIT_ASSERT ( value == false );
}

void TNodeTest::testGetLeftSibling(){
	TNode* node = (*node).getLeftSibling();
	CPPUNIT_ASSERT ( node == nodePlus);	
}

void TNodeTest::testGetRightSibling(){
	TNode* node = (*node).getRightSibling();
	CPPUNIT_ASSERT ( node == NULL);	
}

void TNodeTest::testSetParentNode(){
	bool value = (*node).setParentNode(nodeParent);
	CPPUNIT_ASSERT ( value == true);
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


