#include "DesignExtractor.h"

#include <algorithm>

#include "PKB.h"
#include "Follows.h"


/* Constructor & Destructor */
DesignExtractor::DesignExtractor(void) {
}

DesignExtractor::~DesignExtractor(void) {
}

// public method that extracts all remaining relationships in the PKB
void DesignExtractor::extract() {
	setPKBRelationShips(PKB::getPKB()->getAst()->getRoot());
	setInterprocedureCallStar();
	setInterprocedureModifiesUses();
}



void DesignExtractor::setPKBRelationShips(TNode* node){

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
	
//----------------------------------------------------

	for(int i = 0; i < node->getChildren().size(); i++){
		
		TNode* leftNode = node->getChildren()[i];
		TNode* rightNode = leftNode->getRightSibling();
		if(isPrimitiveNode(leftNode) && isPrimitiveNode(rightNode)){
			///////////////////////
			//follow
			////////////////////////
			PKB::getPKB()->getFollows()->setFollows(leftNode->getStmtLine(), rightNode->getStmtLine());
			///////////////////////
			//cfg
			////////////////////////
			PKB::getPKB()->getCfg()->insert(leftNode->getStmtLine(), rightNode->getStmtLine(),
					PKB::getPKB()->getProcTable()->getProcIndex(leftNode->getParentByTType(PROCEDUREN)->getValue()));
		} 
		
		///////////////////////
		//followstar
		////////////////////////
		while(isPrimitiveNode(leftNode) && isPrimitiveNode(rightNode)){
			PKB::getPKB()->getFollows()->setFollowsStar(leftNode->getStmtLine(), rightNode->getStmtLine());
			rightNode = rightNode->getRightSibling();
		}

//----------------------------------------------------

		if(leftNode->getTType() == PROCEDUREN){
			//////////////////////
			//proctable
			/////////////////////
			PROCINDEX procIndex = PKB::getPKB()->getProcTable()->insertProc(leftNode->getValue());
		}

		if(leftNode->getTType() == CALLN){
			//////////////////////
			//proctable
			/////////////////////
			PROCINDEX calledIndex = PKB::getPKB()->getProcTable()->insertProc(leftNode->getValue());
			TNode* parentNode = leftNode->getParentNode();
			while(parentNode->getTType() != PROCEDUREN){
				parentNode = parentNode->getParentNode();
			}
			PROCINDEX callerIndex = PKB::getPKB()->getProcTable()->insertProc(parentNode->getValue());
			//////////////////////
			//calls
			/////////////////////
			PKB::getPKB()->getCalls()->setCalls(callerIndex, calledIndex);

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
						PROCINDEX procIndex = PKB::getPKB()->getProcTable()->insertProc(parentNode->getParentByTType(PROCEDUREN)->getValue());
						PKB::getPKB()->getModifies()->setModifiesProc(procIndex, varIndex);
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
						PROCINDEX procIndex = PKB::getPKB()->getProcTable()->insertProc(parentNode->getParentByTType(PROCEDUREN)->getValue());
						PKB::getPKB()->getUses()->setUsesProc(procIndex, varIndex);
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
					PROCINDEX procIndex = PKB::getPKB()->getProcTable()->insertProc(parentNode->getParentByTType(PROCEDUREN)->getValue());
					PKB::getPKB()->getUses()->setUsesProc(procIndex, varIndex);
				}
				parentNode = parentNode->getParentNode();
			}
		}
//---------------------------------------------------------------------

		///////////////////////
		//cfg
		////////////////////////
		if(leftNode->getTType() == WHILEN || leftNode->getTType() == IFN){
			TNode* firstChildNode = leftNode->getChildren()[1]->getChildren()[0];
			PKB::getPKB()->getCfg()->insert(leftNode->getStmtLine(), firstChildNode->getStmtLine(), 
							PKB::getPKB()->getProcTable()->getProcIndex(leftNode->getParentByTType(PROCEDUREN)->getValue()));
		}
		
		if(leftNode->getTType() == IFN){
			TNode* secondChildNode = leftNode->getChildren()[2]->getChildren()[0];
			PKB::getPKB()->getCfg()->insert(leftNode->getStmtLine(), secondChildNode->getStmtLine(),
							PKB::getPKB()->getProcTable()->getProcIndex(leftNode->getParentByTType(PROCEDUREN)->getValue()));
		}
		
//----------------------------------------------------------------------

		setPKBRelationShips(leftNode);

	}
}

void DesignExtractor::setInterprocedureCallStar(){
	vector<VARINDEX> procIndexes = PKB::getPKB()->getProcTable()->getAllProcIndex();
	
	for(int i = 0; i < procIndexes.size(); i++){
		vector<PROCINDEX> calledBy = PKB::getPKB()->getCalls()->getCalledBy(procIndexes[i]);
		vector<PROCINDEX> result;
		for(int q = 0; q < calledBy.size(); q++){
			recursiveInterprocedureCallStar(calledBy[q], calledBy[q], true, result);
		}
		for(int q = 0; q < result.size(); q++){
			PKB::getPKB()->getCalls()->setCallsStar(procIndexes[i], result[q]);
		}
	}
}

void DesignExtractor::recursiveInterprocedureCallStar(PROCINDEX currentProc, PROCINDEX originalProc, bool first, vector<PROCINDEX> &result){
	if(currentProc == originalProc && !first) return;

	result.push_back(currentProc);

	vector<PROCINDEX> calledBy = PKB::getPKB()->getCalls()->getCalledBy(currentProc);
	for(int q = 0; q < calledBy.size(); q++){
		result.push_back(calledBy[q]);
		recursiveInterprocedureCallStar(calledBy[q], originalProc, false, result);
	}
}

void DesignExtractor::setInterprocedureModifiesUses(){
	vector<VARINDEX> procIndexes = PKB::getPKB()->getProcTable()->getAllProcIndex();
	
	for(int i = 0; i < procIndexes.size(); i++){
		vector<PROCINDEX> calledByStarVec = PKB::getPKB()->getCalls()->getCalledByStar(procIndexes[i]);
		vector<VARINDEX> modifies, uses;
		for(int q = 0; q < calledByStarVec.size(); q++){
			vector<VARINDEX> calledByModifies = PKB::getPKB()->getModifies()->getModifiedByProc(calledByStarVec[q]);
			vector<VARINDEX> calledByUses = PKB::getPKB()->getUses()->getUsedByProc(calledByStarVec[q]);
			modifies.insert( modifies.end(), calledByModifies.begin(), calledByModifies.end());		
			uses.insert( uses.end(), calledByUses.begin(), calledByUses.end());
		}
		for(int q = 0; q< modifies.size(); q++){
			PKB::getPKB()->getModifies()->setModifiesProc(procIndexes[i], modifies[q]);
		}
		for(int q = 0; q< uses.size(); q++){
			PKB::getPKB()->getUses()->setUsesProc(procIndexes[i], uses[q]);
		}
	}

}


bool DesignExtractor::isPrimitiveNode(TNode* node){
	TType type = node->getTType();

	return ((type == ASSIGNN || type == WHILEN || type == CALLN || type == IFN) && node->getStmtLine() != -1);

}


