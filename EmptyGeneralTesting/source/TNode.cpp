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

void TNode::getAllChildrenIncludeSub(vector<TNode*> &children) {
    
	for(int i = 0; i<this->getChildren().size(); i ++){
		TNode* child = this->getChildren()[i];
		children.push_back(child);
		child->getAllChildrenIncludeSub(children);
	}

}


void TNode::getAllChildrenIncludeSubByTType(vector<TNode*> &children, TType type) {
    
	for(int i = 0; i<this->getChildren().size(); i ++){
		TNode* child = this->getChildren()[i];
		if(child->getTType() == type) children.push_back(child);
		child->getAllChildrenIncludeSubByTType(children, type);
	}

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


bool TNode::contain(TNode* node){

	vector<TNode*> children;
	this->getAllChildrenIncludeSub(children);
	children.insert(children.begin(), this);
	for(int i = 0; i<children.size(); i++){
		if(children[i]->getTType() == node->getTType() && children[i]->getValue() == node->getValue()){
			if(this->containSubProc(children[i], node)){
				return true;
			}
		}
	}
	return false;
}

bool TNode::containSubProc(TNode* node, TNode* toMatchNode){
	if(toMatchNode->getChildren().size() == 0 && node->getChildren().size() == 0) return true;

	if(node->getChildren().size() < toMatchNode->getChildren().size()) return false;

	bool result = false;

	for(int i = 0; i < toMatchNode->getChildren().size(); i++){
		
		if((toMatchNode->getChildren()[i]->getTType() == node->getChildren()[i]->getTType() 
			&& toMatchNode->getChildren()[i]->getValue() == node->getChildren()[i]->getValue())){
				result = this->containSubProc(node->getChildren()[i], toMatchNode->getChildren()[i]);
		}
		else{
			return false;
		}

		if(!result) break;

	}
	
	return result;

}

TNode* TNode::getParentByTType(TType type){
	TNode* parent = this->getParentNode();
	while(parent->getTType() != EMPTYN){
		if(parent->getTType() == type){
			return parent;
		}
		parent = parent->getParentNode();
	}
	return NULL;
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