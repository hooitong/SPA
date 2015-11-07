#pragma once

#include <cppunit/extensions/HelperMacros.h>

#include "Sibling.h"
#include "AST.h"

class SiblingTest : public CPPUNIT_NS::TestFixture {
  CPPUNIT_TEST_SUITE(SiblingTest);
  CPPUNIT_TEST(testIsSibling);
  CPPUNIT_TEST_SUITE_END();

private:
	AST* ast;
	Sibling* sibling;

public:
  void setUp();
  void tearDown();
  void testIsSibling();
};
