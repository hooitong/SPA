#include <cppunit/config/SourcePrefix.h>
#include "ModifiesTest.h"


void ModifiesTest::setUp() {
    modifies = new Modifies;
}

void ModifiesTest::tearDown() {
    delete modifies;
}

CPPUNIT_TEST_SUITE_REGISTRATION(ModifiesTest);

// Test whether setModifiesStmt function works as intended.
void ModifiesTest::testSetStatement() {
    (*modifies).setModifiesStmt(0, 1);
    (*modifies).setModifiesStmt(0, 2);
    (*modifies).setModifiesStmt(1, 2);
}

// Test whether getModifiedByStmt works as intended.
void ModifiesTest::testGetModifiedByStmt() {
    testSetStatement();

    /* Valid input and correct VarIndex should be returned */
    vector<VARINDEX> vLocal;
    vLocal.push_back(0);
    vector<VARINDEX> v = (*modifies).getModifiedByStmt(1);
    CPPUNIT_ASSERT(vLocal == v);

    vLocal.push_back(1);
    v = (*modifies).getModifiedByStmt(2);
    CPPUNIT_ASSERT(vLocal == v);


    /* Invalid input and no VarIndex should be returned */
    v = (*modifies).getModifiedByStmt(3);
    CPPUNIT_ASSERT(v.empty());
}

// Test whether getModifies works as intended
void ModifiesTest::testGetModifies() {
    testSetStatement();

    /* Valid input and correct StmtLine should be returned */
    vector<STMTLINE> vLocal;
    vLocal.push_back(2);
    vector<STMTLINE> v = (*modifies).getModifies(1);
    CPPUNIT_ASSERT(vLocal == v);
    CPPUNIT_ASSERT(vLocal.size() == 1);

    vLocal.push_back(1);
    v = (*modifies).getModifies(0);
    CPPUNIT_ASSERT(vLocal[1] == v[0]);
    CPPUNIT_ASSERT(vLocal[0] == v[1]);
    CPPUNIT_ASSERT(vLocal.size() == 2);

    /* Invalid input and no StmtLine should be returned */
    v = (*modifies).getModifies(2);
    CPPUNIT_ASSERT(v.empty());
}