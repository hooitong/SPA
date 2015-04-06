#include <cppunit/config/SourcePrefix.h>
#include <vector>
#include <string>

#include "ASTTest.h"
#include "VarTable.h"
#include "PKB.h"

void ASTTest::setUp() {
    ast = new AST;
}

void ASTTest::tearDown() {
    delete ast;
}

CPPUNIT_TEST_SUITE_REGISTRATION(ASTTest);

void ASTTest::testCreateTNode() {
    TNode* node = (*ast).createTNode(VARN, "x"); //need to change to varindex
    CPPUNIT_ASSERT((*node).getValue() == "x"); 
}

void ASTTest::testSetSibling() {
    TNode* nodeSiblingLeft = (*ast).createTNode(VARN, "x"); //need to change to varindex
    TNode* nodeSiblingRight = (*ast).createTNode(VARN, "y");//need to change to varindex
    CPPUNIT_ASSERT((*ast).setSibling(nodeSiblingLeft, nodeSiblingRight));
    CPPUNIT_ASSERT(nodeSiblingRight == (*ast).getRightSibling(nodeSiblingLeft));
    CPPUNIT_ASSERT(nodeSiblingLeft == (*ast).getLeftSibling(nodeSiblingRight));
}


void ASTTest::testGetValue() {
	TNode* node = (*ast).createTNode(VARN, "1");
	CPPUNIT_ASSERT((*ast).getValue(node) == "1");
}

void ASTTest::testAddChildTNode() {
    TNode* nodeStmtLst = (*ast).createTNode(STMTLSTN, "");

    vector<TNode*> childrenLocal;
    TNode* node = (*ast).createTNode(PLUSN, "");
    childrenLocal.push_back(node);
    (*ast).addChildTNode(nodeStmtLst, node);

    TNode* nodeSiblingLeft = (*ast).createTNode(VARN, "x");//change to varindex
    childrenLocal.push_back(nodeSiblingLeft);
    (*ast).addChildTNode(nodeStmtLst, nodeSiblingLeft);

    TNode* nodeSiblingRight = (*ast).createTNode(VARN, "y");//change to varindex
    childrenLocal.push_back(nodeSiblingRight);
    (*ast).addChildTNode(nodeStmtLst, nodeSiblingRight);

    vector<TNode*> childrenRetrieved = (*ast).getChildren(nodeStmtLst);
    CPPUNIT_ASSERT(childrenRetrieved == childrenLocal);
    CPPUNIT_ASSERT((*ast).getParentTNode(node) == nodeStmtLst);
}

void ASTTest::testSetStmtLine() {
    TNode* node = (*ast).createTNode(PLUSN, "");
    (*ast).setStmtLine(node, 2);
    CPPUNIT_ASSERT((*ast).getTNode(2) == node);

    (*ast).addToStmtLineMap(PLUSN, 2);
    vector<STMTLINE> stmtLines = (*ast).getStmtLines(PLUSN) ;
    CPPUNIT_ASSERT(stmtLines.size() == 1);
    CPPUNIT_ASSERT(stmtLines[0] == 2);
}

void ASTTest::testSetRoot() {
    TNode* node = (*ast).createTNode(PLUSN, "");
    (*ast).setRoot(node);
    (*ast).setStmtLine(node, 2);
    (*ast).addToStmtLineMap(PLUSN, 2);
    vector<STMTLINE> stmtLines = (*ast).getStmtLines(PLUSN) ;
    CPPUNIT_ASSERT((*ast).getRoot() == node);

}

void ASTTest::testIsMatch() {
    TNode* node = (*ast).createTNode(VARN, "x");//change to varindex
    CPPUNIT_ASSERT((*ast).isMatch(node, VARN));

}

void ASTTest::testMatchLeftPattern() {
    VarTable vTable;
    VARINDEX x = vTable.insertVar("x");
    TNode* root = (*ast).createTNode(ASSIGNN, "");
    stringstream ss;
    ss << x;
    TNode* leftChild = (*ast).createTNode(VARN, ss.str());
    root->addChild(leftChild);
    (*ast).setStmtLine(root, 1);
    CPPUNIT_ASSERT((*ast).matchLeftPattern(1, x));
}

void ASTTest::testMatchRightPattern() {
    //test basic pattern
	//stored "x+y"
	//query strict "x + y"
	//query strict "x+y"
	TNode* node = (*ast).createTNode(PLUSN, "");
    TNode* nodeSiblingLeft = (*ast).createTNode(VARN, "0");
    TNode* nodeSiblingRight = (*ast).createTNode(VARN, "1");
    (*node).addChild(nodeSiblingLeft);
    (*node).addChild(nodeSiblingRight);
    (*ast).setSibling(nodeSiblingLeft, nodeSiblingRight);
    (*ast).setStmtLine(node, 2);
    CPPUNIT_ASSERT((*ast).matchRightPattern(2, "x + y", true));
	CPPUNIT_ASSERT((*ast).matchRightPattern(2, "x+y", true));

	

}


void ASTTest::testMatchRightPattern2(){

	//stored a+b+c
	//query strict a+b
	TNode* nodeRootPlus = ast -> createTNode(PLUSN,"");
	TNode* nodePlus2 = ast -> createTNode(PLUSN,"");

	VARINDEX aIndex = PKB::getPKB()->getVarTable()->insertVar("a");
	TNode* nodeA = ast -> createTNode(VARN,std::to_string(static_cast<long long>(aIndex)));	
	VARINDEX bIndex = PKB::getPKB()->getVarTable()->insertVar("b");	
	TNode* nodeB = ast -> createTNode(VARN, std::to_string(static_cast<long long>(bIndex)));
	VARINDEX cIndex = PKB::getPKB()->getVarTable()->insertVar("c");
	TNode* nodeC = ast -> createTNode(VARN, std::to_string(static_cast<long long>(cIndex)));
	
	nodeRootPlus->addChild(nodePlus2);
	nodeRootPlus->addChild(nodeC);
	ast->setSibling(nodePlus2, nodeC);

	nodePlus2->addChild(nodeA);
	nodePlus2->addChild(nodeB);
	ast->setSibling(nodeA, nodeB);
	ast->setStmtLine(nodeRootPlus, 3);

	CPPUNIT_ASSERT(nodeRootPlus->getStmtLine() == 3);
	CPPUNIT_ASSERT(nodeRootPlus->getChildren().size() == 2);
	CPPUNIT_ASSERT(nodePlus2->getChildren().size() == 2);


	CPPUNIT_ASSERT(!ast->matchRightPattern(3, "a + b", true));
	CPPUNIT_ASSERT(ast->matchRightPattern(3, "a+b", false));
	CPPUNIT_ASSERT(!ast->matchRightPattern(3, "b+c", false));
	CPPUNIT_ASSERT(!ast->matchRightPattern(3, "b+c", true));
	CPPUNIT_ASSERT(ast->matchRightPattern(3, "a+b+c", true));

}
