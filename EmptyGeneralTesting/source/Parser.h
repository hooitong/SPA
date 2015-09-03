#pragma once
#include <map>
#include <vector>
#include <string>
#include "ParserUtils.h"
#include "GlobalType.h"
#include "ParsingToken.h"
#include "AST.h"
#include <stdlib.h>
#include "Exception.h"
#include "Tokenizer.h"
#include "Grammar.h"
#include "PKB.h"
#include "PKB.h"

class Parser {

  public:
    Parser(void);
    ~Parser(void);

    static void parse(string filename);
	static TNode* buildAst();

	static pair<TNode*, int> buildExprNodeProcess(int index, int endIndex);


  private:
    static vector<ParsingToken> programTokenList;
		
	static pair<TNode*, int> buildNodeProcess(GrammarTType currentTokenType, int index);

	static TNode* createVarOrConstNode(ParsingToken token);
	static int getNextSemiColonIndex(int index);
	static TType convertSymbolToTType(string symbol);
	static vector<TNode*> prioritizeExpr(vector<ParsingToken> &tokens);
	static TNode* combinePriotizedNodes(vector<TNode*> &nodes);
	static Grammar grammar;
	
};