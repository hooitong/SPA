#include "TNode.h"
#include <iostream>


TNode::TNode(void) {
	type = EMPTYN;
	stmtNumber = -1;
	parentNode = new TNode(false);
	leftSiblingNode = new TNode(false);
	rightSiblingNode = new TNode(false);
}

TNode::TNode(bool initalizedAdjacentNode){
	type = EMPTYN;
	stmtNumber = -1;
}

//The destructor should be first called by the root of the AST.
TNode::~TNode(void) {
    //delete rightSiblingNode;
    //childrenNodes.clear();
}

TType TNode::getTType() {
    return type;
}

string TNode::getValue() {
    return value;
}

bool TNode::setLeftSibling(TNode* leftSibling) {
    leftSiblingNode = leftSibling;
    return true;
}

bool TNode::setRightSibling(TNode* rightSibling) {
    rightSiblingNode = rightSibling;
    return true;
}

TNode* TNode::getLeftSibling() {
    return leftSiblingNode;
}

TNode* TNode::getRightSibling() {
    return rightSiblingNode;
}

bool TNode::setParentNode(TNode* node) {

	if(parentNode->getTType()!=EMPTYN) {
		return false;
		//already has parent, prevent it from resetting parent
	}
	
    parentNode = node;
    return true;
}

TNode* TNode::getParentNode() {
    return parentNode;
}

bool TNode:: addChild(TNode* node) {
    childrenNodes.push_back(node);
    return true;
}

void TNode:: setChildren(vector<TNode*> children) {
    childrenNodes = children;
}

vector<TNode*> TNode::getChildren() {
    return childrenNodes;
}

bool TNode::setStmtLine(STMTLINE stmtNo) {
    this->stmtNumber = stmtNo;
    return true;
}

STMTLINE TNode::getStmtLine() {
    return stmtNumber;
}

void TNode::setNodeValue(string s){
	value = s;
}

void TNode::setTType(TType t){
	 type = t;
}



void TNode::print(int lvl){

	if(lvl == 0) cout << "\n";

	string typeS;
	switch (type)
    {
        case PROGRAMN:   typeS = "PROGRAM"; break;
		case PROCEDUREN:   typeS = "PROCEDURE"; break;
		case STMTLSTN:   typeS = "STMTLST"; break;
		case CALLN:   typeS = "CALL"; break;
		case ASSIGNN:   typeS = "ASSIGN"; break;
		case VARN:   typeS = "VARIABLE"; break;
		case CONSTN:   typeS = "CONSTANT"; break;
		case UNKNOWNN:   typeS = "UNKNOWN"; break;
		case PLUSN:   typeS = "PLUS"; break;
		case MINUSN:   typeS = "MINUS"; break;
		case TIMESN:   typeS = "TIMES"; break;
		case EMPTYN:   typeS = "EMPTY"; break;
		case IFN:   typeS = "IF"; break;
		case WHILEN:   typeS = "WHILE"; break;
    }

	string tabs;
	int currentLevel = lvl;
	while(currentLevel>0){
		tabs += "  ";
		currentLevel--;
	}

	cout <<  tabs + typeS;
	if(value != ""){
		cout << "("+ value + ")";
	}
	if(stmtNumber > 0){
		cout << ":" << stmtNumber;
	}
	cout << "\n";
	vector<TNode*> children = getChildren();
	if(children.size()>0){
		for(int i =0; i<= children.size()-1; i++){
			children[i]->print(lvl+1);
		}
	}


}