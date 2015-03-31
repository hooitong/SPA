#pragma once

#include <cppunit/extensions/HelperMacros.h>
class AST;

class ASTTest : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(ASTTest);
	CPPUNIT_TEST(testCreateTNode);
	CPPUNIT_TEST(testSetSibling);
	CPPUNIT_TEST(testAddChildTNode);
	CPPUNIT_TEST(testSetStmtLine);
	CPPUNIT_TEST(testSetRoot);
	CPPUNIT_TEST(testIsMatch);
    CPPUNIT_TEST_SUITE_END();

  public:
    AST* ast;
    void setUp();
    void tearDown();

	void testCreateTNode();
	void testSetSibling();
	void testAddChildTNode();
	void testSetStmtLine();
	void testSetRoot();
	void testIsMatch();
	void testPatternMatch();

};