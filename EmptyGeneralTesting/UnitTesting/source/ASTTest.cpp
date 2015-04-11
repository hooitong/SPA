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
	VarTable vTable;
	VARINDEX vx = vTable.insertVar("x");	
    TNode* node = (*ast).createTNode(VARN, std::to_string(static_cast<long long>(vx)));
	string variable = vTable.getVarName(atoi( node->getValue().c_str() ));	
    CPPUNIT_ASSERT(variable == "x");
}

void ASTTest::testSetSibling() {
	VarTable vTable;

	VARINDEX vx = vTable.insertVar("x");	
    TNode* nodeX = (*ast).createTNode(VARN, std::to_string(static_cast<long long>(vx)));
	string variableXIndex = vTable.getVarName(atoi( nodeX->getValue().c_str() ));

	VARINDEX vy = vTable.insertVar("y");	
    TNode* nodeY = (*ast).createTNode(VARN, std::to_string(static_cast<long long>(vy)));
	string variableYIndex = vTable.getVarName(atoi( nodeY->getValue().c_str() ));

    TNode* nodeSiblingLeft = (*ast).createTNode(VARN, variableXIndex); 
    TNode* nodeSiblingRight = (*ast).createTNode(VARN, variableYIndex);
    CPPUNIT_ASSERT((*ast).setSibling(nodeSiblingLeft, nodeSiblingRight));
    CPPUNIT_ASSERT(nodeSiblingRight == (*ast).getRightSibling(nodeSiblingLeft));
    CPPUNIT_ASSERT(nodeSiblingLeft == (*ast).getLeftSibling(nodeSiblingRight));
}


void ASTTest::testGetValue() {
	TNode* node = (*ast).createTNode(VARN, "1");
	CPPUNIT_ASSERT((*ast).getValue(node) == "1");
}

void ASTTest::testAddChildTNode() {
   
	VarTable vTable;
	TNode* nodeStmtLst = (*ast).createTNode(STMTLSTN, "");

    vector<TNode*> childrenLocal;
    TNode* node = (*ast).createTNode(PLUSN, "");
    childrenLocal.push_back(node);
    (*ast).addChildTNode(nodeStmtLst, node);

	VARINDEX vx = vTable.insertVar("x");	
    TNode* nodeSiblingLeft = (*ast).createTNode(VARN, std::to_string(static_cast<long long>(vx)));
	string variableXIndex = vTable.getVarName(atoi( nodeSiblingLeft->getValue().c_str() ));

	VARINDEX vy = vTable.insertVar("y");	
    TNode* nodeSiblingRight = (*ast).createTNode(VARN, std::to_string(static_cast<long long>(vy)));
	string variableYIndex = vTable.getVarName(atoi( nodeSiblingRight->getValue().c_str() ));
	childrenLocal.push_back(nodeSiblingLeft);
    (*ast).addChildTNode(nodeStmtLst, nodeSiblingLeft);
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
	VarTable vTable;
	VARINDEX vx = vTable.insertVar("x");	
    TNode* nodeX = (*ast).createTNode(VARN, std::to_string(static_cast<long long>(vx)));
	string variableXIndex = vTable.getVarName(atoi( nodeX->getValue().c_str() ));
    CPPUNIT_ASSERT((*ast).isMatch(nodeX, VARN));
}

void ASTTest::testMatchLeftPattern() {
    VarTable vTable;
    VARINDEX x = vTable.insertVar("x");
    TNode* root = (*ast).createTNode(ASSIGNN, "");
    TNode* leftChild = (*ast).createTNode(VARN, std::to_string(static_cast<long long>(x)));
    root->addChild(leftChild);
    (*ast).setStmtLine(root, 1);
    CPPUNIT_ASSERT((*ast).matchLeftPattern(1, x));
}

void ASTTest::testMatchRightPattern() {
    //test basic pattern
	//stored "x+y"
	//query strict "x + y"
	//query strict "x+y"

	VarTable vTable;
	TNode* node = (*ast).createTNode(PLUSN, "");

	VARINDEX vx = vTable.insertVar("x");	
    TNode* nodeSiblingLeft = (*ast).createTNode(VARN, std::to_string(static_cast<long long>(vx)));
	string variableXIndex = vTable.getVarName(atoi( nodeSiblingLeft->getValue().c_str() ));

	VARINDEX vy = vTable.insertVar("y");	
    TNode* nodeSiblingRight = (*ast).createTNode(VARN, std::to_string(static_cast<long long>(vy)));
	string variableYIndex = vTable.getVarName(atoi( nodeSiblingRight->getValue().c_str() ));

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


void ASTTest::testMatchRightPattern3(){

	//stored a+b+c-d
	TNode* nodePlus = ast -> createTNode(PLUSN,"");
	TNode* nodePlus2 = ast -> createTNode(PLUSN,"");
	TNode* nodeRootMinus = ast -> createTNode(MINUSN,"");

	VARINDEX aIndex = PKB::getPKB()->getVarTable()->insertVar("a");
	TNode* nodeA = ast -> createTNode(VARN,std::to_string(static_cast<long long>(aIndex)));	
	VARINDEX bIndex = PKB::getPKB()->getVarTable()->insertVar("b");	
	TNode* nodeB = ast -> createTNode(VARN, std::to_string(static_cast<long long>(bIndex)));
	VARINDEX cIndex = PKB::getPKB()->getVarTable()->insertVar("c");
	TNode* nodeC = ast -> createTNode(VARN, std::to_string(static_cast<long long>(cIndex)));
	VARINDEX dIndex = PKB::getPKB()->getVarTable()->insertVar("d");
	TNode* nodeD = ast -> createTNode(VARN, std::to_string(static_cast<long long>(dIndex)));

	nodeRootMinus->addChild(nodePlus);
	nodeRootMinus->addChild(nodeD);
	ast->setSibling(nodePlus, nodeD);

	nodePlus->addChild(nodePlus2);
	nodePlus->addChild(nodeC);
	ast->setSibling(nodePlus2, nodeC);

	nodePlus2->addChild(nodeA);
	nodePlus2->addChild(nodeB);
	ast->setSibling(nodeA, nodeB);

	ast->setStmtLine(nodeRootMinus,3);

	CPPUNIT_ASSERT(ast->matchRightPattern(3, "a+b", false));
	CPPUNIT_ASSERT(ast->matchRightPattern(3, "a+b+c-d", true));
	CPPUNIT_ASSERT(!ast->matchRightPattern(3, "a + b", true));
	CPPUNIT_ASSERT(!ast->matchRightPattern(3, "c-d", false));
	CPPUNIT_ASSERT(!ast->matchRightPattern(3, "b+c", false));
	CPPUNIT_ASSERT(!ast->matchRightPattern(3, "b+c", true));
	CPPUNIT_ASSERT(!ast->matchRightPattern(3, "a+b+c", true));



}

void ASTTest::testMatchRightPattern4(){

	//stored a-b+c-d+z
	TNode* nodeRootPlus = ast -> createTNode(PLUSN,"");
	TNode* nodeMinus1 = ast -> createTNode(MINUSN,"");
	TNode* nodePlus = ast -> createTNode(PLUSN,"");
	TNode* nodeMinus2 = ast -> createTNode(MINUSN,"");

	VARINDEX aIndex = PKB::getPKB()->getVarTable()->insertVar("a");
	TNode* nodeA = ast -> createTNode(VARN,std::to_string(static_cast<long long>(aIndex)));	
	VARINDEX bIndex = PKB::getPKB()->getVarTable()->insertVar("b");	
	TNode* nodeB = ast -> createTNode(VARN, std::to_string(static_cast<long long>(bIndex)));
	VARINDEX cIndex = PKB::getPKB()->getVarTable()->insertVar("c");
	TNode* nodeC = ast -> createTNode(VARN, std::to_string(static_cast<long long>(cIndex)));
	VARINDEX dIndex = PKB::getPKB()->getVarTable()->insertVar("d");
	TNode* nodeD = ast -> createTNode(VARN, std::to_string(static_cast<long long>(dIndex)));
	VARINDEX zIndex = PKB::getPKB()->getVarTable()->insertVar("z");
	TNode* nodeZ = ast -> createTNode(VARN, std::to_string(static_cast<long long>(zIndex)));

	nodeRootPlus->addChild(nodeMinus1);
	nodeRootPlus->addChild(nodeZ);
	ast->setSibling(nodeMinus1, nodeZ);

	nodeMinus1->addChild(nodePlus);
	nodeMinus1->addChild(nodeD);
	ast->setSibling(nodePlus, nodeD);

	nodePlus->addChild(nodeMinus2);
	nodePlus->addChild(nodeC);
	ast->setSibling(nodeMinus2, nodeC);

	nodeMinus2->addChild(nodeA);
	nodeMinus2->addChild(nodeB);
	ast->setSibling(nodeA, nodeB);
	
	ast->setStmtLine(nodeRootPlus,3);
	
	CPPUNIT_ASSERT(ast->matchRightPattern(3, "a-b", false));
	CPPUNIT_ASSERT(ast->matchRightPattern(3, "a-b+c-d+z", true));
	CPPUNIT_ASSERT(ast->matchRightPattern(3, "a-b+c", false));
	CPPUNIT_ASSERT(ast->matchRightPattern(3, "a-b+c-d", false));
	CPPUNIT_ASSERT(ast->matchRightPattern(3, "a", false));
	CPPUNIT_ASSERT(!ast->matchRightPattern(3, "a-b", true));
	CPPUNIT_ASSERT(!ast->matchRightPattern(3, "b+c", false));
	CPPUNIT_ASSERT(!ast->matchRightPattern(3, "c-d", false));
	CPPUNIT_ASSERT(!ast->matchRightPattern(3, "d+z", false));
	CPPUNIT_ASSERT(!ast->matchRightPattern(3, "d+z", true));
	

}
void ASTTest::testMatchRightPatternConst() {

	VarTable vTable;
	TNode* node = (*ast).createTNode(PLUSN, "");

	VARINDEX vx = vTable.insertVar("x");	
    TNode* nodeSiblingLeft = (*ast).createTNode(VARN, std::to_string(static_cast<long long>(vx)));
	string variableXIndex = vTable.getVarName(atoi( nodeSiblingLeft->getValue().c_str() ));

    TNode* nodeSiblingRight = (*ast).createTNode(CONSTN, std::to_string(static_cast<long long>(1)));

    (*node).addChild(nodeSiblingLeft);
    (*node).addChild(nodeSiblingRight);
    (*ast).setSibling(nodeSiblingLeft, nodeSiblingRight);
    (*ast).setStmtLine(node, 2);
    CPPUNIT_ASSERT((*ast).matchRightPattern(2, "x + 1", true));
	CPPUNIT_ASSERT((*ast).matchRightPattern(2, "x+1", true));
}