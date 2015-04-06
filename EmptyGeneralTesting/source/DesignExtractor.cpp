#include "DesignExtractor.h"

#include "PKB.h"
#include "Follows.h"

DesignExtractor* DesignExtractor::deObj;

/* Constructor & Destructor */
DesignExtractor::DesignExtractor(void) {
}

DesignExtractor::~DesignExtractor(void) {
}

DesignExtractor* DesignExtractor::getInstance() {
    if(deObj == NULL) {
        deObj = new DesignExtractor;
    }
    return deObj;
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
    STMTLINE root = (*pkbObj).getAst()->getRoot()->getStmtLine();
    vector<STMTLINE> parents;
    recursiveExtractParent(p, root, parents);
}

// recursive method which starts from the root of the AST/Procedure and based on the parent mapping to
// set the necessary parent* relationship.
void DesignExtractor::recursiveExtractParent(Parent* pObj, STMTLINE root, vector<STMTLINE> parents) {
    // for each parent, set relation setParent* for each parent on current root
    for (std::vector<int>::iterator it = parents.begin() ; it != parents.end(); ++it) {
        pObj->setParentStar(*it, root);
    }

    // add this stmtline to vector of parents
    parents.push_back(root);

    // for each child of current root, call recursive method
    vector<STMTLINE> children = pObj->getChildOf(root);
    for (std::vector<int>::iterator it = children.begin() ; it != children.end(); ++it) {
        recursiveExtractParent(pObj, *it, parents);
    }

    // end of recursion
    return;
}