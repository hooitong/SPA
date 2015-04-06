#include <cppunit/config/SourcePrefix.h>

#include "ParserTest.h"
#include "PKB.h"
#include "Parser.h"
#include "GlobalType.h"

void ParserTest::setUp()
{
	Parser::parse("sample_SIMPLE_source.txt");
}

void ParserTest::tearDown()
{

}

CPPUNIT_TEST_SUITE_REGISTRATION(ParserTest);

void ParserTest::testNodeType()
{
	AST* ast = PKB::getPKB()->getAst();
	TNode* root = ast->getRoot();
	CPPUNIT_ASSERT(root->getTType() == TType::PROCEDUREN);
	CPPUNIT_ASSERT(root->getValue() == "ABC");

	TNode* stmt1Node = ast->getTNode(1);
	CPPUNIT_ASSERT(stmt1Node->getTType() == TType::ASSIGNN);

	TNode* stmt2Node = ast->getTNode(2);
	CPPUNIT_ASSERT(stmt2Node->getTType() == TType::ASSIGNN);

	TNode* stmt3Node = ast->getTNode(3);
	CPPUNIT_ASSERT(stmt3Node->getTType() == TType::ASSIGNN);

	TNode* stmt4Node = ast->getTNode(4);
	CPPUNIT_ASSERT(stmt4Node->getTType() == TType::WHILEN);

	TNode* stmt5Node = ast->getTNode(5);
	CPPUNIT_ASSERT(stmt5Node->getTType() == TType::WHILEN);

	TNode* stmt6Node = ast->getTNode(6);
	CPPUNIT_ASSERT(stmt6Node->getTType() == TType::ASSIGNN);

	TNode* stmt7Node = ast->getTNode(7);
	CPPUNIT_ASSERT(stmt7Node->getTType() == TType::WHILEN);

	TNode* stmt8Node = ast->getTNode(8);
	CPPUNIT_ASSERT(stmt8Node->getTType() == TType::ASSIGNN);


}

void ParserTest::testRelationsOfNodes()
{
	CPPUNIT_ASSERT(PKB::getPKB()->getFollows()->isFollows(1,2));
	CPPUNIT_ASSERT(PKB::getPKB()->getFollows()->isFollows(2,3));
	CPPUNIT_ASSERT(PKB::getPKB()->getFollows()->isFollows(3,4));
	CPPUNIT_ASSERT(PKB::getPKB()->getParent()->isParent(4, 5));
	CPPUNIT_ASSERT(PKB::getPKB()->getParent()->isParent(5, 6));
	CPPUNIT_ASSERT(PKB::getPKB()->getFollows()->isFollows(6,7));
	CPPUNIT_ASSERT(PKB::getPKB()->getParent()->isParent(5, 7));
	CPPUNIT_ASSERT(PKB::getPKB()->getParent()->isParent(7, 8));
	CPPUNIT_ASSERT(PKB::getPKB()->getFollows()->isFollows(7,9));
	CPPUNIT_ASSERT(PKB::getPKB()->getParent()->isParent(5, 9));
	CPPUNIT_ASSERT(PKB::getPKB()->getParent()->isParent(9, 10));
	CPPUNIT_ASSERT(PKB::getPKB()->getFollows()->isFollows(10, 11));
	CPPUNIT_ASSERT(PKB::getPKB()->getParent()->isParent(9, 11));
	CPPUNIT_ASSERT(PKB::getPKB()->getParent()->isParent(11, 12));
	CPPUNIT_ASSERT(PKB::getPKB()->getParent()->isParent(12, 13));
	CPPUNIT_ASSERT(PKB::getPKB()->getFollows()->isFollows(13, 14));
	CPPUNIT_ASSERT(PKB::getPKB()->getParent()->isParent(12, 14));
	CPPUNIT_ASSERT(PKB::getPKB()->getFollows()->isFollows(14, 15));
	CPPUNIT_ASSERT(PKB::getPKB()->getParent()->isParent(12, 15));
	CPPUNIT_ASSERT(PKB::getPKB()->getFollows()->isFollows(12, 16));
	CPPUNIT_ASSERT(PKB::getPKB()->getParent()->isParent(11, 16));
	CPPUNIT_ASSERT(PKB::getPKB()->getParent()->isParent(16, 17));
	CPPUNIT_ASSERT(PKB::getPKB()->getFollows()->isFollows(16, 18));
	CPPUNIT_ASSERT(PKB::getPKB()->getParent()->isParent(11, 18));
	CPPUNIT_ASSERT(PKB::getPKB()->getFollows()->isFollows(9, 19));
	CPPUNIT_ASSERT(PKB::getPKB()->getParent()->isParent(5, 19));
	CPPUNIT_ASSERT(PKB::getPKB()->getFollows()->isFollows(5, 20));
	CPPUNIT_ASSERT(PKB::getPKB()->getParent()->isParent(4, 20));
}