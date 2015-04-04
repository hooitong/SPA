#include <cppunit/config/SourcePrefix.h>

#include "ParserTest.h"
#include "PKB.h"
#include "Parser.h"

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
	//AST* ast = PKB::getPKB()->getAst();
	//TNode* root = ast->getRoot();
	//CPPUNIT_ASSERT(root->getTType() == TType::PROCEDUREN); 
}