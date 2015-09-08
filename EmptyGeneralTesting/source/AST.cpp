#include "AST.h"

#include <stack>
#include <stdlib.h>

#include "Parser.h"
#include "PKB.h"

/* Constructor & Destructor */
AST::AST(void) {
}

AST::~AST(void) {

}


TNode* AST::createTNode(TType nodeType, std::string value) {
    TNode* node = new TNode();
	node->setTType(nodeType);
	node->setNodeValue(value);
	return node;
}

bool AST::setSibling(TNode* leftNode, TNode* rightNode) {
    if((*leftNode).getRightSibling()->getTType() != EMPTYN) {
        return false;
    }
    if((*rightNode).getLeftSibling()->getTType() != EMPTYN) {
        return false;
    }
    (*leftNode).setRightSibling(rightNode);
    (*rightNode).setLeftSibling(leftNode);
    return true;
}

bool AST::addChildTNode(TNode* parent, TNode* child) {
	if((*child).getParentNode()->getTType() != EMPTYN) {
        return false;
    }

    /* Set two-way link of parent and child */
    (*parent).addChild(child);
    (*child).setParentNode(parent);
    return true;
}

vector<TNode*> AST::getChildren(TNode* parent) {
    return (*parent).getChildren();

}

TNode* AST::getLeftSibling(TNode* node) {
    return (*node).getLeftSibling();
}

TNode* AST::getRightSibling(TNode* node) {
    return (*node).getRightSibling();
}

TNode* AST::getParentTNode(TNode* node) {
    return (*node).getParentNode();
}

TNode* AST::getTNode(STMTLINE line) {
    std::map<STMTLINE,TNode*>::iterator it = stmt2NodeMap.find(line);
    if(it == stmt2NodeMap.end()) {
        return NULL;
    } else {
        return it->second;
    }
}

string AST::getValue(TNode* node) {
    return (*node).getValue();
}

bool AST::setStmtLine(TNode* node, STMTLINE stmtNumber) {
	map<STMTLINE, TNode*>::iterator it = stmt2NodeMap.find(stmtNumber);
	if(it != stmt2NodeMap.end()) return false;
    stmt2NodeMap[stmtNumber] = node;
    return true;
}

bool AST::setRoot(TNode* root) {
    rootNode = root;
	this->setRelationShip(root);
	this->setPKBRelationShips(root);
    return true;
}

TNode* AST::getRoot() {
    return rootNode;
}

void AST::addToStmtLineMap(TType type, STMTLINE stmtNumber) {
    TType2StmtMap.insert(std::pair<TType,STMTLINE>(type, stmtNumber));
}

vector<STMTLINE> AST::getStmtLines(TType type) {
    vector<STMTLINE> stmtList;
    if(type == TType::STMTN) {
        for(stmtIt = TType2StmtMap.begin(); stmtIt != TType2StmtMap.end(); ++stmtIt) {
            stmtList.push_back(stmtIt->second);
        }
    } else {
        stmtRet = TType2StmtMap.equal_range(type);
        for(stmtIt = stmtRet.first; stmtIt != stmtRet.second; ++stmtIt) {
            stmtList.push_back(stmtIt->second);
        }
    }
    return stmtList;
}

bool AST::isMatch(TNode* node, TType type) {
    return (*node).getTType() == type;
}

bool AST::matchLeftPattern(STMTLINE stmtRoot, VARINDEX varToMatch) {
    vector<TNode*> childList = getTNode(stmtRoot)->getChildren();
    if(childList.empty() || childList[0]->getTType() != VARN) {
        return false;
    } else {
		return (childList[0]->getValue() == PKB::getPKB()->getVarTable()->getVarName(varToMatch));
    }
	return false;
}

bool AST::matchRightPattern(STMTLINE stmtRoot, std::string expression, bool strict) {

	expression = "dummy="+ expression + ";";
	Tokenizer tokenizer = Tokenizer::Tokenizer();
	vector<ParsingToken> tokens;
	tokenizer.tokenizeLine(expression, 0, tokens);

	Parser parser = Parser::Parser(tokens);
	
	TNode* astNode = parser.buildNodeProcess(G_ASSIGN, 0).first;

	if(!strict){
		if(!(astNode->getChildren().size() < 2 || getTNode(stmtRoot)->getChildren().size() < 2)){
			TNode* node = getTNode(stmtRoot)->getChildren()[1];
			TNode* nodeToMatch = astNode->getChildren()[1];
			return node->contain(nodeToMatch);
		}

		return false;
	
	}
	else{

		if(!(astNode->getChildren().size() < 2 || getTNode(stmtRoot)->getChildren().size() < 2)){
			TNode* node = getTNode(stmtRoot);
			vector<TNode*> children1;
			node->getChildren()[1]->getAllChildrenIncludeSub(children1);
			children1.insert(children1.begin(), node->getChildren()[1]);


			vector<TNode*> children2;
			astNode->getChildren()[1]->getAllChildrenIncludeSub(children2);
			children2.insert(children2.begin(), astNode->getChildren()[1]);
			
			if(children1.size() == children2.size()){
				for(int i =0; i<children1.size(); i++){
					if(children1[i]->getTType() != children2[i]->getTType() || children1[i]->getValue() != children2[i]->getValue()){
						return false;
					}
				}
				return true;
			}

		}
			
		return false;

	}

}


void AST::setRelationShip(TNode* node){
	for(int i = 0; i < node->getChildren().size(); i++){
		
		TNode* child = node->getChildren()[i];
		child->setParentNode(node);
		if(child->getStmtLine() != -1){
			this->setStmtLine(child, child->getStmtLine());
		}

		if(node->getChildren().size() > i+1){
			TNode* rightChild = node->getChildren()[i+1];
			this->setSibling(child, rightChild);
		}

		this->setRelationShip(child);
	}

}

void AST::setPKBRelationShips(TNode* node){

	///////////////////////
	//parent & parentstar
	///////////////////////
	if(isPrimitiveNode(node)){
		TNode* parentNode = node->getParentNode();
		bool foundParent = false;
		while(parentNode->getTType() != EMPTYN){

			if(isPrimitiveNode(parentNode)){
				if(foundParent == false){		
					PKB::getPKB()->getParent()->setParent(parentNode->getStmtLine(), node->getStmtLine());
					PKB::getPKB()->getParent()->setParentStar(parentNode->getStmtLine(), node->getStmtLine());
					foundParent = true;
				}
				else{			//already found parent, next found parent should be parentstar only		
					PKB::getPKB()->getParent()->setParentStar(parentNode->getStmtLine(), node->getStmtLine());
				}
			}

			parentNode = parentNode->getParentNode();
		
		}
	}
	

	
	for(int i = 0; i < node->getChildren().size(); i++){
		
		///////////////////////
		//follow & followstar
		////////////////////////
		TNode* leftNode = node->getChildren()[i];
		TNode* rightNode = leftNode->getRightSibling();
		if(isPrimitiveNode(leftNode) && isPrimitiveNode(rightNode)){
			PKB::getPKB()->getFollows()->setFollows(leftNode->getStmtLine(), rightNode->getStmtLine());
		} 
		
		while(isPrimitiveNode(leftNode) && isPrimitiveNode(rightNode)){
			PKB::getPKB()->getFollows()->setFollowsStar(leftNode->getStmtLine(), rightNode->getStmtLine());
			rightNode = rightNode->getRightSibling();
		}

//----------------------------------------------------

		if(leftNode->getTType() == VARN){
			///////////////////////
			//vartable
			////////////////////////
			VARINDEX varIndex = PKB::getPKB()->getVarTable()->insertVar(leftNode->getValue());
			
			///////////////////////
			//modifies
			////////////////////////
			TNode* parentNode = leftNode->getParentNode();
			if(leftNode->getLeftSibling()->getTType() == EMPTYN && parentNode->getTType() == ASSIGNN){
				while(parentNode->getTType() != EMPTYN){
					if(isPrimitiveNode(parentNode)){
						PKB::getPKB()->getModifies()->setModifiesStmt(varIndex, parentNode->getStmtLine());
					}
					parentNode = parentNode->getParentNode();
				}

				
			}
		}

//----------------------------------------------------------------------

		if(leftNode->getTType() == ASSIGNN){
			vector<TNode*> children;
			vector<TNode*> usedVarNodes;

			leftNode->getAllChildrenIncludeSub(children);
			
			for(int i = 0; i < children.size(); i++){
				if((children[i]->getParentNode()->getTType() != ASSIGNN 
					|| children[i]->getLeftSibling()->getTType() != EMPTYN)
					&& children[i]->getTType() == VARN){
					usedVarNodes.push_back(children[i]);
				}
			}

			TNode* parentNode = leftNode;
			while(parentNode->getTType() != EMPTYN){
				if(isPrimitiveNode(parentNode)){
					for(int i = 0; i < usedVarNodes.size(); i++){
						///////////////////////
						//vartable & uses
						////////////////////////
						VARINDEX varIndex = PKB::getPKB()->getVarTable()->insertVar(usedVarNodes[i]->getValue());
						PKB::getPKB()->getUses()->setUsesStmt(varIndex, parentNode->getStmtLine());
					}
				}
				parentNode = parentNode->getParentNode();
			}
		}

//----------------------------------------------------------------------

		if(leftNode->getTType() == WHILEN || leftNode->getTType() == IFN){
			TNode* varNode = leftNode->getChildren()[0];
			///////////////////////
			//vartable & uses
			////////////////////////
			VARINDEX varIndex = PKB::getPKB()->getVarTable()->insertVar(varNode->getValue());
			TNode* parentNode = leftNode;
			while(parentNode->getTType() != EMPTYN){
				if(isPrimitiveNode(parentNode)){
					PKB::getPKB()->getUses()->setUsesStmt(varIndex, parentNode->getStmtLine());
				}
				parentNode = parentNode->getParentNode();
			}
		}

//----------------------------------------------------------------------

		this->setPKBRelationShips(leftNode);

	}
}

bool AST::isPrimitiveNode(TNode* node){
	TType type = node->getTType();

	return ((type == ASSIGNN || type == WHILEN || type == CALLN || type == IFN || type == PROCEDUREN) && node->getStmtLine() != -1);

}

