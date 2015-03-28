#include <cppunit/config/SourcePrefix.h>
#include "UsesTest.h"
#include "Uses.h"
	


void UsesTest::setUp() {
	uses = new Uses;
}

void UsesTest::tearDown() {
	delete uses;
	
}

CPPUNIT_TEST_SUITE_REGISTRATION(UsesTest);

void UsesTest::testSetStatement(){
	bool status = (*uses).setUsesStmt(0,1);
	CPPUNIT_ASSERT(true == status);	
}

void UsesTest::testGetUsedByStmt(){

	bool status = (*uses).setUsesStmt(0,1);
	vector<VARINDEX> vLocal;
	vLocal.push_back(0);
	vector<VARINDEX> v =(*uses).getUsedByStmt(1);
	CPPUNIT_ASSERT(vLocal==v);
}

void UsesTest::testGetUses(){
	bool status = (*uses).setUsesStmt(0,1);
	vector<STMTLINE> vLocal;
	vLocal.push_back(1);
	vector<VARINDEX> v =(*uses).getUses(0);
	CPPUNIT_ASSERT(vLocal==v);
}


