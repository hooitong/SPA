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
void DesignExtractor::extractVariousRelationship(TNode* node) {

  ///////////////////////
  //parent & parentstar
  ///////////////////////
  if (isPrimaryNode(node)) {
    TNode* parentNode = node->getParentNode();
    bool foundParent = false;
    while (parentNode->getTType() != EMPTYN) {

      if (isPrimaryNode(parentNode)) {
        if (foundParent == false) {
          PKB::getPKB()->getParent()->setParent(parentNode->getStmtLine(), node->getStmtLine());
          PKB::getPKB()->getParent()->setParentStar(parentNode->getStmtLine(), node->getStmtLine());
          foundParent = true;
        }
        else {			//already found parent, next found parent should be parentstar only		
          PKB::getPKB()->getParent()->setParentStar(parentNode->getStmtLine(), node->getStmtLine());
        }
      }

      parentNode = parentNode->getParentNode();

    }
  }

  //----------------------------------------------------

  for (int i = 0; i < node->getChildren().size(); i++) {

    TNode* leftNode = node->getChildren()[i];
    TNode* rightNode = leftNode->getRightSibling();
    if (isPrimaryNode(leftNode) && isPrimaryNode(rightNode)) {
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
    while (isPrimaryNode(leftNode) && isPrimaryNode(rightNode)) {
      PKB::getPKB()->getFollows()->setFollowsStar(leftNode->getStmtLine(), rightNode->getStmtLine());
      rightNode = rightNode->getRightSibling();
    }

    //----------------------------------------------------

    if (leftNode->getTType() == PROCEDUREN) {
      //////////////////////
      //proctable
      /////////////////////
      PROCINDEX procIndex = PKB::getPKB()->getProcTable()->insertProc(leftNode->getValue());
      PKB::getPKB()->getProcTable()->setTRoot(procIndex, leftNode);
    }

    if (leftNode->getTType() == CALLN) {
      //////////////////////
      //proctable
      /////////////////////
      PROCINDEX calledIndex = PKB::getPKB()->getProcTable()->insertProc(leftNode->getValue());
      PKB::getPKB()->getProcTable()->setTRoot(calledIndex, leftNode);
      TNode* parentNode = leftNode->getParentNode();
      while (parentNode->getTType() != PROCEDUREN) {
        parentNode = parentNode->getParentNode();
      }
      PROCINDEX callerIndex = PKB::getPKB()->getProcTable()->insertProc(parentNode->getValue());
      PKB::getPKB()->getProcTable()->setTRoot(callerIndex, parentNode);
      //////////////////////
      //calls
      /////////////////////
      PKB::getPKB()->getCalls()->setCalls(callerIndex, calledIndex);

    }



    //----------------------------------------------------

    if (leftNode->getTType() == VARN) {
      ///////////////////////
      //vartable
      ////////////////////////
      VARINDEX varIndex = PKB::getPKB()->getVarTable()->insertVar(leftNode->getValue());

      ///////////////////////
      //modifies
      ////////////////////////
      TNode* parentNode = leftNode->getParentNode();
      if (leftNode->getLeftSibling()->getTType() == EMPTYN && parentNode->getTType() == ASSIGNN) {
        while (parentNode->getTType() != EMPTYN) {
          if (isPrimaryNode(parentNode)) {
            PKB::getPKB()->getModifies()->setModifiesStmt(varIndex, parentNode->getStmtLine());
            TNode* procNode = parentNode->getParentByTType(PROCEDUREN);
            PROCINDEX procIndex = PKB::getPKB()->getProcTable()->insertProc(procNode->getValue());
            PKB::getPKB()->getProcTable()->setTRoot(procIndex, procNode);
            PKB::getPKB()->getModifies()->setModifiesProc(procIndex, varIndex);
          }
          parentNode = parentNode->getParentNode();
        }


      }
    }

    //----------------------------------------------------------------------

    if (leftNode->getTType() == ASSIGNN) {
      vector<TNode*> children;
      vector<TNode*> usedVarNodes;

      leftNode->getAllChildrenIncludeSub(children);

      for (int b = 0; b < children.size(); b++) {
        if ((children[b]->getParentNode()->getTType() != ASSIGNN
          || children[b]->getLeftSibling()->getTType() != EMPTYN)
          && children[b]->getTType() == VARN) {
          usedVarNodes.push_back(children[b]);
        }
      }

      TNode* parentNode = leftNode;
      while (parentNode->getTType() != EMPTYN) {
        if (isPrimaryNode(parentNode)) {
          for (int b = 0; b < usedVarNodes.size(); b++) {
            ///////////////////////
            //vartable & uses
            ////////////////////////
            VARINDEX varIndex = PKB::getPKB()->getVarTable()->insertVar(usedVarNodes[b]->getValue());
            PKB::getPKB()->getUses()->setUsesStmt(varIndex, parentNode->getStmtLine());
            TNode* procNode = parentNode->getParentByTType(PROCEDUREN);
            PROCINDEX procIndex = PKB::getPKB()->getProcTable()->insertProc(procNode->getValue());
            PKB::getPKB()->getProcTable()->setTRoot(procIndex, procNode);
            PKB::getPKB()->getUses()->setUsesProc(procIndex, varIndex);
          }
        }
        parentNode = parentNode->getParentNode();
      }
    }

    //----------------------------------------------------------------------

    if (leftNode->getTType() == WHILEN || leftNode->getTType() == IFN) {
      TNode* varNode = leftNode->getChildren()[0];
      ///////////////////////
      //vartable & uses
      ////////////////////////
      VARINDEX varIndex = PKB::getPKB()->getVarTable()->insertVar(varNode->getValue());
      TNode* parentNode = leftNode;
      while (parentNode->getTType() != EMPTYN) {
        if (isPrimaryNode(parentNode)) {
          PKB::getPKB()->getUses()->setUsesStmt(varIndex, parentNode->getStmtLine());
          TNode* procNode = parentNode->getParentByTType(PROCEDUREN);
          PROCINDEX procIndex = PKB::getPKB()->getProcTable()->insertProc(procNode->getValue());
          PKB::getPKB()->getProcTable()->setTRoot(procIndex, procNode);
          PKB::getPKB()->getUses()->setUsesProc(procIndex, varIndex);
        }
        parentNode = parentNode->getParentNode();
      }
    }
    //---------------------------------------------------------------------

        ///////////////////////
        //cfg
        ////////////////////////
    if (leftNode->getTType() == WHILEN || leftNode->getTType() == IFN) {
      TNode* firstChildNode = leftNode->getChildren()[1]->getChildren()[0];
      PKB::getPKB()->getCfg()->insert(leftNode->getStmtLine(), firstChildNode->getStmtLine(),
        PKB::getPKB()->getProcTable()->getProcIndex(leftNode->getParentByTType(PROCEDUREN)->getValue()));
    }

    if (leftNode->getTType() == IFN) {
      TNode* secondChildNode = leftNode->getChildren()[2]->getChildren()[0];
      PKB::getPKB()->getCfg()->insert(leftNode->getStmtLine(), secondChildNode->getStmtLine(),
        PKB::getPKB()->getProcTable()->getProcIndex(leftNode->getParentByTType(PROCEDUREN)->getValue()));
    }

    //while looping of last node to first in cfg
    if (leftNode->getTType() == WHILEN) {

      vector<TNode*> endPointNodes;
      getNodeEndPoints(leftNode, endPointNodes);
      for (int b = 0; b < endPointNodes.size(); b++) {
        PKB::getPKB()->getCfg()->insert(endPointNodes[b]->getStmtLine(), leftNode->getStmtLine(),
          PKB::getPKB()->getProcTable()->getProcIndex(leftNode->getParentByTType(PROCEDUREN)->getValue()));
      }

    }


    //----------------------------------------------------------------------

    extractVariousRelationship(leftNode);

  }
}

//callstar in between different procedure is being extracted here
void DesignExtractor::extractInterprocedureCallStar() {
  vector<VARINDEX> procIndexes = PKB::getPKB()->getProcTable()->getAllProcIndex();

  for (int i = 0; i < procIndexes.size(); i++) {
    vector<PROCINDEX> calledBy = PKB::getPKB()->getCalls()->getCalledBy(procIndexes[i]);
    vector<PROCINDEX> result;
    for (int q = 0; q < calledBy.size(); q++) {
      recursiveInterprocedureCallStar(calledBy[q], calledBy[q], true, result);
    }
    for (int q = 0; q < result.size(); q++) {
      PKB::getPKB()->getCalls()->setCallsStar(procIndexes[i], result[q]);
    }
  }
}

void DesignExtractor::recursiveInterprocedureCallStar(PROCINDEX currentProc, PROCINDEX originalProc, bool first, vector<PROCINDEX> &result) {
  if (currentProc == originalProc && !first) return;

  result.push_back(currentProc);

  vector<PROCINDEX> calledBy = PKB::getPKB()->getCalls()->getCalledBy(currentProc);
  for (int q = 0; q < calledBy.size(); q++) {
    result.push_back(calledBy[q]);
    recursiveInterprocedureCallStar(calledBy[q], originalProc, false, result);
  }
}

//modifies & uses in between different procedures is between extracted here
void DesignExtractor::extractInterprocedureModifiesUses() {
  vector<PROCINDEX> procIndexes = PKB::getPKB()->getProcTable()->getAllProcIndex();

  for (int i = 0; i < procIndexes.size(); i++) {
    TNode* procedureNode = PKB::getPKB()->getAst()->getProcTNodeByIndex(procIndexes[i]);
    vector<TNode*> procedureCallNodes;
    procedureNode->getAllChildrenIncludeSubByTType(procedureCallNodes, CALLN);

    for (int b = 0; b < procedureCallNodes.size(); b++) {
      PROCINDEX callingProcIndex = PKB::getPKB()->getProcTable()->getProcIndex(procedureCallNodes[b]->getValue());
      vector<TNode*> parents = procedureCallNodes[b]->getAllParentNodes();
      vector<PROCINDEX> calledByStarVec = PKB::getPKB()->getCalls()->getCalledByStar(callingProcIndex);
      vector<VARINDEX> modifies = PKB::getPKB()->getModifies()->getModifiedByProc(callingProcIndex);
      vector<VARINDEX> uses = PKB::getPKB()->getUses()->getUsedByProc(callingProcIndex);
      for (int q = 0; q < calledByStarVec.size(); q++) {
        vector<VARINDEX> calledByModifies = PKB::getPKB()->getModifies()->getModifiedByProc(calledByStarVec[q]);
        vector<VARINDEX> calledByUses = PKB::getPKB()->getUses()->getUsedByProc(calledByStarVec[q]);

        modifies.insert(modifies.end(), calledByModifies.begin(), calledByModifies.end());
        uses.insert(uses.end(), calledByUses.begin(), calledByUses.end());
      }
      for (int q = 0; q < modifies.size(); q++) {
        PKB::getPKB()->getModifies()->setModifiesProc(procIndexes[i], modifies[q]);
        PKB::getPKB()->getModifies()->setModifiesStmt(modifies[q], procedureCallNodes[b]->getStmtLine());

        for (int z = 0; z < parents.size(); z++) {
          if (isPrimaryNode(parents[z])) {
            PKB::getPKB()->getModifies()->setModifiesStmt(modifies[q], parents[z]->getStmtLine());
          }
        }
      }
      for (int q = 0; q < uses.size(); q++) {
        PKB::getPKB()->getUses()->setUsesProc(procIndexes[i], uses[q]);
        PKB::getPKB()->getUses()->setUsesStmt(uses[q], procedureCallNodes[b]->getStmtLine());

        for (int z = 0; z < parents.size(); z++) {
          if (isPrimaryNode(parents[z])) {
            PKB::getPKB()->getUses()->setUsesStmt(uses[q], parents[z]->getStmtLine());
          }
        }
      }

    }
  }
}


//next is extracted in this function
void DesignExtractor::extractNext() {
  vector<GNode*> gNodes = PKB::getPKB()->getCfg()->getAllGNodes();
  for (int i = 0; i < gNodes.size(); i++) {

    vector<GNode*> nodes = gNodes[i]->getForwardNodes();
    for (int q = 0; q < nodes.size(); q++) {
      PKB::getPKB()->getNext()->setNext(gNodes[i]->getLineNumber(), nodes[q]->getLineNumber());
    }

    //vector<GNode*> allNodes;
    //gNodes[i]->getAllPossibleForwardNodes(gNodes[i]->getLineNumber(), false, allNodes);
    //for (int q = 0; q < allNodes.size(); q++) {
    //  PKB::getPKB()->getNext()->setNextStar(gNodes[i]->getLineNumber(), allNodes[q]->getLineNumber());
    //}
  }


}


bool DesignExtractor::isPrimaryNode(TNode* node) {
  TType type = node->getTType();
  return ((type == ASSIGNN || type == WHILEN || type == CALLN || type == IFN) && node->getStmtLine() != -1);
}

//get node possible end points for each branch, multiple results for 'if' container
void DesignExtractor::getNodeEndPoints(TNode* node, vector<TNode*> &result) {
  vector<TNode*> children = node->getChildren();
  if (children.size() == 0) {
    result.push_back(node);
  }
  else {
    TNode* lastNode = children.at(children.size() - 1);
    if (!isPrimaryNode(lastNode)) {
      getNodeEndPoints(lastNode, result);
      return;
    }

    if (lastNode->getTType() != IFN) {
      result.push_back(lastNode);
    }
    else {
      TNode* ifBranchLastNode = lastNode->getChildren()[1];
      TNode* elseBranchLastNode = lastNode->getChildren()[2];
      getNodeEndPoints(ifBranchLastNode, result);
      getNodeEndPoints(elseBranchLastNode, result);
    }
  }
}
