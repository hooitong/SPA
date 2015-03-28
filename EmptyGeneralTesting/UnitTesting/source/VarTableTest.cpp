#include <cppunit/config/SourcePrefix.h>
#include "VarTableTest.h"
#include "VarTable.h"
	


void VarTableTest::setUp() {
	varTable = new VarTable;
}

void VarTableTest::tearDown() {
	delete varTable;
}

CPPUNIT_TEST_SUITE_REGISTRATION(VarTableTest);

void VarTableTest::testStoreRetrieveName() {
	VARINDEX indexOfX  = (*varTable).insertVar("ab");
	CPPUNIT_ASSERT(indexOfX == 0);
}