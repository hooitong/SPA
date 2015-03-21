#include "CFG.h"


CFG::CFG(void)
{
}



GNode createGNode(PROGLINE nodeRoot){
	return GNode();
}
bool setStmtNumber(PROGLINE PROGLINE){
	return true;
}
bool addPROGLINE(GNode node, PROGLINE PROGLINE){
	return true;
}
GNode getGNode(PROGLINE PROGLINE){
	return GNode();
}
GNode getNextGNode(GNode current, bool getRight){
	return GNode();	
}
GNode getPreviousGNode(GNode current, bool getRight){
	return GNode();
}
bool setNextGNode(GNode current, GNode next, bool direction){
	return true;
}
bool setPreviousGNode(GNode current, GNode prevous, bool direction){
	return true;
}
vector<PROGLINE> getAllLine(GNode node){
	vector<PROGLINE> a;
	return a;
}
bool setGRoot(GNode root){
	return true;
}
vector<GNode> getGRoots(){
	vector<GNode> g;
	return g;
}

bool isNext(PROGLINE firstLine, PROGLINE secondLine){
	return true;
}
bool isNextStar(PROGLINE firstLine, PROGLINE secondLine){
	return true;
}
vector<PROGLINE> getBefore(PROGLINE currentLine){
	vector<PROGLINE>p;
	return p;
}
vector<PROGLINE> getBeforeStar (PROGLINE currentLine){
	vector<PROGLINE>p;
	return p;

}
vector <PROGLINE> getNext(PROGLINE currentLine){
	vector<PROGLINE>p;
	return p;

}
vector <PROGLINE> getNextStar(PROGLINE currentLine){
	vector<PROGLINE>p;
	return p;
}
CFG::~CFG(void)
{
}
