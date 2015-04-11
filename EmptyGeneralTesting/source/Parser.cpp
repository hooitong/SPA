#include "Parser.h"
#include "PKB.h"
#include <stack>
#include <fstream>

class SyntaxErrorException : public exception {
};

class InvalidNameException : public exception {
};

class InvalidProcedureException : public SyntaxErrorException {
};

class InvalidExpressionException : public SyntaxErrorException {
};

class InvalidWhileStmtException: public SyntaxErrorException {
};

vector<ParsingToken*> Parser::programTokenList;

// parse source code from file
void Parser::parse(string filename) {
	ifstream sourceFile;
	sourceFile.open(filename);
	string line;
	programTokenList.clear();
	while (getline(sourceFile, line)) {
		Parser::tokenizeLine(line, &programTokenList);
	}

	Parser::buildProcedureAST();
}

/*
	Remove comment in a line and return a list of tokens from that line
*/
void Parser::tokenizeLine(string line, vector<ParsingToken*> *tokenList) {
    string currStr = "";
    for (size_t i=0; i<line.size(); i++) {
        char nextChar = line.at(i);
        if (nextChar == ' ' || nextChar == '\t') {
            if (currStr.size() > 0) {
                tokenList->push_back(Parser::convertStringToToken(currStr));
                currStr = "";
            }
        } else if (nextChar == '=' || nextChar == '+' || nextChar == '-' || nextChar == ';' || nextChar == '{' || nextChar == '}') {
            if (currStr.size() > 0) {
                tokenList->push_back(Parser::convertStringToToken(currStr));
            }
			currStr = string(1, nextChar);
            tokenList->push_back(Parser::convertStringToToken(currStr));
			currStr = "";
        } else if (nextChar == '\\') {
            if (i == line.size() - 1) {
                throw SyntaxErrorException();
            } else if (line.at(i+1) == '\\') {  // Ignore comments
                return;
            } else {
                throw SyntaxErrorException();
            }
        } else if ((nextChar >= 'a' && nextChar <= 'z') || (nextChar >= 'A' && nextChar <= 'Z') || (nextChar >= '0' && nextChar <= '9')) {
            currStr.push_back(nextChar);
        }
    }

	if(currStr.size() > 0) {
		tokenList->push_back(Parser::convertStringToToken(currStr));
		currStr = "";
	}

    return;
}

ParsingToken* Parser::convertStringToToken(string aString) {
	ParsingToken* token = new ParsingToken();
	if (aString.compare("procedure") == 0) {
		token->setTokenType(TokenType::PROCEDURE_TOKEN);
	} else if (aString.compare("while") == 0) {
		token->setTokenType(TokenType::WHILE_TOKEN);
	} else if (aString.compare("if") == 0) {
		token->setTokenType(TokenType::IF_TOKEN);
	} else if (aString.compare("else") == 0) {
		token->setTokenType(TokenType::ELSE_TOKEN);
	} else if (aString.compare("=") == 0) {
		token->setTokenType(TokenType::ASSIGNMENT_TOKEN);
	} else if (aString.compare("+") == 0) {
		token->setTokenType(TokenType::PLUS);
	} else if (aString.compare("-") == 0) {
		token->setTokenType(TokenType::MINUS);
	} else if (aString.compare(";") == 0) {
		token->setTokenType(TokenType::SEMICOLON);
	} else if (aString.compare("{") == 0) {
		token->setTokenType(TokenType::OPEN_CURLY_BRACKET);
	} else if (aString.compare("}") == 0) {
		token->setTokenType(TokenType::CLOSE_CURLY_BRACKET);
	} else if (Parser::isNumeric(aString)) {
		token->setTokenType(TokenType::CONSTANT);
		token->setIntValue(atoi(aString.c_str()));
	} else if (Parser::isValidName(aString)) {
		token->setTokenType(TokenType::NAME);
		token->setStringValue(aString);
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

// build the AST for a procedure
void Parser::buildProcedureAST() {
	PKB *pkb = PKB::getPKB();
	AST *ast = pkb->getAst();

	if (programTokenList.size() < 8) {  // if the number of tokens in the procedure is less than 8, then the procedure is invalid
		throw InvalidProcedureException();
	}

	// if the procedure does not start with the format procedure proc_name {, then return invalid
	if (programTokenList.at(0)->getTokenType() != TokenType::PROCEDURE_TOKEN || programTokenList.at(1)->getTokenType() != TokenType::NAME
		|| programTokenList.at(2)->getTokenType() != TokenType::OPEN_CURLY_BRACKET) {
		throw InvalidProcedureException();
	}

	// set up the AST 
	TNode *procedureNode = new TNode(TType::PROCEDUREN, programTokenList.at(1)->getStringValue());
	ast->setRoot(procedureNode);
	TNode *stmtLstNode = new TNode(TType::STMTLSTN, "");
	ast->addChildTNode(procedureNode, stmtLstNode);
	TNode *prevNode = stmtLstNode;
	TNodeRelation expectedRelation = TNodeRelation::CHILD;

	int i=3;
	int stmtLine = 1;
	while (i < programTokenList.size()) {
		if (programTokenList.at(i)->getTokenType() == TokenType::NAME) { // assignment statement  
			// if the fisrt token of the statement is a name, then the statement is an assignment
			if (programTokenList.at(i+1)->getTokenType() != TokenType::ASSIGNMENT_TOKEN)
				throw SyntaxErrorException();
			
			// add the variable to varTable and Modifies Table
			PKB::getPKB()->getVarTable()->insertVar(programTokenList.at(i)->getStringValue());
			Parser::addVarToModifies(programTokenList.at(i)->getStringValue(), stmtLine);
			string varName = programTokenList.at(i)->getStringValue();
			TNode *varNode = new TNode(TType::VARN, Parser::getStringIndexOfVar(varName));

			// parse the expression on the right hand side of the assignment
			int j = i+2;
			vector<ParsingToken *> exprTokenList;
			while (programTokenList.at(j)->getTokenType() != TokenType::SEMICOLON) {
				exprTokenList.push_back(programTokenList.at(j));
				j++;
			}
			i = j+1; // move i to after the SEMICOLON position
			TNode *exprNode = Parser::buildExprAST(exprTokenList, stmtLine);
			TNode *assignNode = new TNode(TType::ASSIGNN, "");
			assignNode->setStmtLine(stmtLine);
			ast->setStmtLine(assignNode, stmtLine);
			ast->addToStmtLineMap(TType::ASSIGNN, stmtLine);
			stmtLine++;
			Parser::linkTNodes(assignNode, varNode, exprNode);
			
			// link assignNode to previous nodes on the AST
			Parser::linkTNodeToPrevNodes(assignNode, prevNode, expectedRelation);
			
			// prevNode now points to assignNode to parse the next statement
			prevNode = assignNode;
			expectedRelation = TNodeRelation::RIGHT_SIBLING;
		} else if (programTokenList.at(i)->getTokenType() == TokenType::WHILE_TOKEN) { // while statement
			if (programTokenList.at(i+1)->getTokenType() != TokenType::NAME || programTokenList.at(i+2)->getTokenType() != TokenType::OPEN_CURLY_BRACKET) {
				// if the statement does not follow the format 'while var_name {' then thow exception
				throw InvalidWhileStmtException();
			} else {
				i = i+3; // move i to after the open curly bracket
				TNode *whileNode = new TNode(TType::WHILEN, "");
				whileNode->setStmtLine(stmtLine);
				ast->setStmtLine(whileNode, stmtLine);
				ast->addToStmtLineMap(TType::WHILEN, stmtLine);
				stmtLine++;
				
				string varName = programTokenList.at(i-2)->getStringValue();
				PKB::getPKB()->getVarTable()->insertVar(varName);
				Parser::addVarToUses(varName, stmtLine-1);

				// link whileNode to varNode
				TNode *varNode = new TNode(TType::VARN, Parser::getStringIndexOfVar(varName));
				TNode *whileStmtLstNode = new TNode(TType::STMTLSTN, "");
				whileStmtLstNode->setStmtLine(whileNode->getStmtLine());
				Parser::linkTNodes(whileNode, varNode, whileStmtLstNode);

				// link whileNode to previous nodes on the AST
				linkTNodeToPrevNodes(whileNode, prevNode, expectedRelation);

				// prevNode now points to whileNode to parse the next statement
				prevNode = whileStmtLstNode;
				expectedRelation = TNodeRelation::CHILD;
			}
		} else if (programTokenList.at(i)->getTokenType() == TokenType::CLOSE_CURLY_BRACKET) { // end of a while loop
			// prevNode now points to its parent* which is a while node
			prevNode = prevNode->getParentNode()->getParentNode();
			expectedRelation = TNodeRelation::RIGHT_SIBLING;
			i++;
		}
	}
}

// build the AST for an expression, e.g. x + y + z
TNode* Parser::buildExprAST(vector<ParsingToken *> exprTokenList, STMTLINE stmtLine) {
	if (exprTokenList.size() == 0)
		throw InvalidExpressionException();

	stack<TNode*> operandStack;
	stack<OperatorType> operatorStack;

	for (int i=0; i<exprTokenList.size(); i++) {
		ParsingToken* currToken = exprTokenList.at(i);
		if (currToken->getTokenType() == TokenType::PLUS) // if token is + or - then put it to the operator stack
			operatorStack.push(OperatorType::PLUS_OP);
		else if (currToken->getTokenType() == TokenType::MINUS) {
			operatorStack.push(OperatorType::MINUS_OP);
		} else if (currToken->getTokenType() == TokenType::NAME || currToken->getTokenType() == TokenType::CONSTANT) {
			if (currToken->getTokenType() == TokenType::NAME) {
				PKB::getPKB()->getVarTable()->insertVar(currToken->getStringValue());
			}

			if (!operatorStack.empty()) { 
				OperatorType opType = operatorStack.top();
				operatorStack.pop();

				if (operandStack.empty())
					throw InvalidExpressionException();
				TNode* fNode = operandStack.top();
				operandStack.pop();

				if (opType == OperatorType::PLUS_OP) {
					TNode *plusNode = new TNode(TType::PLUSN, "");
					plusNode->setStmtLine(stmtLine);
					TNode *sNode;
					if (currToken->getTokenType() == TokenType::NAME)
						sNode = new TNode(TType::VARN, Parser::getStringIndexOfVar(currToken->getStringValue()));
					else 
						sNode = new TNode(TType::CONSTN, Parser::convertIntToString(currToken->getIntValue()));
					sNode->setStmtLine(stmtLine);
					Parser::linkTNodes(plusNode, fNode, sNode);
					operandStack.push(plusNode);
				} else if (opType == OperatorType::MINUS_OP) {
					TNode *minusNode = new TNode(TType::MINUSN, "");
					minusNode->setStmtLine(stmtLine);
					TNode *sNode;
					if (currToken->getTokenType() == TokenType::NAME)
						sNode = new TNode(TType::VARN, Parser::getStringIndexOfVar(currToken->getStringValue()));
					else 
						sNode = new TNode(TType::CONSTN, Parser::convertIntToString(currToken->getIntValue()));
					sNode->setStmtLine(stmtLine);
					Parser::linkTNodes(minusNode, fNode, sNode);
					operandStack.push(minusNode);
				}
			} else {
				TNode *aNode; 
				if (currToken->getTokenType() == TokenType::NAME)
					aNode = new TNode(TType::VARN, Parser::getStringIndexOfVar(currToken->getStringValue()));
				else 
					aNode = new TNode(TType::CONSTN, Parser::convertIntToString(currToken->getIntValue()));
				aNode->setStmtLine(stmtLine);
				operandStack.push(aNode);
			}

			// Add variable to varTable and Uses Table
			if (currToken->getTokenType() == TokenType::NAME) {
				PKB::getPKB()->getVarTable()->insertVar(currToken->getStringValue());
				Parser::addVarToUses(currToken->getStringValue(), stmtLine);
			}
		}
	}

	if (!operatorStack.empty()) // if there are more operators than necessary, then the expression is invalid
		throw InvalidExpressionException();

	if (operandStack.empty()) // after finishing parsing, there should be only one operand in the operand stack
		throw InvalidExpressionException();

	TNode *exprRootNode = operandStack.top();
	operandStack.pop();

	if (!operandStack.empty())
		throw InvalidExpressionException();

	return exprRootNode;
}

void Parser::addVarToUses(VARNAME varName, STMTLINE stmt)
{
	VARINDEX varIndex = PKB::getPKB()->getVarTable()->getVarIndex(varName);
	if (varIndex < 0) {
		PKB::getPKB()->getVarTable()->insertVar(varName);
	} else {
		PKB::getPKB()->getUses()->setUsesStmt(varIndex, stmt);
	}
}

void Parser::addVarToModifies(VARNAME varName, STMTLINE stmt)
{
	VARINDEX varIndex = PKB::getPKB()->getVarTable()->getVarIndex(varName);
	if (varIndex < 0) {
		PKB::getPKB()->getVarTable()->insertVar(varName);
	} else {
		PKB::getPKB()->getModifies()->setModifiesStmt(varIndex, stmt);
	}
}

string Parser::getStringIndexOfVar(VARNAME varName)
{
	VARINDEX varIndex = PKB::getPKB()->getVarTable()->getVarIndex(varName);
	
	return std::to_string(static_cast<long long>(varIndex));
}

string Parser::convertIntToString(int i) 
{
	return std::to_string(static_cast<long long>(i));
}

void Parser::linkTNodes(TNode *parentNode, TNode *leftNode, TNode *rightNode)
{
	parentNode->addChild(leftNode);
	parentNode->addChild(rightNode);
	leftNode->setParentNode(parentNode);
	rightNode->setParentNode(parentNode);
	leftNode->setRightSibling(rightNode);
	rightNode->setLeftSibling(leftNode);
}

void Parser::linkTNodeToPrevNodes(TNode *currNode, TNode *prevNode, TNodeRelation expectedRelation)
{
	if (expectedRelation == TNodeRelation::CHILD) {
		// link back to previous node and its parent
		prevNode->addChild(currNode);
		currNode->setParentNode(prevNode);

		// since the expected relation is CHILD, we know that the previous node is a stmtLst node
		// if the stmtLst is not the first stmtLst after precodure node, then we need to set parent and parent star for current statement
		if (prevNode->getStmtLine() > 0) {
			/*vector<STMTLINE> prevStmtParentStarList = PKB::getPKB()->getParent()->getParentStar(prevNode->getStmtLine());
			for (int i=0; i<prevStmtParentStarList.size(); i++) {
				PKB::getPKB()->getParent()->setParentStar(prevStmtParentStarList.at(i), currNode->getStmtLine());
			}*/

			// set Parent(prevStmt, currStmt)
			PKB::getPKB()->getParent()->setParent(prevNode->getStmtLine(), currNode->getStmtLine());
		}
	} else if (expectedRelation == TNodeRelation::RIGHT_SIBLING) {
		// link back to previous node and its parent
		prevNode->setRightSibling(currNode);
		currNode->setLeftSibling(prevNode);
		TNode *parentNode = prevNode->getParentNode();
		parentNode->addChild(currNode);
		currNode->setParentNode(parentNode);

		// set Parent and Parent star for current statement based on previous statement
		// we know that previous statement is an assignment or a while statement
		STMTLINE prevParentStmt = PKB::getPKB()->getParent()->getParent(prevNode->getStmtLine());
		if (prevParentStmt != -1) {
			PKB::getPKB()->getParent()->setParent(prevParentStmt, currNode->getStmtLine());
		}
		/*vector<STMTLINE> prevStmtParentStarList = PKB::getPKB()->getParent()->getParentStar(prevNode->getStmtLine());
		for (int i=0; i<prevStmtParentStarList.size(); i++) {
			PKB::getPKB()->getParent()->setParentStar(prevStmtParentStarList.at(i), currNode->getStmtLine());
		}*/

		// set Follows for current statement based on previous statement
		/*vector<STMTLINE> prevStmtFollowsStarList = PKB::getPKB()->getFollows()->getFollowedByStar(prevNode->getStmtLine());
		for (int i=0; i<prevStmtFollowsStarList.size(); i++) {
			PKB::getPKB()->getFollows()->setFollowsStar(prevStmtFollowsStarList.at(i), currNode->getStmtLine());
		}*/
		// set Follows(currStmt, prevStmt)
		PKB::getPKB()->getFollows()->setFollows(prevNode->getStmtLine(), currNode->getStmtLine());
	}
}

TNode* Parser::buildExprAST(string expression) {
	vector<ParsingToken*> exprToken;
	tokenizeLine(expression, &exprToken);
	return buildExprAST(exprToken, -1);
}