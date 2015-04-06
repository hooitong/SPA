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

void ParserTest::testAST()
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