#pragma once

#include <cppunit/extensions/HelperMacros.h>
class VarTable;

class VarTableTest : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(VarTableTest);
	CPPUNIT_TEST(testStoreRetrieveName);
	CPPUNIT_TEST_SUITE_END();

public:
	VarTable* varTable;
	void setUp();
	void tearDown();

	void testStoreRetrieveName();

};