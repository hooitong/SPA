#pragma once

#include <cppunit/extensions/HelperMacros.h>

class ParentTest : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(ParentTest);
    CPPUNIT_TEST(testSet);
    CPPUNIT_TEST(testSetStar);
    CPPUNIT_TEST(testIsParent);
    CPPUNIT_TEST(testIsParentStar);
    CPPUNIT_TEST(testGetParent);
    CPPUNIT_TEST(testGetParentStar);
    CPPUNIT_TEST(testGetChildOf);
    CPPUNIT_TEST(testGetChildOfStar);
    CPPUNIT_TEST_SUITE_END();

  public:
    void setUp();
    void tearDown();

    void testSet();
    void testSetStar();
    void testIsParent();
    void testIsParentStar();
    void testGetParent();
    void testGetParentStar();
    void testGetChildOf();
    void testGetChildOfStar();
};