#pragma once

#include <cppunit/extensions/HelperMacros.h>

#include "Follows.h"
#include "PKB.h"

class ParserFollowsTest : public CPPUNIT_NS::TestFixture {
  CPPUNIT_TEST_SUITE(ParserFollowsTest);
  CPPUNIT_TEST(testFollows);
  CPPUNIT_TEST(testFollowsStar);
  CPPUNIT_TEST_SUITE_END();

private:
  Follows* fTest;

public:
  void setUp();
  void tearDown();

  void testFollows();
  void testFollowsStar();
};