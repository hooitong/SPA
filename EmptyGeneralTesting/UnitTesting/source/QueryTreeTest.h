#pragma once

#include <cppunit/extensions/HelperMacros.h>

#include "QueryTree.h"

class QueryTreeTest : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(QueryTreeTest);
    CPPUNIT_TEST(testCreateQNode);
    CPPUNIT_TEST(testSetAsRoot);
    CPPUNIT_TEST(testAddChild);
    CPPUNIT_TEST_SUITE_END();

  private:
    QueryTree* queryTree;

  public:
    QueryTreeTest();
    void testCreateQNode();
    void testSetAsRoot();
    void testAddChild();
};