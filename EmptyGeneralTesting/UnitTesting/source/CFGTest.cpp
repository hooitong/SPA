#include <cppunit/config/SourcePrefix.h>

#include "CFGTest.h"
#include "PKB.h"

#include <vector>
#include <string>



void CFGTest::setUp() {

}

void CFGTest::tearDown() {

}

CPPUNIT_TEST_SUITE_REGISTRATION(CFGTest);

void CFGTest::testInsert() {
	/*CFG* cfg = PKB::getPKB()->getCfg();
	cfg->insert(1, 2);
	cfg->insert(1, 5);
	cfg->insert(1, 6);

	vector<STMTLINE> results = cfg->getImmediateToStmts(1);

	CPPUNIT_ASSERT(cfg->getImmediateToStmts(1).size() == 3);
	CPPUNIT_ASSERT(results.at(0) == 2);
	CPPUNIT_ASSERT(results.at(1) == 5);
	CPPUNIT_ASSERT(results.at(2) == 6);
	CPPUNIT_ASSERT(cfg->getImmediateToStmts(2).size() == 0);*/

}

void CFGTest::testGetAllToStmts(){
	/*CFG* cfg = PKB::getPKB()->getCfg();
	cfg->insert(1, 2);
	cfg->insert(2, 3);
	cfg->insert(3, 4);
	cfg->insert(1, 5);
	cfg->insert(1, 6);

	vector<STMTLINE> results;
	cfg->getAllToStmts(1, results);

	CPPUNIT_ASSERT(results.size() == 5);
	CPPUNIT_ASSERT(results.at(0) == 2);
	CPPUNIT_ASSERT(results.at(1) == 3);
	CPPUNIT_ASSERT(results.at(2) == 4);
	CPPUNIT_ASSERT(results.at(3) == 5);
	CPPUNIT_ASSERT(results.at(4) == 6);*/

}