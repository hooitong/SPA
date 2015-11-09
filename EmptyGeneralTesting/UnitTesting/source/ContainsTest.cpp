#include <cppunit/config/SourcePrefix.h>

#include "ContainsTest.h"

void ContainsTest::setUp() {
	 ast = new AST;
	 contains = new Contains;
}

void ContainsTest::tearDown() {
	delete ast;
	delete contains;
}

CPPUNIT_TEST_SUITE_REGISTRATION(ContainsTest);

void ContainsTest::testIsContains() {
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

  CPPUNIT_ASSERT(contains->isContainsNode(parent, child1));
  CPPUNIT_ASSERT(contains->isContainsNode(parent, child2));
  CPPUNIT_ASSERT(contains->isContainsNode(parent, child3));
  CPPUNIT_ASSERT(contains->isContainsNode(parent, child4));
  CPPUNIT_ASSERT(contains->isContainsNode(child2, child4));
  CPPUNIT_ASSERT(!contains->isContainsNode(child1, child2));
  CPPUNIT_ASSERT(!contains->isContainsNode(child4, child4));
}
