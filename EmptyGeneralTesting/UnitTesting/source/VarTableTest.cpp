#include <cppunit/config/SourcePrefix.h>
#include "VarTableTest.h"
#include "VarTable.h"
	


void VarTableTest::setUp() {	
}

void VarTableTest::tearDown() {
}

CPPUNIT_TEST_SUITE_REGISTRATION(VarTableTest);

void VarTableTest::testStoreRetrieveName() {
	VARINDEX indexOfX  = (*varTable).insertVar("x");
	CPPUNIT_ASSERT(indexOfX == 1);
}