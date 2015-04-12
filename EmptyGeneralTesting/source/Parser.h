#pragma once
#include <map>
#include <vector>
#include <string>
#include "GlobalType.h"
#include "ParsingToken.h"
#include "AST.h"
#include "Exception.h"

class Parser {

  public:
    Parser(void);
    ~Parser(void);

    static void parse(string filename);
    static TNode* buildExprAST(string expression);

    static string convertIntToString(int i);

  private:
    static vector<ParsingToken*> programTokenList;

    static void tokenizeLine(string line, int lineIndex, vector<ParsingToken*> *tokenList);
    static void buildProcedureAST();
    static TNode* buildExprAST(vector<ParsingToken *> exprTokenList, STMTLINE stmtLine, int displayedLineIndex);
    static TNode* buildExprAST(vector<ParsingToken *> exprTokenList);

    static ParsingToken* convertStringToToken(string aString, int lineIndex);
    static bool isNumeric(string aString);
    static bool isValidName(string aString);

    static void linkTNodes(TNode *parentNode, TNode *leftNode, TNode *rightNode);
    static void linkTNodeToPrevNodes(TNode *currNode, TNode *prevNode, TNodeRelation expectedRelation);

    static void addVarToUses(VARNAME varName, STMTLINE stmt);
    static void addVarToModifies(VARNAME varName, STMTLINE stmt);

    static string getStringIndexOfVar(VARNAME varName);
};