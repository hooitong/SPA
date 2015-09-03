#pragma once

#include <cppunit/extensions/HelperMacros.h>

#include "Modifies.h"

class ModifiesTest : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(ModifiesTest);
 /*   CPPUNIT_TEST(testSetStatement);
    CPPUNIT_TEST(testGetModifiedByStmt);
    CPPUNIT_TEST(testGetModifies);*/
    CPPUNIT_TEST_SUITE_END();

  private:
    Modifies* modifies;

  public:
    void setUp();
    void tearDown();

    void testSetStatement();
    void testGetModifiedByStmt();
    void testGetModifies();
};