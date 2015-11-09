#include <cppunit/config/SourcePrefix.h>

#include "SiblingTest.h"

void SiblingTest::setUp() {
	 ast = new AST;
	 sibling = new Sibling;
}

void SiblingTest::tearDown() {
	delete ast;
	delete sibling;
}

CPPUNIT_TEST_SUITE_REGISTRATION(SiblingTest);

void SiblingTest::testIsSibling() {
  TNode* parent = new TNode();
  parent->setTType(ASSIGNN);
  
  TNode* child1 = new TNode();
  child1->setTType(VARN);
  child1->setNodeValue("x");

  TNode* child2 = new TNode();
  child2->setTType(PLUSN);
  child2->setNodeValue("+");

  TNode* child3 = new TNode();
  child3->setTType(VARN);
  child3->setNodeValue("x");

  TNode* child4 = new TNode();
  child4->setTType(VARN);
  child4->setNodeValue("x");

  ast->setRoot(parent);
  ast->addChildTNode(parent, child1);
  ast->addChildTNode(parent, child2);
  ast->addChildTNode(child2, child3);
  ast->addChildTNode(child2, child4);

  CPPUNIT_ASSERT(!sibling->isSiblingNode(parent, child1));
  CPPUNIT_ASSERT(sibling->isSiblingNode(child1, child2));
  CPPUNIT_ASSERT(sibling->isSiblingNode(child2, child1));
  CPPUNIT_ASSERT(sibling->isSiblingNode(child3, child4));
  CPPUNIT_ASSERT(!sibling->isSiblingNode(child1, child3));
  CPPUNIT_ASSERT(!sibling->isSiblingNode(child4, child1));
}
