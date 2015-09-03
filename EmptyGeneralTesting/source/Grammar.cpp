#include "Grammar.h"
#include "ParserUtils.h"

map<GrammarTType, string> _typeToStringMap;
map<GrammarTType, GrammarToken> _typeToTokenMap;


Grammar::Grammar(){	

}

Grammar::~Grammar(void) {
}

void Grammar::initiate(){
	_typeToStringMap.insert(make_pair<GrammarTType, string>(G_PROGRAM, "PROCEDURE+"));
	_typeToStringMap.insert(make_pair<GrammarTType, string>(G_PROCEDURE, "'procedure' PROC_NAME '{' STMTLST '}'"));
	_typeToStringMap.insert(make_pair<GrammarTType, string>(G_STMTLST, "STMT+"));
	_typeToStringMap.insert(make_pair<GrammarTType, string>(G_STMT, "CALL | WHILE | IF | ASSIGN"));
	_typeToStringMap.insert(make_pair<GrammarTType, string>(G_CALL, "'call' PROC_NAME ';'"));
	_typeToStringMap.insert(make_pair<GrammarTType, string>(G_WHILE, "'while' VAR_NAME '{' STMTLST '}'"));
	_typeToStringMap.insert(make_pair<GrammarTType, string>(G_IF, "'if' VAR_NAME 'then' '{' STMTLST '}' 'else' '{' STMTLST '}'"));
	_typeToStringMap.insert(make_pair<GrammarTType, string>(G_ASSIGN, "VAR_NAME '=' EXPR ';'"));
	_typeToStringMap.insert(make_pair<GrammarTType, string>(G_EXPR, "EXPR '+' TERM | EXPR '-' TERM | TERM"));
	_typeToStringMap.insert(make_pair<GrammarTType, string>(G_TERM, "TERM '*' FACTOR | FACTOR"));
	_typeToStringMap.insert(make_pair<GrammarTType, string>(G_FACTOR, "VAR_NAME | CONST_VALUE | '(' EXPR ')'"));
	_typeToStringMap.insert(make_pair<GrammarTType, string>(G_VAR_NAME, "NAME"));
	_typeToStringMap.insert(make_pair<GrammarTType, string>(G_PROC_NAME, "NAME"));
	_typeToStringMap.insert(make_pair<GrammarTType, string>(G_CONST_VALUE, "INTEGER"));
	_typeToTokenMap = convertStringMapToTokenMap(_typeToStringMap);
}

GrammarToken Grammar::getTokenByType(GrammarTType type){
	return _typeToTokenMap.find(type)->second;
}


map<GrammarTType, GrammarToken> Grammar::convertStringMapToTokenMap(map<GrammarTType, string> typeToStringMap){

	map<GrammarTType, GrammarToken> typeToTokenMap;
	
	map<string, GrammarTType> stringToTypeMap;
	stringToTypeMap.insert(make_pair<string, GrammarTType>("PROCEDURE", G_PROCEDURE));
	stringToTypeMap.insert(make_pair<string, GrammarTType>("PROGRAM", G_PROGRAM));
	stringToTypeMap.insert(make_pair<string, GrammarTType>("STMTLST", G_STMTLST));
	stringToTypeMap.insert(make_pair<string, GrammarTType>("STMT", G_STMT));
	stringToTypeMap.insert(make_pair<string, GrammarTType>("CALL", G_CALL));
	stringToTypeMap.insert(make_pair<string, GrammarTType>("WHILE", G_WHILE));
	stringToTypeMap.insert(make_pair<string, GrammarTType>("IF", G_IF));
	stringToTypeMap.insert(make_pair<string, GrammarTType>("ASSIGN", G_ASSIGN));
	stringToTypeMap.insert(make_pair<string, GrammarTType>("EXPR", G_EXPR));
	stringToTypeMap.insert(make_pair<string, GrammarTType>("TERM", G_TERM));
	stringToTypeMap.insert(make_pair<string, GrammarTType>("FACTOR", G_FACTOR));
	stringToTypeMap.insert(make_pair<string, GrammarTType>("VAR_NAME", G_VAR_NAME));
	stringToTypeMap.insert(make_pair<string, GrammarTType>("PROC_NAME", G_PROC_NAME));
	stringToTypeMap.insert(make_pair<string, GrammarTType>("CONST_VALUE", G_CONST_VALUE));
	stringToTypeMap.insert(make_pair<string, GrammarTType>("NAME", G_NAME));
	stringToTypeMap.insert(make_pair<string, GrammarTType>("INTEGER", G_INTEGER));

	int z = 0;
	typedef map<GrammarTType, string>::iterator it_type;
	for(it_type iterator = typeToStringMap.begin(); iterator != typeToStringMap.end(); iterator++) {
		
	
		vector<string> syntaxArr = ParserUtils::split(iterator->second, '|');
		vector<vector<GrammarToken>> possibleTokensList;

		for (unsigned i=0; i < syntaxArr.size(); i++) {
			vector<GrammarToken> tokens;
			vector<string> subSyntaxArr = ParserUtils::split(syntaxArr[i], ' ');
			
			for (unsigned q=0; q < subSyntaxArr.size(); q++) {

				bool allowMultiple = false;
				if(subSyntaxArr[q].find("+") != std::string::npos
					&& subSyntaxArr[q].find("'") == std::string::npos){
					allowMultiple = true;
					ParserUtils::replaceAll(subSyntaxArr[q], "+", "");
				}

				map<string, GrammarTType>::iterator p;
				p = stringToTypeMap.find(subSyntaxArr[q]);

				if ( p != stringToTypeMap.end() ) {
					GrammarTType anotherType = p->second;
					GrammarToken token = GrammarToken::GrammarToken(p->second);
					if(allowMultiple) token.setAllowMultiple();
					tokens.push_back(token);
				} 
				else{
					ParserUtils::replaceAll(subSyntaxArr[q], "'", "");
					GrammarToken token = GrammarToken::GrammarToken(G_TEXT);
					token.setString(subSyntaxArr[q]);
					tokens.push_back(token);
				}
				
			}

			possibleTokensList.push_back(tokens);

		}

	
		GrammarTType type = iterator->first;
		GrammarToken insertingToken = GrammarToken::GrammarToken(iterator->first);
		insertingToken.addExpectedTokensList(possibleTokensList);
		typeToTokenMap.insert(make_pair<GrammarTType, GrammarToken>(type, insertingToken));
		
	}

	return typeToTokenMap;

}


