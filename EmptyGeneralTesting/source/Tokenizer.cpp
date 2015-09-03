#include "Tokenizer.h"
#include "Exception.h"
#include "ParserUtils.h"
#include <fstream>
#include <iostream>
#include <map>
#include <regex>

ifstream _stream;

Tokenizer::Tokenizer(string fileName){
    _stream.open(fileName);
}

Tokenizer::Tokenizer(void) {
}

Tokenizer::~Tokenizer(void) {
}

vector<ParsingToken> Tokenizer::start(){
	vector<ParsingToken> programTokenList;
	string str;
    int currLineIndex = 0;

    while (getline(_stream, str)) {

		int lineIndex = -1;
		if(Tokenizer::isCodeBody(str)){
			currLineIndex++;
			lineIndex = currLineIndex;
		}

		Tokenizer::tokenizeLine(str, lineIndex, programTokenList);
		
    }

	_stream.close();
	return programTokenList;
}

void Tokenizer::tokenizeLine(string line, int lineIndex, vector<ParsingToken> &tokenList) {
    line = Tokenizer::appendWhiteSpace(line);
	vector<string> tokens;
	tokens = ParserUtils::split(line, ' ');
	for(int i = 0; i<tokens.size(); i++){
		if(tokens[i].size() >= 2 && tokens[i].at(0) == '\\' && tokens[i].at(1) == '\\'){
			return; //return immediately as the rest of the line is commented
		}
		else{
			tokenList.push_back(ParsingToken::ParsingToken(tokens[i], lineIndex));
		}
	}
}

bool Tokenizer::isNumeric(string aString) {
    for (int i=0; i<aString.size(); i++) {
        if (aString.at(i) < '0' || aString.at(i) > '9')
            return false;
    }
    return true;
}

bool Tokenizer::isValidName(string aString) {
    if (aString.size() == 0)
        return false;
    else if (aString.compare("while") == 0 || aString.compare("if") == 0
             || aString.compare("else") == 0 || aString.compare("procedure") == 0) {
        // name cannot be one of reserved words
        return false;
    } else {
        if (aString.at(0) < 'A' || (aString.at(0) > 'Z' && aString.at(0) < 'a') || (aString.at(0) > 'z')) {
            // first character is not a letter
            return false;
        } else {
            for (int i=1; i<aString.size(); i++) {
                if ((aString.at(i) >= '0' && aString.at(i) <= '9') || (aString.at(i) >= 'a' && aString.at(i) <= 'z')
                        || (aString.at(i) >= 'A' && aString.at(i) <= 'Z')) {
                    // if ith character is a digit or a letter, then continue
                } else {
                    return false;
                }
            }
            return true;
        }
    }
}

string Tokenizer::appendWhiteSpace(string input){
  	
	vector<string> symbolList;
	symbolList.push_back(";");
	symbolList.push_back("{");
	symbolList.push_back("}");
	symbolList.push_back("(");
	symbolList.push_back(")");
	symbolList.push_back("*");
	symbolList.push_back("+");
	symbolList.push_back("=");
	for(int i=0; i <= symbolList.size() - 1 ; i++){
		ParserUtils::replaceAll(input, symbolList[i], " " + symbolList[i] + " ");
	}

	regex e ("[[:space:]]+");
	const string format=" ";
	input = regex_replace(input,e,format,regex_constants::format_default);

	return input;

}

bool Tokenizer::isCodeBody(string code){
	bool foundAlpha = false;
	ParserUtils::replaceAll(code," ","");

	for(std::string::iterator it = code.begin(); it != code.end(); ++it) {
		if (isalpha(*it)){
			foundAlpha = true;
			break;
		} 
	}


	if(!foundAlpha || foundAlpha && code.find("procedure") == 0){
		return false;
	}
	else{
		return foundAlpha;
	}

}
