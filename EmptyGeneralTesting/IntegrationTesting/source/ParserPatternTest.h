#pragma once

#include <cppunit/extensions/HelperMacros.h>
#include "PKB.h"
#include "VarTable.h"


class ParserPatternTest : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(ParserPatternTest);
	CPPUNIT_TEST(testLeftPatternStrict);
	CPPUNIT_TEST(testRightPatternStrict);
	CPPUNIT_TEST(testRightPatternUnStrict);
    CPPUNIT_TEST_SUITE_END();

  private:
	AST *ast;
	VarTable *vTable;

  public:
    void setUp();
    void tearDown();

	void testLeftPatternStrict();
	void testRightPatternStrict();
	void testRightPatternUnStrict();

};