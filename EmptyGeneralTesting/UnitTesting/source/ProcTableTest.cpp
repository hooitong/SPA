#include <cppunit/config/SourcePrefix.h>

#include "ProcTableTest.h"

void ProcTableTest::setUp() {
    procTable = new ProcTable;
}

void ProcTableTest::tearDown() {
    delete procTable;
}

CPPUNIT_TEST_SUITE_REGISTRATION(ProcTableTest);

void ProcTableTest::insertProcTest(){
	PROCINDEX index = (*procTable).insertProc("winnieWhile");

	//to test and make sure it is stored properly with all the required variables
	CPPUNIT_ASSERT((*procTable).getSize() == 1);
	CPPUNIT_ASSERT((*procTable).getProcName(index) == "winnieWhile");
	CPPUNIT_ASSERT((*procTable).getProcIndex("winnieWhile") == index);

}

void ProcTableTest::getAllTest(){
	PROCINDEX index = (*procTable).insertProc("winnieWhile");
	PROCINDEX index2 = (*procTable).insertProc("issacIf");
	PROCINDEX index3 = (*procTable).insertProc("winnieIssac");

	CPPUNIT_ASSERT((*procTable).getSize() == 3);
	

	//do not have to do failed test, as the test has verified that they are indeed the exact value among
	//all the possible values that might be inside
	vector<PROCINDEX> resultIndex = (*procTable).getAllProcIndex();
	
	CPPUNIT_ASSERT(resultIndex.size() == 3);
	
	CPPUNIT_ASSERT(resultIndex.at(0) == 0);
	CPPUNIT_ASSERT(resultIndex.at(1) == 1);
	CPPUNIT_ASSERT(resultIndex.at(2) == 2);

	vector<PROCNAME> resultName = (*procTable).getAllProcName();

	CPPUNIT_ASSERT(resultName.size() == 3);

	CPPUNIT_ASSERT(resultName.at(0) == "winnieWhile");
	CPPUNIT_ASSERT(resultName.at(1) == "issacIf");
	CPPUNIT_ASSERT(resultName.at(2) == "winnieIssac");




}