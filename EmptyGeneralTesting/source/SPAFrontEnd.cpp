#include "SPAFrontEnd.h"

SPAFrontEnd* SPAFrontEnd::feObj;

SPAFrontEnd::SPAFrontEnd(void) {
}

SPAFrontEnd::~SPAFrontEnd(void) {
}

SPAFrontEnd* SPAFrontEnd::getInstance() {
    if(feObj == NULL) {
        feObj = new SPAFrontEnd;
    }

    return feObj;
}

void SPAFrontEnd::parseSource(const std::string fileName) {
    // call Parser static method to parse given file into AST
    Parser::parse(fileName);

    // get design extractor and call all the extract methods
    deObj = DesignExtractor::getInstance();
    deObj->extractFollowsStar();
    deObj->extractParentStar();
}