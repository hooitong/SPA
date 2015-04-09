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
    // call Parser static method to parse given file into AST.
    Parser::parse(fileName);

    // Call DesignExtractor static method to parse AST further into PKB.
    DesignExtractor::extract();
}