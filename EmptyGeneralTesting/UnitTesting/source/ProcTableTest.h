#pragma once

#include <cppunit/extensions/HelperMacros.h>
class ProcTable;

class ProcTableTest : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(ProcTableTest);
	CPPUNIT_TEST(testInsertProc);
	CPPUNIT_TEST(testGetProcIndex);
	CPPUNIT_TEST(testGetProcName);
	CPPUNIT_TEST(testGetAllProc);
	CPPUNIT_TEST(testSetTRoot);
	CPPUNIT_TEST(testSetGRoot);
	CPPUNIT_TEST(testGetTRoot);
	CPPUNIT_TEST(testGetGNode);
	CPPUNIT_TEST(testAddModified);
	CPPUNIT_TEST(testAddUsed);
	CPPUNIT_TEST(testGetModified);
	CPPUNIT_TEST(testGetUsed);
    CPPUNIT_TEST_SUITE_END();

  public:
    ProcTable* procTable;
    void setUp();
    void tearDown();
	
	void testInsertProc();
	void testGetProcIndex();
	void testGetProcName();
	void testGetAllProc();
	void testSetTRoot();
	void testSetGRoot();
	void testGetTRoot();
	void testGetGNode();
	void testAddModified();
	void testAddUsed();
	void testGetModified();
	void testGetUsed();

};