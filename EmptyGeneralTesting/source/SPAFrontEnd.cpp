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
	try
	{
	   Parser::parse(fileName);
	   Parser::buildAst();
	} catch (SyntaxErrorException e) {
        cout << e.message();
        exit (EXIT_FAILURE);
    } catch (InvalidNameException e) {
        cout << e.message();
        exit (EXIT_FAILURE);
    } catch (InvalidProcedureException e) {
        cout << e.message();
        exit (EXIT_FAILURE);
    }


    // Call DesignExtractor static method to parse AST further into PKB.
    DesignExtractor::extract();
}