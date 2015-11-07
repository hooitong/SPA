#pragma once

#include <cppunit/extensions/HelperMacros.h>

#include "Contains.h"
#include "AST.h"

class ContainsTest : public CPPUNIT_NS::TestFixture {
  CPPUNIT_TEST_SUITE(ContainsTest);
  CPPUNIT_TEST(testIsContains);
  CPPUNIT_TEST_SUITE_END();

private:
	AST* ast;
	Contains* contains;

public:
  void setUp();
  void tearDown();
  void testIsContains();
};
