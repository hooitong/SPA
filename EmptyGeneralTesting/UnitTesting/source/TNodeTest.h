#pragma once

#include <cppunit/extensions/HelperMacros.h>
class TNode;

class TNodeTest : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(TNodeTest);/*
	CPPUNIT_TEST(testCreateNode);
	CPPUNIT_TEST(testIsTType);
	CPPUNIT_TEST(testSetSiblings);
	CPPUNIT_TEST(testGetLeftSibling);
	CPPUNIT_TEST(testGetRightSibling);
	CPPUNIT_TEST(testSetParentNode);
	CPPUNIT_TEST(testGetParentNode);
	CPPUNIT_TEST(testAddChildren);
	CPPUNIT_TEST(testGetChildren);
	CPPUNIT_TEST(testSetStmtLine);
	CPPUNIT_TEST(testGetStmtLine);*/
	CPPUNIT_TEST_SUITE_END();

public:
	TNode* node;
	TNode* nodePlus;//added to assist testing
	TNode* nodeParent;//added to assist testing
	void setUp();
	void tearDown();

	void testCreateNode();
	void testIsTType();
	void testSetSiblings();
	void testGetLeftSibling();
	void testGetRightSibling();
	void testSetParentNode();
	void testGetParentNode();
	void testAddChildren();
	void testGetChildren();
	void testSetStmtLine();
	void testGetStmtLine();

};