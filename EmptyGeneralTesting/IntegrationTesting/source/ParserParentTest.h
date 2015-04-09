#pragma once

#include <cppunit/extensions/HelperMacros.h>

#include "Parent.h"
#include "PKB.h"

class ParserParentTest : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(ParserParentTest);
    CPPUNIT_TEST(testParent);
    CPPUNIT_TEST(testParentStar);
    CPPUNIT_TEST_SUITE_END();

  private:
    Parent* pTest;

  public:
    void setUp();
    void tearDown();

    void testParent();
    void testParentStar();
};