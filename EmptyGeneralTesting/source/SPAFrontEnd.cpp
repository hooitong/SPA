#include "SPAFrontEnd.h"
#include <fstream>

void SPAFrontEnd::parseSource(const std::string fileName) {		// test parser
	std::ifstream sourceFile(fileName);

	if(sourceFile.is_open()) {
		/*
		string line;
		while (getline(sourceFile, line)) {
			vector<string> tokenList = Parser::tokenizeLine(line);
		}
		Parser::
		sourceFile.close();
		*/
	}
}