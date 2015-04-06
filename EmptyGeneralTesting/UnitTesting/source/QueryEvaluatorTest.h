#pragma once

#include <cppunit/extensions/HelperMacros.h>

#include "QueryEvaluator.h"
#include "PKB.h"
#include "QueryTree.h"
#include "QNode.h"

class QueryEvaluatorTest : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(QueryEvaluatorTest);
    CPPUNIT_TEST(testFollows);
    CPPUNIT_TEST(testFollowsStar);
    CPPUNIT_TEST(testParentTuple);
    CPPUNIT_TEST(testModifiesTuple);
    CPPUNIT_TEST(testUsesTuple);
    CPPUNIT_TEST_SUITE_END();

  private:
    PKB* pkbObj;
    void setupTestData();

  public:
    void setUp();
    void tearDown();

    void testFollows();
    void testFollowsStar();
    void testParentTuple();
    void testModifiesTuple();
    void testUsesTuple();
};