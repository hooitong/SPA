#include "GrammarToken.h"

vector<vector<GrammarToken>> _expectedTokensList;
bool _allowMultiple = false;
string _text;
GrammarTType _type = G_EMPTY;


GrammarToken::GrammarToken(GrammarTType type){
	GrammarToken::_type = type;
	GrammarToken::_allowMultiple = false;
}

void GrammarToken::setString(string text){
	GrammarToken::_text = text;
}

string GrammarToken::getString(){
	return GrammarToken::_text;
}

void GrammarToken::addExpectedToken(GrammarToken expectedToken){
	vector<GrammarToken> tokens;
	tokens.push_back(expectedToken);
	GrammarToken::_expectedTokensList.push_back(tokens);
}

void GrammarToken::addExpectedTokens(vector<GrammarToken> expectedTokens){
	GrammarToken::_expectedTokensList.push_back(expectedTokens);	
}

void GrammarToken::addExpectedTokensList(vector<vector<GrammarToken>> expectedTokensList){
	GrammarToken::_expectedTokensList = expectedTokensList;	
}

vector<vector<GrammarToken>> GrammarToken::getExpectedTokensList(){
	return GrammarToken::_expectedTokensList;
}

void GrammarToken::setAllowMultiple(){
	GrammarToken::_allowMultiple = true;
}

bool GrammarToken::isAllowMultiple(){
	return GrammarToken::_allowMultiple;
}

GrammarTType GrammarToken::getType(){
	return GrammarToken::_type;
}

void GrammarToken::setType(GrammarTType type){
	GrammarToken::_type = type;
}