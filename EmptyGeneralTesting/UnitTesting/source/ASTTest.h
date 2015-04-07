#pragma once

#include <cppunit/extensions/HelperMacros.h>

#include "AST.h"

class ASTTest : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(ASTTest);
    CPPUNIT_TEST(testCreateTNode);
    CPPUNIT_TEST(testSetSibling);
    CPPUNIT_TEST(testAddChildTNode);
    CPPUNIT_TEST(testSetStmtLine);
    CPPUNIT_TEST(testSetRoot);
    CPPUNIT_TEST(testIsMatch);
	CPPUNIT_TEST(testGetValue);
	CPPUNIT_TEST(testMatchLeftPattern);
    CPPUNIT_TEST(testMatchRightPattern);
	CPPUNIT_TEST(testMatchRightPattern2);
	CPPUNIT_TEST(testMatchRightPattern3);
    CPPUNIT_TEST_SUITE_END();

  private:
    AST* ast;

  public:
    void setUp();
    void tearDown();

    void testCreateTNode();
    void testSetSibling();
    void testAddChildTNode();
    void testSetStmtLine();
    void testSetRoot();
	void testGetValue();
    void testIsMatch();
    void testMatchLeftPattern();
    void testMatchRightPattern();
	void testMatchRightPattern2();
	void testMatchRightPattern3();

};