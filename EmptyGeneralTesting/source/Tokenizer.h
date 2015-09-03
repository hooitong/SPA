#pragma once

#include <string>
#include "ParsingToken.h"
#include "vector"

class Tokenizer {
  public:
    Tokenizer(string fileName);
    ~Tokenizer(void);
	Tokenizer();
	 
	vector<ParsingToken> start();
	void tokenizeLine(string line, int lineIndex, vector<ParsingToken> &tokenList); 

  private:
	
	 bool isCodeBody(string code);
	 bool isNumeric(string aString);
	 bool isValidName(string aString);
	 string appendWhiteSpace(string input);

};