#include <cppunit/config/SourcePrefix.h>
#include <algorithm>

#include "ParserModifiesTest.h"

void ParserModifiesTest::setUp() {
    mTest = PKB::getPKB()->getModifies();
}

void ParserModifiesTest::tearDown() {
    mTest = nullptr;
}

CPPUNIT_TEST_SUITE_REGISTRATION(ParserModifiesTest);

// Test whether the parser and PKB is able to capture all the Modifies relationship
void ParserModifiesTest::testModifiesStmt() {
    // for each stmt line in procedure ABC, check whether VarIndex returned is valid.
    vector<VARINDEX> result;

    result = mTest->getModifiedByStmt(1);
    CPPUNIT_ASSERT(containVarIndex(&result, "i"));
    CPPUNIT_ASSERT(matchSize(&result, 1));

    result = mTest->getModifiedByStmt(2);
    CPPUNIT_ASSERT(containVarIndex(&result, "b"));
    CPPUNIT_ASSERT(matchSize(&result, 1));

    result = mTest->getModifiedByStmt(3);
    CPPUNIT_ASSERT(containVarIndex(&result, "c"));
    CPPUNIT_ASSERT(matchSize(&result, 1));

    result = mTest->getModifiedByStmt(4);
    CPPUNIT_ASSERT(containVarIndex(&result, "w"));
    CPPUNIT_ASSERT(containVarIndex(&result, "oSCar"));
    CPPUNIT_ASSERT(containVarIndex(&result, "Romeo"));
    CPPUNIT_ASSERT(containVarIndex(&result, "b"));
    CPPUNIT_ASSERT(containVarIndex(&result, "c"));
    CPPUNIT_ASSERT(containVarIndex(&result, "x"));
    CPPUNIT_ASSERT(containVarIndex(&result, "a"));
    CPPUNIT_ASSERT(matchSize(&result, 7));

    result = mTest->getModifiedByStmt(5);
    CPPUNIT_ASSERT(containVarIndex(&result, "oSCar"));
    CPPUNIT_ASSERT(containVarIndex(&result, "Romeo"));
    CPPUNIT_ASSERT(containVarIndex(&result, "b"));
    CPPUNIT_ASSERT(containVarIndex(&result, "c"));
    CPPUNIT_ASSERT(containVarIndex(&result, "x"));
    CPPUNIT_ASSERT(containVarIndex(&result, "a"));
    CPPUNIT_ASSERT(matchSize(&result, 6));

    result = mTest->getModifiedByStmt(6);
    CPPUNIT_ASSERT(containVarIndex(&result, "oSCar"));
    CPPUNIT_ASSERT(matchSize(&result, 1));

    result = mTest->getModifiedByStmt(7);
    CPPUNIT_ASSERT(containVarIndex(&result, "oSCar"));
    CPPUNIT_ASSERT(matchSize(&result, 1));

    result = mTest->getModifiedByStmt(8);
    CPPUNIT_ASSERT(containVarIndex(&result, "oSCar"));
    CPPUNIT_ASSERT(matchSize(&result, 1));

    result = mTest->getModifiedByStmt(9);
    CPPUNIT_ASSERT(containVarIndex(&result, "Romeo"));
    CPPUNIT_ASSERT(containVarIndex(&result, "b"));
    CPPUNIT_ASSERT(containVarIndex(&result, "c"));
    CPPUNIT_ASSERT(containVarIndex(&result, "x"));
    CPPUNIT_ASSERT(matchSize(&result, 4));

    result = mTest->getModifiedByStmt(10);
    CPPUNIT_ASSERT(containVarIndex(&result, "x"));
    CPPUNIT_ASSERT(matchSize(&result, 1));

    result = mTest->getModifiedByStmt(11);
    CPPUNIT_ASSERT(containVarIndex(&result, "Romeo"));
    CPPUNIT_ASSERT(containVarIndex(&result, "b"));
    CPPUNIT_ASSERT(containVarIndex(&result, "c"));
    CPPUNIT_ASSERT(containVarIndex(&result, "x"));
    CPPUNIT_ASSERT(matchSize(&result, 4));

    result = mTest->getModifiedByStmt(12);
    CPPUNIT_ASSERT(containVarIndex(&result, "Romeo"));
    CPPUNIT_ASSERT(containVarIndex(&result, "b"));
    CPPUNIT_ASSERT(containVarIndex(&result, "c"));
    CPPUNIT_ASSERT(matchSize(&result, 3));

    result = mTest->getModifiedByStmt(13);
    CPPUNIT_ASSERT(containVarIndex(&result, "Romeo"));
    CPPUNIT_ASSERT(matchSize(&result, 1));

    result = mTest->getModifiedByStmt(14);
    CPPUNIT_ASSERT(containVarIndex(&result, "b"));
    CPPUNIT_ASSERT(matchSize(&result, 1));

    result = mTest->getModifiedByStmt(15);
    CPPUNIT_ASSERT(containVarIndex(&result, "c"));
    CPPUNIT_ASSERT(matchSize(&result, 1));


    result = mTest->getModifiedByStmt(16);
    CPPUNIT_ASSERT(containVarIndex(&result, "c"));
    CPPUNIT_ASSERT(matchSize(&result, 1));

    result = mTest->getModifiedByStmt(17);
    CPPUNIT_ASSERT(containVarIndex(&result, "c"));
    CPPUNIT_ASSERT(matchSize(&result, 1));


    result = mTest->getModifiedByStmt(18);
    CPPUNIT_ASSERT(containVarIndex(&result, "x"));
    CPPUNIT_ASSERT(matchSize(&result, 1));


    result = mTest->getModifiedByStmt(19);
    CPPUNIT_ASSERT(containVarIndex(&result, "a"));
    CPPUNIT_ASSERT(matchSize(&result, 1));


    result = mTest->getModifiedByStmt(20);
    CPPUNIT_ASSERT(containVarIndex(&result, "w"));
    CPPUNIT_ASSERT(matchSize(&result, 1));

}
void ParserModifiesTest::testModifiesVarIndex() {
    VarTable* varTest = PKB::getPKB()->getVarTable();

    // for each variable in procedure ABC, check whether STMTLINE returned is valid.
    vector<STMTLINE> result;

    result = mTest->getModifiesForStmt(varTest->getVarIndex("i"));
    CPPUNIT_ASSERT(containStmtLine(&result, 1));
    CPPUNIT_ASSERT(matchSize(&result, 1));

    result = mTest->getModifiesForStmt(varTest->getVarIndex("b"));
    CPPUNIT_ASSERT(containStmtLine(&result, 2));
    CPPUNIT_ASSERT(containStmtLine(&result, 4));
    CPPUNIT_ASSERT(containStmtLine(&result, 5));
    CPPUNIT_ASSERT(containStmtLine(&result, 9));
    CPPUNIT_ASSERT(containStmtLine(&result, 11));
    CPPUNIT_ASSERT(containStmtLine(&result, 12));
    CPPUNIT_ASSERT(containStmtLine(&result, 14));
    CPPUNIT_ASSERT(matchSize(&result, 7));

    result = mTest->getModifiesForStmt(varTest->getVarIndex("w"));
    CPPUNIT_ASSERT(containStmtLine(&result, 4));
    CPPUNIT_ASSERT(containStmtLine(&result, 20));
    CPPUNIT_ASSERT(matchSize(&result, 2));

    result = mTest->getModifiesForStmt(varTest->getVarIndex("c"));
    CPPUNIT_ASSERT(containStmtLine(&result, 3));
    CPPUNIT_ASSERT(containStmtLine(&result, 4));
    CPPUNIT_ASSERT(containStmtLine(&result, 5));
    CPPUNIT_ASSERT(containStmtLine(&result, 9));
    CPPUNIT_ASSERT(containStmtLine(&result, 11));
    CPPUNIT_ASSERT(containStmtLine(&result, 12));
    CPPUNIT_ASSERT(containStmtLine(&result, 15));
    CPPUNIT_ASSERT(containStmtLine(&result, 16));
    CPPUNIT_ASSERT(containStmtLine(&result, 17));
    CPPUNIT_ASSERT(matchSize(&result, 9));

    result = mTest->getModifiesForStmt(varTest->getVarIndex("a"));
    CPPUNIT_ASSERT(containStmtLine(&result, 4));
    CPPUNIT_ASSERT(containStmtLine(&result, 5));
    CPPUNIT_ASSERT(containStmtLine(&result, 19));
    CPPUNIT_ASSERT(matchSize(&result, 3));

    result = mTest->getModifiesForStmt(varTest->getVarIndex("Romeo"));
    CPPUNIT_ASSERT(containStmtLine(&result, 4));
    CPPUNIT_ASSERT(containStmtLine(&result, 5));
    CPPUNIT_ASSERT(containStmtLine(&result, 9));
    CPPUNIT_ASSERT(containStmtLine(&result, 11));
    CPPUNIT_ASSERT(containStmtLine(&result, 12));
    CPPUNIT_ASSERT(containStmtLine(&result, 13));
    CPPUNIT_ASSERT(matchSize(&result, 6));

    result = mTest->getModifiesForStmt(varTest->getVarIndex("oSCar"));
    CPPUNIT_ASSERT(containStmtLine(&result, 4));
    CPPUNIT_ASSERT(containStmtLine(&result, 5));
    CPPUNIT_ASSERT(containStmtLine(&result, 6));
    CPPUNIT_ASSERT(containStmtLine(&result, 7));
    CPPUNIT_ASSERT(containStmtLine(&result, 8));
    CPPUNIT_ASSERT(matchSize(&result, 5));

    result = mTest->getModifiesForStmt(varTest->getVarIndex("x"));
    CPPUNIT_ASSERT(containStmtLine(&result, 4));
    CPPUNIT_ASSERT(containStmtLine(&result, 5));
    CPPUNIT_ASSERT(containStmtLine(&result, 9));
    CPPUNIT_ASSERT(containStmtLine(&result, 10));
    CPPUNIT_ASSERT(containStmtLine(&result, 11));
    CPPUNIT_ASSERT(containStmtLine(&result, 18));
    CPPUNIT_ASSERT(matchSize(&result, 6));
}

bool ParserModifiesTest::containStmtLine(vector<STMTLINE> *list, STMTLINE s) {
    return find(list->begin(), list->end(), s) != list->end();
}

bool ParserModifiesTest::containVarIndex(vector<VARINDEX> *list, VARNAME v) {
    VarTable* varTest = PKB::getPKB()->getVarTable();
    VARINDEX vIndex = varTest->getVarIndex(v);
    return find(list->begin(), list->end(), vIndex) != list->end();
}

bool ParserModifiesTest::matchSize(vector<VARINDEX> *list, int size) {
    return list->size() == size;
}
