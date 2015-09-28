#pragma once

#include <cppunit/extensions/HelperMacros.h>

#include "CallsEvaluator.h"
#include "PKB.h"
#include "QueryTree.h"
#include <QNode.h>

class WithEvaluatorTest : public CPPUNIT_NS::TestFixture {
  CPPUNIT_TEST_SUITE(WithEvaluatorTest);
  CPPUNIT_TEST(testConstConst);
  CPPUNIT_TEST(testAttrConst);
  CPPUNIT_TEST(testConstAttr);
  CPPUNIT_TEST_SUITE_END();

private:
  PKB* pkbObj;
  QNode* createConstConstNode(string left, string right);
  QNode* createConstAttrNode(string left,
      QNodeType typeRight,
      string synonymRight,
      string attrRight);
  QNode* createAttrConstNode(QNodeType typeLeft, 
      string synonymLeft, 
      string attrLeft,
      string right);
  QNode* createAttrAttrNode(QNodeType typeLeft,
      string synonymLeft,
      string attrLeft,
      QNodeType typeRight,
      string synonymRight,
      string attrRight);
  void cleanUp(QNode* node);

public:
  void setUp();
  void tearDown();

  void testConstConst();
  void testAttrConst();
  void testConstAttr();

};
