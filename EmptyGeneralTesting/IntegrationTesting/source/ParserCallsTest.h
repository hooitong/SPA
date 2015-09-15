#pragma once

#include <cppunit/extensions/HelperMacros.h>

#include "Calls.h"
#include "PKB.h"

class ParserCallsTest : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(ParserCallsTest);
    CPPUNIT_TEST(testCalls);
    CPPUNIT_TEST(testCallsStar);
    CPPUNIT_TEST_SUITE_END();

  private:
    Calls* cTest;

  public:
    void setUp();
    void tearDown();

    void testCalls();
    void testCallsStar();
};