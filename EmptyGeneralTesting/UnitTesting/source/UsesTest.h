#pragma once

#include <cppunit/extensions/HelperMacros.h>
class Uses;

class UsesTest : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(UsesTest);
    CPPUNIT_TEST(testSetStatement);
    CPPUNIT_TEST(testGetUsedByStmt);
    CPPUNIT_TEST(testGetUses);
    CPPUNIT_TEST_SUITE_END();

  public:
    Uses* uses;
    void setUp();
    void tearDown();

    void testSetStatement();
    void testGetUsedByStmt();
    void testGetUses();

};