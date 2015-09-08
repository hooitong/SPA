#pragma once

#include <cppunit/extensions/HelperMacros.h>

#include "ProcTable.h"

class ProcTableTest : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(ProcTableTest);
	CPPUNIT_TEST(insertProcTest);
	CPPUNIT_TEST(getAllTest);
    CPPUNIT_TEST_SUITE_END();

  private:
    ProcTable* procTable;

  public:
    void setUp();
    void tearDown();

	void insertProcTest();
	void getAllTest();

};