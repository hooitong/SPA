#include <algorithm>
#include <iostream>

#include "DesignExtractor.h"

#include "PKB.h"
#include "Follows.h"


/* Constructor & Destructor */
DesignExtractor::DesignExtractor(void) {
}

DesignExtractor::~DesignExtractor(void) {
}

void DesignExtractor::extract() {
    extractFollowsStar();
    extractParentStar();
    extractModifiesContainer();
    extractUsesContainer();
}

// method that extracts the Follows* relationship from the Follow map.
void DesignExtractor::extractFollowsStar() {
    PKB* pkbObj = PKB::getPKB();
    Follows* f = (*pkbObj).getFollows();
    vector<STMTLINE> allStmtLines = (*pkbObj).getAst()->getStmtLines(STMTN);

    // for each stmtline, set relation setFollowStar for every right sibling
    for (std::vector<int>::iterator it = allStmtLines.begin() ; it != allStmtLines.end(); ++it) {
        STMTLINE nextSibling = f->getFollowedBy(*it);
        while(nextSibling != -1) {
            f->setFollowsStar(*it, nextSibling);
            nextSibling = f->getFollowedBy(nextSibling);
        }
    }
}

// helper method that calls a recursive method to extract the relation.
void DesignExtractor::extractParentStar() {
    PKB* pkbObj = PKB::getPKB();
    Parent* p = (*pkbObj).getParent();
    STMTLINE root = 1;

    vector<STMTLINE> parents;
    recursiveExtractParent(p, root, parents);
}

// recursive method which starts from the root of the AST/Procedure and based on the parent mapping to
// set the necessary parent* relationship.
void DesignExtractor::recursiveExtractParent(Parent* pObj, STMTLINE root, vector<STMTLINE> parents) {
    // for each parent, set relation setParent* for each parent on current root
    for (std::vector<int>::iterator it = parents.begin(); it != parents.end(); ++it) {
        pObj->setParentStar(*it, root);
    }

    // add this stmtline to vector of parents
    parents.push_back(root);

    // for each child of current root, call recursive method
    vector<STMTLINE> children = pObj->getChildOf(root);
    for (std::vector<int>::iterator it = children.begin(); it != children.end(); ++it) {
        recursiveExtractParent(pObj, *it, parents);
    }

    // end of recursion
    return;
}

void DesignExtractor::extractModifiesContainer() {
    PKB* pkbObj = PKB::getPKB();
    vector<STMTLINE> aList = pkbObj->getAst()->getStmtLines(ASSIGNN);
    for(std::vector<STMTLINE>::iterator i = aList.begin(); i != aList.end(); ++i) {
        vector<STMTLINE> pList = pkbObj->getParent()->getParentStar(*i);
		vector<VARINDEX> vList = pkbObj->getModifies()->getModifiedByStmt(*i);
        for(std::vector<VARINDEX>::iterator k = vList.begin(); k != vList.end(); ++k) {
			for(std::vector<STMTLINE>::iterator j = pList.begin(); j != pList.end(); ++j) {
				if(!isModifiesDuplicate(*j, *k)) {
					pkbObj->getModifies()->setModifiesStmt(*k, *j);
				}
			}
        }
    }
}

void DesignExtractor::extractUsesContainer() {
	PKB* pkbObj = PKB::getPKB();
	vector<STMTLINE> aList = pkbObj->getAst()->getStmtLines(ASSIGNN);
	for(std::vector<STMTLINE>::iterator i = aList.begin(); i != aList.end(); ++i) {
		vector<STMTLINE> pList = pkbObj->getParent()->getParentStar(*i);
		vector<VARINDEX> vList = pkbObj->getUses()->getUsedByStmt(*i);
		for(std::vector<VARINDEX>::iterator k = vList.begin(); k != vList.end(); ++k) {
			for(std::vector<STMTLINE>::iterator j = pList.begin(); j != pList.end(); ++j) {
				if(!isUsesDuplicate(*j, *k)) {
					pkbObj->getUses()->setUsesStmt(*k, *j);
				}
			}
		}
	}
}

bool DesignExtractor::isModifiesDuplicate(STMTLINE source, VARINDEX item) {
	Modifies* mObj = PKB::getPKB()->getModifies();
	vector<VARINDEX> list = mObj->getModifiedByStmt(source);
	return find(list.begin(), list.end(), item) != list.end();
}

bool DesignExtractor::isUsesDuplicate(STMTLINE source, VARINDEX item) {
	Uses* uObj = PKB::getPKB()->getUses();
	vector<VARINDEX> list = uObj->getUsedByStmt(source);
	return find(list.begin(), list.end(), item) != list.end();
}