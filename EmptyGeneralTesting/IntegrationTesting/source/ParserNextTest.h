#pragma once

#include <cppunit/extensions/HelperMacros.h>

#include "Next.h"
#include "PKB.h"

class ParserNextTest : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(ParserNextTest);
    CPPUNIT_TEST(testNext);
    CPPUNIT_TEST(testNextStar);
    CPPUNIT_TEST_SUITE_END();

  private:
    Next* nTest;

  public:
    void setUp();
    void tearDown();

    void testNext();
    void testNextStar();
};