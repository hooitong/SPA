#include "Parser.h"

class SyntaxErrorException : public exception {
};

class InvalidNameException : public exception {
};

/*
	Remove comment in a line and return a list of tokens from that line
*/
vector<ParsingToken> Parser::tokenizeLine(string line) {
    vector<ParsingToken> tokenList;

    string currStr = "";
    for (size_t i=0; i<line.size(); i++) {
        char nextChar = line.at(i);
        if (nextChar == ' ' || nextChar == '\t') {
            if (currStr.size() > 0) {
                tokenList.push_back(Parser::convertStringToToken(currStr));
                currStr = "";
            }
        } else if (nextChar == '=' || nextChar == '+' || nextChar == '-' || nextChar == ';' || nextChar == '{' || nextChar == '}') {
            if (currStr.size() > 0) {
                tokenList.push_back(Parser::convertStringToToken(currStr));
            }
			currStr = string(1, nextChar);
            tokenList.push_back(Parser::convertStringToToken(currStr));
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
	} else if (Parser::isNumeric(aString)) {
		token.setTokenType(TokenType::CONSTANT);
		token.setIntValue(atoi(aString.c_str()));
	} else if (Parser::isValidName(aString)) {
		token.setTokenType(TokenType::NAME);
		token.setStringValue(aString);
	} else {
		throw InvalidNameException();
	}

	return token;
}

bool Parser::isNumeric(string aString) {
	for (int i=0; i<aString.size(); i++) {
		if (aString.at(i) < '0' || aString.at(i) > '9')
			return false;
	}
	return true;
}

bool Parser::isValidName(string aString) {
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
		}
		else {
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
