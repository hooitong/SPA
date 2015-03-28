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

// Test whether setUsesStmt function works as intended.
void UsesTest::testSetStatement() {
    bool status = (*uses).setUsesStmt(0, 1);
    CPPUNIT_ASSERT(true == status);

    status = (*uses).setUsesStmt(0, 2);
    CPPUNIT_ASSERT(true == status);

    status = (*uses).setUsesStmt(1, 2);
    CPPUNIT_ASSERT(true == status);
}

// Test whether getUsedByStmt works as intended.
void UsesTest::testGetUsedByStmt() {
    testSetStatement();

    /* Valid input and correct VarIndex should be returned */
    vector<VARINDEX> vLocal;
    vLocal.push_back(0);
    vector<VARINDEX> v = (*uses).getUsedByStmt(1);
    CPPUNIT_ASSERT(vLocal == v);

    vLocal.push_back(1);
    v = (*uses).getUsedByStmt(2);
    CPPUNIT_ASSERT(vLocal == v);


    /* Invalid input and no VarIndex should be returned */
    v = (*uses).getUsedByStmt(3);
    CPPUNIT_ASSERT(v.empty());
}

// Test whether getUses works as intended
void UsesTest::testGetUses() {
    testSetStatement();

    /* Valid input and correct StmtLine should be returned */
    vector<STMTLINE> vLocal;
    vLocal.push_back(2);
    vector<STMTLINE> v = (*uses).getUses(1);
    CPPUNIT_ASSERT(vLocal == v);
    CPPUNIT_ASSERT(vLocal.size() == 1);

    vLocal.push_back(1);
    v = (*uses).getUses(0);
    CPPUNIT_ASSERT(vLocal[1] == v[0]);
    CPPUNIT_ASSERT(vLocal[0] == v[1]);
    CPPUNIT_ASSERT(vLocal.size() == 2);

    /* Invalid input and no StmtLine should be returned */
    v = (*uses).getUses(2);
    CPPUNIT_ASSERT(v.empty());
}


