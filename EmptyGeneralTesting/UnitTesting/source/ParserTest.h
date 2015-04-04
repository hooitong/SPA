#pragma once

#include <cppunit/extensions/HelperMacros.h>

class ParserTest : public CPPUNIT_NS::TestFixture {
	CPPUNIT_TEST_SUITE(ParserTest);
	CPPUNIT_TEST(testAST);
	CPPUNIT_TEST_SUITE_END();

private:

public:
	void setUp();
    void tearDown();

	void testAST();

};