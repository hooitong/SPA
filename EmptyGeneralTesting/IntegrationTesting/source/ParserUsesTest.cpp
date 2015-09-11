#include <cppunit/config/SourcePrefix.h>
#include <algorithm>

#include "ParserUsesTest.h"

void ParserUsesTest::setUp() {
    uTest = PKB::getPKB()->getUses();
}

void ParserUsesTest::tearDown() {
    uTest = nullptr;
}

CPPUNIT_TEST_SUITE_REGISTRATION(ParserUsesTest);

// Test whether the parser and PKB is able to capture all the Uses relationship by StmtLine
void ParserUsesTest::testUsesStmt() {
    vector<VARINDEX> result;

    result = uTest->getUsedByStmt(1);
    CPPUNIT_ASSERT(matchSize(&result, 0));

    result = uTest->getUsedByStmt(2);
    CPPUNIT_ASSERT(matchSize(&result, 0));

    result = uTest->getUsedByStmt(3);
    CPPUNIT_ASSERT(containVarIndex(&result, "a"));
    CPPUNIT_ASSERT(matchSize(&result, 1));

    result = uTest->getUsedByStmt(4);
    CPPUNIT_ASSERT(containVarIndex(&result, "a"));
    CPPUNIT_ASSERT(containVarIndex(&result, "beta"));
    CPPUNIT_ASSERT(containVarIndex(&result, "tmp"));
    CPPUNIT_ASSERT(containVarIndex(&result, "I"));
    CPPUNIT_ASSERT(containVarIndex(&result, "k"));
    CPPUNIT_ASSERT(containVarIndex(&result, "j1k"));
    CPPUNIT_ASSERT(containVarIndex(&result, "chArlie"));
    CPPUNIT_ASSERT(containVarIndex(&result, "left"));
    CPPUNIT_ASSERT(containVarIndex(&result, "right"));
    CPPUNIT_ASSERT(containVarIndex(&result, "delta"));
    CPPUNIT_ASSERT(containVarIndex(&result, "l"));
    CPPUNIT_ASSERT(containVarIndex(&result, "width"));
    CPPUNIT_ASSERT(containVarIndex(&result, "Romeo"));
    CPPUNIT_ASSERT(containVarIndex(&result, "x"));
    CPPUNIT_ASSERT(containVarIndex(&result, "c"));
    CPPUNIT_ASSERT(containVarIndex(&result, "w"));
    CPPUNIT_ASSERT(matchSize(&result, 16));

    result = uTest->getUsedByStmt(5);
    CPPUNIT_ASSERT(containVarIndex(&result, "beta"));
    CPPUNIT_ASSERT(containVarIndex(&result, "tmp"));
    CPPUNIT_ASSERT(containVarIndex(&result, "I"));
    CPPUNIT_ASSERT(containVarIndex(&result, "k"));
    CPPUNIT_ASSERT(containVarIndex(&result, "j1k"));
    CPPUNIT_ASSERT(containVarIndex(&result, "chArlie"));
    CPPUNIT_ASSERT(containVarIndex(&result, "left"));
    CPPUNIT_ASSERT(containVarIndex(&result, "right"));
    CPPUNIT_ASSERT(containVarIndex(&result, "delta"));
    CPPUNIT_ASSERT(containVarIndex(&result, "l"));
    CPPUNIT_ASSERT(containVarIndex(&result, "width"));
    CPPUNIT_ASSERT(containVarIndex(&result, "Romeo"));
    CPPUNIT_ASSERT(containVarIndex(&result, "x"));
    CPPUNIT_ASSERT(containVarIndex(&result, "c"));
    CPPUNIT_ASSERT(matchSize(&result, 14));

    result = uTest->getUsedByStmt(6);
    CPPUNIT_ASSERT(containVarIndex(&result, "beta"));
    CPPUNIT_ASSERT(containVarIndex(&result, "tmp"));
    CPPUNIT_ASSERT(matchSize(&result, 2));

    result = uTest->getUsedByStmt(7);
    CPPUNIT_ASSERT(containVarIndex(&result, "tmp"));
    CPPUNIT_ASSERT(containVarIndex(&result, "I"));
    CPPUNIT_ASSERT(containVarIndex(&result, "k"));
    CPPUNIT_ASSERT(containVarIndex(&result, "j1k"));
    CPPUNIT_ASSERT(containVarIndex(&result, "chArlie"));
    CPPUNIT_ASSERT(matchSize(&result, 5));

    result = uTest->getUsedByStmt(8);
    CPPUNIT_ASSERT(containVarIndex(&result, "I"));
    CPPUNIT_ASSERT(containVarIndex(&result, "k"));
    CPPUNIT_ASSERT(containVarIndex(&result, "j1k"));
    CPPUNIT_ASSERT(containVarIndex(&result, "chArlie"));
    CPPUNIT_ASSERT(matchSize(&result, 4));

    result = uTest->getUsedByStmt(9);
    CPPUNIT_ASSERT(containVarIndex(&result, "left"));
    CPPUNIT_ASSERT(containVarIndex(&result, "right"));
    CPPUNIT_ASSERT(containVarIndex(&result, "delta"));
    CPPUNIT_ASSERT(containVarIndex(&result, "l"));
    CPPUNIT_ASSERT(containVarIndex(&result, "width"));
    CPPUNIT_ASSERT(containVarIndex(&result, "Romeo"));
    CPPUNIT_ASSERT(containVarIndex(&result, "x"));
    CPPUNIT_ASSERT(containVarIndex(&result, "c"));
    CPPUNIT_ASSERT(matchSize(&result, 8));

    result = uTest->getUsedByStmt(10);
    CPPUNIT_ASSERT(containVarIndex(&result, "x"));
    CPPUNIT_ASSERT(matchSize(&result, 1));

    result = uTest->getUsedByStmt(11);
    CPPUNIT_ASSERT(containVarIndex(&result, "left"));
    CPPUNIT_ASSERT(containVarIndex(&result, "right"));
    CPPUNIT_ASSERT(containVarIndex(&result, "delta"));
    CPPUNIT_ASSERT(containVarIndex(&result, "l"));
    CPPUNIT_ASSERT(containVarIndex(&result, "width"));
    CPPUNIT_ASSERT(containVarIndex(&result, "Romeo"));
    CPPUNIT_ASSERT(containVarIndex(&result, "x"));
    CPPUNIT_ASSERT(containVarIndex(&result, "c"));
    CPPUNIT_ASSERT(matchSize(&result, 8));

    result = uTest->getUsedByStmt(12);
    CPPUNIT_ASSERT(containVarIndex(&result, "right"));
    CPPUNIT_ASSERT(containVarIndex(&result, "delta"));
    CPPUNIT_ASSERT(containVarIndex(&result, "l"));
    CPPUNIT_ASSERT(containVarIndex(&result, "width"));
    CPPUNIT_ASSERT(containVarIndex(&result, "Romeo"));
    CPPUNIT_ASSERT(matchSize(&result, 5));

    result = uTest->getUsedByStmt(13);
    CPPUNIT_ASSERT(containVarIndex(&result, "Romeo"));
    CPPUNIT_ASSERT(matchSize(&result, 1));

    result = uTest->getUsedByStmt(14);
    CPPUNIT_ASSERT(matchSize(&result, 0));

    result = uTest->getUsedByStmt(15);
    CPPUNIT_ASSERT(containVarIndex(&result, "delta"));
    CPPUNIT_ASSERT(containVarIndex(&result, "l"));
    CPPUNIT_ASSERT(containVarIndex(&result, "width"));
    CPPUNIT_ASSERT(containVarIndex(&result, "Romeo"));
    CPPUNIT_ASSERT(matchSize(&result, 4));

    result = uTest->getUsedByStmt(16);
    CPPUNIT_ASSERT(containVarIndex(&result, "c"));
    CPPUNIT_ASSERT(matchSize(&result, 1));

    result = uTest->getUsedByStmt(17);
    CPPUNIT_ASSERT(containVarIndex(&result, "c"));
    CPPUNIT_ASSERT(matchSize(&result, 1));

    result = uTest->getUsedByStmt(18);
    CPPUNIT_ASSERT(containVarIndex(&result, "x"));
    CPPUNIT_ASSERT(matchSize(&result, 1));

    result = uTest->getUsedByStmt(19);
    CPPUNIT_ASSERT(matchSize(&result, 0));

    result = uTest->getUsedByStmt(20);
    CPPUNIT_ASSERT(containVarIndex(&result, "w"));
    CPPUNIT_ASSERT(matchSize(&result, 1));
}

// Test whether the parser and PKB is able to capture all the Uses relationship by VarIndex
void ParserUsesTest::testUsesVarIndex() {
    VarTable* varTest = PKB::getPKB()->getVarTable();

    // for each variable in procedure ABC, check whether STMTLINE returned is valid.
    vector<STMTLINE> result;

    result = uTest->getUsesForStmt(varTest->getVarIndex("w"));
    CPPUNIT_ASSERT(containStmtLine(&result, 4));
    CPPUNIT_ASSERT(containStmtLine(&result, 20));
    CPPUNIT_ASSERT(matchSize(&result, 2));

    result = uTest->getUsesForStmt(varTest->getVarIndex("x"));
    CPPUNIT_ASSERT(containStmtLine(&result, 4));
    CPPUNIT_ASSERT(containStmtLine(&result, 5));
    CPPUNIT_ASSERT(containStmtLine(&result, 9));
    CPPUNIT_ASSERT(containStmtLine(&result, 10));
    CPPUNIT_ASSERT(containStmtLine(&result, 11));
    CPPUNIT_ASSERT(containStmtLine(&result, 18));
    CPPUNIT_ASSERT(matchSize(&result, 6));

    result = uTest->getUsesForStmt(varTest->getVarIndex("c"));
    CPPUNIT_ASSERT(containStmtLine(&result, 4));
    CPPUNIT_ASSERT(containStmtLine(&result, 5));
    CPPUNIT_ASSERT(containStmtLine(&result, 9));
    CPPUNIT_ASSERT(containStmtLine(&result, 11));
    CPPUNIT_ASSERT(containStmtLine(&result, 16));
    CPPUNIT_ASSERT(containStmtLine(&result, 17));
    CPPUNIT_ASSERT(matchSize(&result, 6));

    result = uTest->getUsesForStmt(varTest->getVarIndex("delta"));
    CPPUNIT_ASSERT(containStmtLine(&result, 4));
    CPPUNIT_ASSERT(containStmtLine(&result, 5));
    CPPUNIT_ASSERT(containStmtLine(&result, 9));
    CPPUNIT_ASSERT(containStmtLine(&result, 11));
    CPPUNIT_ASSERT(containStmtLine(&result, 12));
    CPPUNIT_ASSERT(containStmtLine(&result, 15));
    CPPUNIT_ASSERT(matchSize(&result, 6));


    result = uTest->getUsesForStmt(varTest->getVarIndex("l"));
    CPPUNIT_ASSERT(containStmtLine(&result, 4));
    CPPUNIT_ASSERT(containStmtLine(&result, 5));
    CPPUNIT_ASSERT(containStmtLine(&result, 9));
    CPPUNIT_ASSERT(containStmtLine(&result, 11));
    CPPUNIT_ASSERT(containStmtLine(&result, 12));
    CPPUNIT_ASSERT(containStmtLine(&result, 15));
    CPPUNIT_ASSERT(matchSize(&result, 6));

    result = uTest->getUsesForStmt(varTest->getVarIndex("width"));
    CPPUNIT_ASSERT(containStmtLine(&result, 4));
    CPPUNIT_ASSERT(containStmtLine(&result, 5));
    CPPUNIT_ASSERT(containStmtLine(&result, 9));
    CPPUNIT_ASSERT(containStmtLine(&result, 11));
    CPPUNIT_ASSERT(containStmtLine(&result, 12));
    CPPUNIT_ASSERT(containStmtLine(&result, 15));
    CPPUNIT_ASSERT(matchSize(&result, 6));

    result = uTest->getUsesForStmt(varTest->getVarIndex("Romeo"));
    CPPUNIT_ASSERT(containStmtLine(&result, 4));
    CPPUNIT_ASSERT(containStmtLine(&result, 5));
    CPPUNIT_ASSERT(containStmtLine(&result, 9));
    CPPUNIT_ASSERT(containStmtLine(&result, 11));
    CPPUNIT_ASSERT(containStmtLine(&result, 12));
    CPPUNIT_ASSERT(containStmtLine(&result, 13));
    CPPUNIT_ASSERT(containStmtLine(&result, 15));
    CPPUNIT_ASSERT(matchSize(&result, 7));

    result = uTest->getUsesForStmt(varTest->getVarIndex("right"));
    CPPUNIT_ASSERT(containStmtLine(&result, 4));
    CPPUNIT_ASSERT(containStmtLine(&result, 5));
    CPPUNIT_ASSERT(containStmtLine(&result, 9));
    CPPUNIT_ASSERT(containStmtLine(&result, 11));
    CPPUNIT_ASSERT(containStmtLine(&result, 12));
    CPPUNIT_ASSERT(matchSize(&result, 5));

    result = uTest->getUsesForStmt(varTest->getVarIndex("left"));
    CPPUNIT_ASSERT(containStmtLine(&result, 4));
    CPPUNIT_ASSERT(containStmtLine(&result, 5));
    CPPUNIT_ASSERT(containStmtLine(&result, 9));
    CPPUNIT_ASSERT(containStmtLine(&result, 11));
    CPPUNIT_ASSERT(matchSize(&result, 4));

    result = uTest->getUsesForStmt(varTest->getVarIndex("I"));
    CPPUNIT_ASSERT(containStmtLine(&result, 4));
    CPPUNIT_ASSERT(containStmtLine(&result, 5));
    CPPUNIT_ASSERT(containStmtLine(&result, 7));
    CPPUNIT_ASSERT(containStmtLine(&result, 8));
    CPPUNIT_ASSERT(matchSize(&result, 4));

    result = uTest->getUsesForStmt(varTest->getVarIndex("k"));
    CPPUNIT_ASSERT(containStmtLine(&result, 4));
    CPPUNIT_ASSERT(containStmtLine(&result, 5));
    CPPUNIT_ASSERT(containStmtLine(&result, 7));
    CPPUNIT_ASSERT(containStmtLine(&result, 8));
    CPPUNIT_ASSERT(matchSize(&result, 4));

    result = uTest->getUsesForStmt(varTest->getVarIndex("j1k"));
    CPPUNIT_ASSERT(containStmtLine(&result, 4));
    CPPUNIT_ASSERT(containStmtLine(&result, 5));
    CPPUNIT_ASSERT(containStmtLine(&result, 7));
    CPPUNIT_ASSERT(containStmtLine(&result, 8));
    CPPUNIT_ASSERT(matchSize(&result, 4));

    result = uTest->getUsesForStmt(varTest->getVarIndex("chArlie"));
    CPPUNIT_ASSERT(containStmtLine(&result, 4));
    CPPUNIT_ASSERT(containStmtLine(&result, 5));
    CPPUNIT_ASSERT(containStmtLine(&result, 7));
    CPPUNIT_ASSERT(containStmtLine(&result, 8));
    CPPUNIT_ASSERT(matchSize(&result, 4));

    result = uTest->getUsesForStmt(varTest->getVarIndex("tmp"));
    CPPUNIT_ASSERT(containStmtLine(&result, 4));
    CPPUNIT_ASSERT(containStmtLine(&result, 5));
    CPPUNIT_ASSERT(containStmtLine(&result, 6));
    CPPUNIT_ASSERT(containStmtLine(&result, 7));
    CPPUNIT_ASSERT(matchSize(&result, 4));

    result = uTest->getUsesForStmt(varTest->getVarIndex("beta"));
    CPPUNIT_ASSERT(containStmtLine(&result, 4));
    CPPUNIT_ASSERT(containStmtLine(&result, 5));
    CPPUNIT_ASSERT(containStmtLine(&result, 6));
    CPPUNIT_ASSERT(matchSize(&result, 3));

    result = uTest->getUsesForStmt(varTest->getVarIndex("a"));
    CPPUNIT_ASSERT(containStmtLine(&result, 3));
    CPPUNIT_ASSERT(containStmtLine(&result, 4));
    CPPUNIT_ASSERT(matchSize(&result, 2));
}

bool ParserUsesTest::containStmtLine(vector<STMTLINE> *list, STMTLINE s) {
    return find(list->begin(), list->end(), s) != list->end();
}

bool ParserUsesTest::containVarIndex(vector<VARINDEX> *list, VARNAME v) {
    VarTable* varTest = PKB::getPKB()->getVarTable();
    VARINDEX vIndex = varTest->getVarIndex(v);
    return find(list->begin(), list->end(), vIndex) != list->end();
}

bool ParserUsesTest::matchSize(vector<VARINDEX> *list, int size) {
    return list->size() == size;
}
