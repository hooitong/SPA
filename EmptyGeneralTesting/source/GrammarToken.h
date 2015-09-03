#pragma once

#include "GlobalType.h"
#include <vector>
#include <string>

class GrammarToken {

  public:
	GrammarToken(GrammarTType type);

	void setAllowMultiple();
	void setString(string);
	void addExpectedToken(GrammarToken expectedToken);
	void addExpectedTokens(vector<GrammarToken> expectedTokens);
	void addExpectedTokensList(vector<vector<GrammarToken>> expectedTokens);
	vector<vector<GrammarToken>> getExpectedTokensList();

	string getString();
	GrammarTType getType();
	void setType(GrammarTType type);
	bool isAllowMultiple();

  private:
	 vector<vector<GrammarToken>> _expectedTokensList;
	 bool _allowMultiple;
	 GrammarTType _type;
	 string _text;
};