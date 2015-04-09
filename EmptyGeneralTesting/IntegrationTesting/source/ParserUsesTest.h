#pragma once

#include <cppunit/extensions/HelperMacros.h>

#include "Uses.h"
#include "PKB.h"

class ParserUsesTest : public CPPUNIT_NS::TestFixture {
	CPPUNIT_TEST_SUITE(ParserUsesTest);
	CPPUNIT_TEST(testUses);
	CPPUNIT_TEST_SUITE_END();

private:
	Uses* uTest;

public:
	void setUp();
	void tearDown();

	void testUses();
};