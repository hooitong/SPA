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
	extractVariousRelationship(PKB::getPKB()->getAst()->getRoot());
	extractInterprocedureCallStar();
	extractInterprocedureModifiesUses();
	extractNext();
}


//
// parent, parentstar, follow, followstar, calls, modifies, cfg, vartable, proctable 
// are being extracted using this function
//
void DesignExtractor::extractVariousRelationship(TNode* node){

	///////////////////////
	//parent & parentstar
	///////////////////////
	if(isPrimaryNode(node)){
		TNode* parentNode = node->getParentNode();
		bool foundParent = false;
		while(parentNode->getTType() != EMPTYN){

			if(isPrimaryNode(parentNode)){
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
		if(isPrimaryNode(leftNode) && isPrimaryNode(rightNode)){
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
		while(isPrimaryNode(leftNode) && isPrimaryNode(rightNode)){
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
					if(isPrimaryNode(parentNode)){
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
				if(isPrimaryNode(parentNode)){
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
				if(isPrimaryNode(parentNode)){
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

		//while looping of last node to first in cfg
		if(leftNode->getTType() == WHILEN){
			vector<TNode*> children = leftNode->getChildren()[1]->getChildren();
			TNode* lastNode = children.at(children.size()-1);

			if(lastNode->getTType() == IFN){	//if last child node of while is IF node
				vector<TNode*> ifBranchChildren = lastNode->getChildren()[1]->getChildren();
				vector<TNode*> elseBranchChildren = lastNode->getChildren()[2]->getChildren();
				TNode* ifBranchLastNode = ifBranchChildren.at(ifBranchChildren.size()-1);
				TNode* elseBranchLastNode = elseBranchChildren.at(elseBranchChildren.size()-1);

				PKB::getPKB()->getCfg()->insert(ifBranchLastNode->getStmtLine(), leftNode->getStmtLine() ,
							PKB::getPKB()->getProcTable()->getProcIndex(leftNode->getParentByTType(PROCEDUREN)->getValue()));

				PKB::getPKB()->getCfg()->insert(elseBranchLastNode->getStmtLine(), leftNode->getStmtLine() ,
							PKB::getPKB()->getProcTable()->getProcIndex(leftNode->getParentByTType(PROCEDUREN)->getValue()));
			}
			else{
				PKB::getPKB()->getCfg()->insert(lastNode->getStmtLine(), leftNode->getStmtLine() ,
							PKB::getPKB()->getProcTable()->getProcIndex(leftNode->getParentByTType(PROCEDUREN)->getValue()));
			}

			
		}
	
		
//----------------------------------------------------------------------

		extractVariousRelationship(leftNode);

	}
}

//callstar in between different procedure is being extracted here
void DesignExtractor::extractInterprocedureCallStar(){
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

//modifies & uses in between different procedures is between extracted here
void DesignExtractor::extractInterprocedureModifiesUses(){
	vector<PROCINDEX> procIndexes = PKB::getPKB()->getProcTable()->getAllProcIndex();
	
	for(int i = 0; i < procIndexes.size(); i++){
		TNode* procedureNode = PKB::getPKB()->getAst()->getProcTNodeByIndex(procIndexes[i]);
		vector<TNode*> procedureCallNodes;
		procedureNode->getAllChildrenIncludeSubByTType(procedureCallNodes, CALLN);

		for(int b = 0; b < procedureCallNodes.size(); b++){
			PROCINDEX callingProcIndex = PKB::getPKB()->getProcTable()->getProcIndex(procedureCallNodes[b]->getValue());
			vector<TNode*> parents = procedureCallNodes[b]->getAllParentNodes();
			vector<PROCINDEX> calledByStarVec = PKB::getPKB()->getCalls()->getCalledByStar(callingProcIndex);
			vector<VARINDEX> modifies = PKB::getPKB()->getModifies()->getModifiedByProc(callingProcIndex);
			vector<VARINDEX> uses = PKB::getPKB()->getUses()->getUsedByProc(callingProcIndex);
			for(int q = 0; q < calledByStarVec.size(); q++){
				vector<VARINDEX> calledByModifies = PKB::getPKB()->getModifies()->getModifiedByProc(calledByStarVec[q]);
				vector<VARINDEX> calledByUses = PKB::getPKB()->getUses()->getUsedByProc(calledByStarVec[q]);

				modifies.insert( modifies.end(), calledByModifies.begin(), calledByModifies.end());		
				uses.insert( uses.end(), calledByUses.begin(), calledByUses.end());
			}
			for(int q = 0; q< modifies.size(); q++){
				PKB::getPKB()->getModifies()->setModifiesProc(procIndexes[i], modifies[q]);
				PKB::getPKB()->getModifies()->setModifiesStmt(modifies[q], procedureCallNodes[b]->getStmtLine());

				for(int z = 0; z < parents.size(); z++){
					if(isPrimaryNode(parents[z])){
						PKB::getPKB()->getModifies()->setModifiesStmt(modifies[q], parents[z]->getStmtLine());
					}
				}
			}
			for(int q = 0; q< uses.size(); q++){
				PKB::getPKB()->getUses()->setUsesProc(procIndexes[i], uses[q]);
				PKB::getPKB()->getUses()->setUsesStmt(uses[q], procedureCallNodes[b]->getStmtLine());

				for(int z = 0; z < parents.size(); z++){
					if(isPrimaryNode(parents[z])){
						PKB::getPKB()->getUses()->setUsesStmt(uses[q], parents[z]->getStmtLine());
					}
				}
			}

		}
	}
}


bool DesignExtractor::isPrimaryNode(TNode* node){
	TType type = node->getTType();

	return ((type == ASSIGNN || type == WHILEN || type == CALLN || type == IFN) && node->getStmtLine() != -1);

}

//next and nextstar is extracted in this function
void DesignExtractor::extractNext(){
	vector<GNode*> gNodes = PKB::getPKB()->getCfg()->getAllGNodes();
	for(int i = 0; i < gNodes.size(); i++){
		
		vector<GNode*> nodes = gNodes[i]->getForwardNodes();
		for(int q = 0; q< nodes.size(); q++){
			PKB::getPKB()->getNext()->setNext(gNodes[i]->getLineNumber(), nodes[q]->getLineNumber());
		}

		
		
		vector<GNode*> allNodes;
		gNodes[i]->getAllPossibleForwardNodes(gNodes[i]->getLineNumber(), allNodes);
		for(int q = 0; q< allNodes.size(); q++){
			PKB::getPKB()->getNext()->setNextStar(gNodes[i]->getLineNumber(), allNodes[q]->getLineNumber());
		}
	}


}
