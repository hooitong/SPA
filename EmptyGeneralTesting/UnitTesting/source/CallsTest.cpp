#include <cppunit/config/SourcePrefix.h>

#include "CallsTest.h"

void CallsTest::setUp() {
    calls = new Calls;
}

void CallsTest::tearDown() {
    delete calls;
}

CPPUNIT_TEST_SUITE_REGISTRATION(CallsTest);

// Test whether setUsesStmt function works as intended.
void CallsTest::testSetCalls() {
	(*calls).setCalls(0,1);
	(*calls).setCalls(0,2);
	(*calls).setCalls(1,2);
	
}

void CallsTest::testIsCall(){
	(*calls).setCalls(0,1);
	(*calls).setCalls(1,2);

	//make sure though being called, it can call
	CPPUNIT_ASSERT((*calls).isCall(1,2));

	//test direct normal call
	CPPUNIT_ASSERT((*calls).isCall(0,1));

	//it should return false, as 0 does not call 1
	CPPUNIT_ASSERT(!(*calls).isCall(1,0));

	//make sure call star do not fall in here
	CPPUNIT_ASSERT(!(*calls).isCall(0,2));

}

void CallsTest::testIsCallStar(){
	(*calls).setCallsStar(0,1);
	(*calls).setCallsStar(0,2);
	(*calls).setCallsStar(1,2);

	//test normal is call to make sure its working
	CPPUNIT_ASSERT((*calls).isCallStar(0,2));

	//direct call is also considered in callstar
	CPPUNIT_ASSERT((*calls).isCallStar(1,2));
	
	//test case that should fail
	CPPUNIT_ASSERT(!(*calls).isCallStar(2,1));
}

void CallsTest::testGetCalledBy(){
	(*calls).setCalls(0,1);
	(*calls).setCalls(0,2);
	(*calls).setCalls(1,2);

	vector<PROCINDEX> result = (*calls).getCalledBy(0);

	//making sure that the return size is correct
	CPPUNIT_ASSERT(result.size() == 2);

	//making sure that 1 is indeed called
	CPPUNIT_ASSERT(result.at(0) == 1);

	//making sure that 2 is indeed called
	CPPUNIT_ASSERT(result.at(1) == 2);	

}

void CallsTest::testGetCalledByStar(){
	(*calls).setCallsStar(0,1);
	(*calls).setCallsStar(0,2);
	(*calls).setCallsStar(1,2);

	//test basic single getCalledByStar
	vector <PROCINDEX> result = (*calls).getCalledByStar(0);

	//making sure that the return size is correct
	CPPUNIT_ASSERT(result.size() == 2);

	//making sure that 1 is indeed called
	CPPUNIT_ASSERT(result.at(0) == 1);

	//making sure that 2 is indeed called
	CPPUNIT_ASSERT(result.at(1) == 2);	

	//this test is similar to calleby test, as this is to ensure it was implemented correctly as well

}

void CallsTest::testGetCallsTo(){
	(*calls).setCalls(0,1);
	(*calls).setCalls(0,2);
	(*calls).setCalls(1,2);

	vector<PROCINDEX> result = (*calls).getCallsTo(2);

	//making sure that the return size is correct
	CPPUNIT_ASSERT(result.size() == 2);

	//making sure that 0 indeed calls
	CPPUNIT_ASSERT(result.at(0) == 0);

	//making sure that 2 indeed calls
	CPPUNIT_ASSERT(result.at(1) == 1);	

}

void CallsTest::testGetCallsToStar(){
	(*calls).setCallsStar(0,1);
	(*calls).setCallsStar(0,2);
	(*calls).setCallsStar(1,2);

	vector<PROCINDEX> result = (*calls).getCallsToStar(2);

	//making sure that the return size is correct
	CPPUNIT_ASSERT(result.size() == 2);

	//making sure that 0 indeed calls
	CPPUNIT_ASSERT(result.at(0) == 0);

	//making sure that 2 indeed calls
	CPPUNIT_ASSERT(result.at(1) == 1);	

	//though it is testing base on the setup like calls,
	//it was intended for as during the design extraction phase,
	//the calls and calls star are set up the same way

	//there is no check for failed cases, as the vector size test along with the 
	//verification of the 2 result inside would be more then enough

}






