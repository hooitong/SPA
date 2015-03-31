#pragma once

#include <cppunit/extensions/HelperMacros.h>

#include "QueryEvaluator.h"
#include "PKB.h";

class QueryEvaluatorTest : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(QueryEvaluatorTest);
    CPPUNIT_TEST(testFollowsTuple);
    CPPUNIT_TEST(testParentTuple);
    CPPUNIT_TEST(testModifiesTuple);
    CPPUNIT_TEST(testUsesTuple);
    CPPUNIT_TEST_SUITE_END();

  private:
    PKB* pkbObj;
	QueryEvaluator qeObj;
    void setupTestData();

  public:
    void setUp();
    void tearDown();

    void testFollowsTuple();
    void testParentTuple();
    void testModifiesTuple();
    void testUsesTuple();
}