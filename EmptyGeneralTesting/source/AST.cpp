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
	this->addToStmtLineMap(node->getTType(), stmtNumber);
    return true;
}

bool AST::setRoot(TNode* root) {
    rootNode = root;
	this->setRelationShip(root);
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

TNode* AST::getProcTNodeByIndex(PROCINDEX index){
	vector<TNode*> procedures;
	this->getRoot()->getAllChildrenIncludeSubByTType(procedures, PROCEDUREN);
	for(int i = 0; i < procedures.size(); i ++){
		if(PKB::getPKB()->getProcTable()->getProcIndex(procedures[i]->getValue()) == index){
			return procedures[i];
		}
	}
	return NULL;
}