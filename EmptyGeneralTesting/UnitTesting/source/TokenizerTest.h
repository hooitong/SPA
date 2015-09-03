#pragma once

#include <cppunit/extensions/HelperMacros.h>

#include "GlobalType.h"

class TokenizerTest : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(TokenizerTest);
    CPPUNIT_TEST(testTokenize);
    CPPUNIT_TEST_SUITE_END();

  public:
    void setUp();
    void tearDown();

    void testTokenize();

};