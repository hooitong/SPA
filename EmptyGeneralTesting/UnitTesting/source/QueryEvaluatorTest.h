#pragma once

#include <cppunit/extensions/HelperMacros.h>

#include "QueryEvaluator.h"
#include "PKB.h"
#include "QueryTree.h"
#include "QNode.h"

class QueryEvaluatorTest : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(QueryEvaluatorTest);
    CPPUNIT_TEST(testFollowsLeft);
    CPPUNIT_TEST_SUITE_END();

  private:
    PKB* pkbObj;
    void setupTestData();
	QueryTree* createTree(
		QNodeType typeResult,
		string result,
		string relationString, QNodeType type1, string s1, QNodeType type2, string s2);

  public:
    void setUp();
    void tearDown();

    void testFollowsLeft();
};