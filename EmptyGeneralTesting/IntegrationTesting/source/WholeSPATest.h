#pragma once

#include <cppunit/extensions/HelperMacros.h>

#include "PKB.h"
#include "SPAFrontEnd.h"
#include "QueryPreprocessor.h"
#include "QueryEvaluator.h"

class WholeSPATest : public CPPUNIT_NS::TestFixture {
  CPPUNIT_TEST_SUITE(WholeSPATest);
  CPPUNIT_TEST(test);
  CPPUNIT_TEST_SUITE_END();

private:

public:
  void setUp();
  void tearDown();

  void test();

};