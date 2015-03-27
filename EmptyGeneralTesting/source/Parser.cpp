#include "Parser.h"

class SyntaxErrorException : public exception {
};

/*
	Remove comment in a line and return a list of tokens from that line
*/
vector<string> Parser::tokenizeLine(string line) {
    vector<string> tokenList;

    string currStr = "";
    for (size_t i=0; i<line.size(); i++) {
        char nextChar = line.at(i);
        if (nextChar == ' ' || nextChar == '\t') {
            if (currStr.size() > 0) {
                tokenList.push_back(currStr);
                currStr = "";
            }
        } else if (nextChar == '=' || nextChar == '+' || nextChar == ';' || nextChar == '{' || nextChar == '}') {
            if (currStr.size() > 0) {
                tokenList.push_back(currStr);
            }
            tokenList.push_back(string(1, nextChar));
            currStr = "";
        } else if (nextChar == '\\') {
            if (i == line.size() - 1) {
                throw SyntaxErrorException();
            } else if (line.at(i+1) == '\\') {  // Ignore comments
                return tokenList;
            } else {
                throw SyntaxErrorException();
            }
        } else if ((nextChar >= 'a' && nextChar <= 'z') || (nextChar >= 'A' && nextChar <= 'Z') || (nextChar >= '0' && nextChar <= '9')) {
            currStr.push_back(nextChar);
        }
    }

    return tokenList;
}

ParsingToken Parser::convertStringToToken(string aString) {
	ParsingToken token;
	if (aString.compare("procedure") == 0) {
		token.setTokenType(TokenType::PROCEDURE_TOKEN);
	} else if (aString.compare("while") == 0) {
		token.setTokenType(TokenType::WHILE_TOKEN);
	} else if (aString.compare("if") == 0) {
		token.setTokenType(TokenType::IF_TOKEN);
	} else if (aString.compare("else") == 0) {
		token.setTokenType(TokenType::ELSE_TOKEN);
	} else if (aString.compare("=") == 0) {
		token.setTokenType(TokenType::ASSIGNMENT_TOKEN);
	} else if (aString.compare("+") == 0) {
		token.setTokenType(TokenType::PLUS);
	} else if (aString.compare("-") == 0) {
		token.setTokenType(TokenType::MINUS);
	} else if (aString.compare(";") == 0) {
		token.setTokenType(TokenType::SEMICOLON);
	} else if (aString.compare("{") == 0) {
		token.setTokenType(TokenType::OPEN_CURLY_BRACKET);
	} else if (aString.compare("}") == 0) {
		token.setTokenType(TokenType::CLOSE_CURLY_BRACKET);
	} 

	return token;
}

