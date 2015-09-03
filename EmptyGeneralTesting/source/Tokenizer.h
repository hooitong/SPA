#pragma once

#include <string>
#include "ParsingToken.h"
#include "vector"
#include <fstream>
#include <iostream>
#include "Exception.h"
#include "ParserUtils.h"
#include <map>
#include <regex>


class Tokenizer {
  public:
    Tokenizer(string fileName);
	Tokenizer();
	vector<ParsingToken> start();
	void tokenizeLine(string line, int lineIndex, vector<ParsingToken> &tokenList); 

  private:
	
	 bool isCodeBody(string code);
	 string appendWhiteSpace(string input);

};