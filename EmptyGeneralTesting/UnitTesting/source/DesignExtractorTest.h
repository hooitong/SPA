#pragma once

#include <cppunit/extensions/HelperMacros.h>

#include "DesignExtractor.h"

class DesignExtractorTest : public CPPUNIT_NS::TestFixture {
	CPPUNIT_TEST_SUITE(DesignExtractorTest);
	CPPUNIT_TEST(testExtractParentStar);
	CPPUNIT_TEST(testExtractFollowsStar);
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	void testExtractParentStar();
	void testExtractFollowsStar();
};