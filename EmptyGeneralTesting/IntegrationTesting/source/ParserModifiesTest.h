#pragma once

#include <cppunit/extensions/HelperMacros.h>

#include "Modifies.h"
#include "PKB.h"

class ParserModifiesTest : public CPPUNIT_NS::TestFixture {
	CPPUNIT_TEST_SUITE(ParserModifiesTest);
	CPPUNIT_TEST(testModifies);
	CPPUNIT_TEST_SUITE_END();

private:
	Uses* uTest;

public:
	void setUp();
	void tearDown();

	void testModifies();
};