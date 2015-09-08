#pragma once

#include <cppunit/extensions/HelperMacros.h>

#include "Calls.h"

class CallsTest : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(CallsTest);
    CPPUNIT_TEST(testSetCalls);
    CPPUNIT_TEST(testIsCall);
	CPPUNIT_TEST(testIsCallStar);
	CPPUNIT_TEST(testGetCalledBy);
	CPPUNIT_TEST(testGetCallsTo);
	CPPUNIT_TEST(testGetCallsToStar);
    CPPUNIT_TEST_SUITE_END();

  private:
    Calls* calls;

  public:
    void setUp();
    void tearDown();

    void testSetCalls();
    void testIsCall();
	void testIsCallStar();
	void testGetCalledBy();
	void testGetCalledByStar();
	void testGetCallsTo();
	void testGetCallsToStar();

};