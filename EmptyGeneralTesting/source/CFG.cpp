#include "CFG.h"


CFG::CFG(void)
{
}



GNode createGNode(ProgLine nodeRoot){
}
bool setStmtNumber(ProgLine progLine){
}
bool addProgLine(GNode node, ProgLine progLine){
}
GNode getGNode(ProgLine progLine){
}
GNode getNextGNode(GNode current, bool getRight){
}
GNode getPreviousGNode(GNode current, bool getRight){
}
bool setNextGNode(GNode current, GNode next, bool direction){
}
bool setPreviousGNode(GNode current, GNode prevous, bool direction){
}
vector<ProgLine> getAllLine(GNode node){
}
bool setGRoot(GNode root){
}
vector<GNode> getGRoots(){
}

bool isNext(ProgLine firstLine, ProgLine secondLine){
}
bool isNextStar(ProgLine firstLine, ProgLine secondLine){
}
vector<ProgLine> getBefore(ProgLine currentLine){
}
vector<ProgLine> getBeforeStar (ProgLine currentLine){
}
vector <ProgLine> getNext(ProgLine currentLine){
}
vector <ProgLine> getNextStar(ProgLine currentLine){
}
CFG::~CFG(void)
{
}
