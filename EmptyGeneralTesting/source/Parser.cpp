#include "Parser.h"


vector<ParsingToken> Parser::programTokenList;
Grammar Parser::grammar;
int Parser::maxIndex = 0;

Parser::Parser(vector<ParsingToken> tokens){
	Parser::grammar = Grammar::Grammar();
	Parser::grammar.initiate();
	programTokenList = tokens;	
}

Parser::~Parser(){
}

// parse source code from file
void Parser::parse(string filename) {
	Parser::grammar = Grammar::Grammar();
	Parser::grammar.initiate();
	Tokenizer tokenizer = Tokenizer::Tokenizer(filename);
	programTokenList = tokenizer.start();
}

TNode* Parser::buildAst(){
	maxIndex = 0;
	TNode* root = Parser::buildNodeProcess(G_PROGRAM, 0).first;
	if(root->getTType() == EMPTYN){
		throw SyntaxErrorException(programTokenList.at(maxIndex).getLineNumber());
	}
	PKB::getPKB()->getAst()->setRoot(root);
	Parser::verifyProcedureRules(root);
	return root;
}

void Parser::verifyProcedureRules(TNode* node){
	vector<TNode*> procedureNodes;
	node->getAllChildrenIncludeSubByTType(procedureNodes, PROCEDUREN);

	for(int i = 0; i<procedureNodes.size(); i++){
		vector<TNode*> callsNodes;
		procedureNodes[i]->getAllChildrenIncludeSubByTType(callsNodes, CALLN);
		
		for(int k=0; k< callsNodes.size(); k++){
			//not found procedure name in call
			bool found = false;
			for(int g=0; g<procedureNodes.size(); g++){
				if(procedureNodes[g]->getValue() == callsNodes[k]->getValue()){
					found = true;
					break;
				}
			}
			if(!found){
				throw InvalidProcedureException(callsNodes[k]->getStmtLine());
			}

			
			//recursively procedure call error
			if(callsNodes[k]->getValue() == procedureNodes[i]->getValue()){
				throw RecursiveCallException(callsNodes[k]->getStmtLine());
			}
		}

		//duplicate procedure name
		for(int k = 0; k<procedureNodes.size(); k++){
			if(k!=i){
				if(procedureNodes[k]->getValue() == procedureNodes[i]->getValue()){
					throw InvalidNameException(procedureNodes[k]->getStmtLine());
				}
			}
		}

	}
}

pair<TNode*, int> Parser::buildNodeProcess(GrammarTType currentTokenType, int index){

	GrammarToken currentToken = Parser::grammar.getTokenByType(currentTokenType);
	vector<vector<GrammarToken>> expectedTokens = currentToken.getExpectedTokensList();

	TNode* parentTNode = new TNode();
	TType nodeType = EMPTYN;

	switch(currentToken.getType()){
		
		case G_PROGRAM:
			nodeType = PROGRAMN;
		break;
		case G_PROCEDURE:
			nodeType = PROCEDUREN;
		break;
		case G_STMTLST:
			nodeType = STMTLSTN;
		break;
		case G_STMT:
		case G_EXPR:
		case G_TERM:
		case G_FACTOR:
			nodeType = UNKNOWNN;
		break;
		case G_WHILE:
			nodeType = WHILEN;
			if(!(index >= programTokenList.size())){
				parentTNode->setStmtLine(programTokenList[index].getLineNumber());
			}
		break;
		case G_IF:
			nodeType = IFN;
			if(!(index >= programTokenList.size())){
				parentTNode->setStmtLine(programTokenList[index].getLineNumber());
			}
		break;
		case G_CALL:
			nodeType = CALLN;
			if(!(index >= programTokenList.size())){
				parentTNode->setStmtLine(programTokenList[index].getLineNumber());
			}
		break;
		case G_ASSIGN:
			nodeType = ASSIGNN;
			if(!(index >= programTokenList.size())){
				parentTNode->setStmtLine(programTokenList[index].getLineNumber());
			}
			
		break;
		case G_VAR_NAME:
			nodeType = VARN;
		break;
		case G_CONST_VALUE:
			nodeType = CONSTN;
		break;
		
	}

	parentTNode->setTType(nodeType);
	
	bool matchAtLeastOneRule = false;
	int originalIndex = index;
	TNode* originalParentTNode = parentTNode;

	if(!(index >= programTokenList.size())){
		
		for(int i = 0; i< expectedTokens.size(); i ++){

			bool breakOuter = false;
			if(!matchAtLeastOneRule){
				index = originalIndex;
				parentTNode = originalParentTNode;
			} 
			else{
				originalIndex = index;
				originalParentTNode = parentTNode;
			} 

			for(int q=0; q < expectedTokens[i].size(); q++){
			
				bool breakInner = false;
				bool hasSubRule = false;
				TNode* childTNode;
				GrammarToken expectedToken = expectedTokens[i][q];
				GrammarTType type = expectedToken.getType();

				switch(type){
			
					case G_PROCEDURE: 
					case G_STMTLST:
					case G_STMT:
					case G_CALL:
					case G_WHILE:
					case G_IF:
					case G_ASSIGN:
					case G_VAR_NAME:
					case G_CONST_VALUE:
					case G_EXPR:
					case G_TERM:
					case G_FACTOR:
					{
						pair<TNode*, int> result;
						if(type == G_EXPR || type == G_TERM){
							result = buildExprNodeProcess(index, -1);
						}
						else{
							result = buildNodeProcess(type, index);
						}

						childTNode = result.first;
						index = result.second;

					
						if(childTNode->getTType() == EMPTYN){
							if(!matchAtLeastOneRule){
								parentTNode->setTType(EMPTYN);
							}
							hasSubRule = false;
							breakInner = true;
						}
						else{
							hasSubRule = true;

							parentTNode->addChild(childTNode);
						
							if(expectedToken.isAllowMultiple()){
								matchAtLeastOneRule = true;
								q = -1;
								
							}
						}
					}
					break;

					case G_PROC_NAME:
					case G_NAME:
						if(ParserUtils::isValidName(programTokenList.at(index).getString())){
							parentTNode->setStmtLine(programTokenList.at(index).getLineNumber());
							parentTNode->setNodeValue(programTokenList.at(index).getString());
							index++;
							updateMaxIndex(index);
							hasSubRule = true;
						}
						else{
							breakInner = true;
							hasSubRule = false;
						}
					break;

					case G_INTEGER:
						if(ParserUtils::isNumeric(programTokenList.at(index).getString())){
							parentTNode->setStmtLine(programTokenList.at(index).getLineNumber());
							parentTNode->setNodeValue(programTokenList.at(index).getString());
							index++;
							updateMaxIndex(index);
							hasSubRule = true;
						}
						else{
							breakInner = true;
							hasSubRule = false;
						}
					break;

					case G_TEXT:
						if(index > programTokenList.size() -1) throw SyntaxErrorException(programTokenList.at(index-1).getLineNumber()); 
						
						if(programTokenList.at(index).getString() == expectedToken.getString()){
							index++;
							updateMaxIndex(index);
							hasSubRule = true;
						}
						else{
							breakInner = true;
							hasSubRule = false;
						}
					break;


				}

				if(q == expectedTokens[i].size()-1 && hasSubRule){
					matchAtLeastOneRule = true;
					breakOuter = true;
					updateMaxIndex(index);
				}

				if(breakInner) break;
		
			}
			if(breakOuter) break;
		}
	}

	if((parentTNode->getTType() == EMPTYN || parentTNode->getTType() == UNKNOWNN)){
		if(parentTNode->getChildren().size() == 1){
			parentTNode = parentTNode->getChildren().at(0);
		}
	}
	

	if(!matchAtLeastOneRule) parentTNode->setTType(EMPTYN);

	return make_pair<TNode*, int>(parentTNode, index);
	

}



pair<TNode*, int> Parser::buildExprNodeProcess(int index, int endIndex){

	if(endIndex == -1) endIndex = Parser::getNextSemiColonIndex(index);
	if(endIndex == -1) return make_pair<TNode*, int>(new TNode, endIndex);


	vector<ParsingToken> tokens;
	for(int i = index; i < endIndex; i++) tokens.push_back(programTokenList[i]);


	vector<TNode*> nodes = Parser::prioritizeExpr(tokens);
	TNode* exprNode = Parser::combinePriotizedNodes(nodes);

	return make_pair<TNode*, int>(exprNode, endIndex);
}

TNode* Parser::combinePriotizedNodes(vector<TNode*> &nodes){
	
	int maxIndex = -1;
	int maxPriority = -1;
	for(int i = 0; i<nodes.size(); i++){
		if(nodes[i]->getTType() == PLUSN || nodes[i]->getTType() == MINUSN || nodes[i]->getTType() == TIMESN){
			string p = nodes[i]->getValue();
			if(p!="" && atoi(p.c_str()) > maxPriority){
				maxIndex = i;
				maxPriority = atoi(p.c_str());
			}
		}
		
	}

	if(maxIndex != -1){
		TNode* leftNode = nodes[maxIndex-1];
		TNode* symbolNode = nodes[maxIndex];
		if(maxIndex+1 >= nodes.size()){
			throw SyntaxErrorException(programTokenList.at(Parser::maxIndex).getLineNumber());
		}
		TNode* rightNode = nodes[maxIndex+1];

		symbolNode->addChild(leftNode);
		symbolNode->addChild(rightNode);
		symbolNode->setNodeValue("-1");
		nodes.erase(nodes.begin() + maxIndex-1, nodes.begin() + maxIndex+2);
		nodes.insert(nodes.begin()+ (maxIndex-1), symbolNode);
		combinePriotizedNodes(nodes);
	}

	if(nodes.size() == 0){
		return new TNode();
	}
	else{
		return nodes[0];
	}
	

}

vector<TNode*> Parser::prioritizeExpr(vector<ParsingToken> &tokens){
	
	int base = 0;
	vector<TNode*> nodes;

	for(int i = 0; i<tokens.size(); i++){
		if(tokens[i].getString() == "(") base++;
		else if(tokens[i].getString() == ")") base--;
		else if(tokens[i].getString() == "*"){
			TNode* node = new TNode();
			node->setTType(TIMESN);
			node->setNodeValue(to_string((_ULonglong)(base+1)));
			nodes.push_back(node);
		}
		else if(tokens[i].getString() == "+" || tokens[i].getString() == "-"){
			TNode* node = new TNode();
			node->setTType(PLUSN);
			node->setNodeValue(to_string((_ULonglong)(base)));
			if(tokens[i].getString() == "-") node->setTType(MINUSN);
			nodes.push_back(node);
		} 
		else{
			TNode* node = new TNode();
			node = Parser::createVarOrConstNode(tokens[i]);
			nodes.push_back(node);
		}

	}

	if(base !=0) nodes.clear();
	return nodes;
}

int Parser::getNextSemiColonIndex(int index){
	string token;
	while(token != ";"){
		if(index > programTokenList.size()-1) return -1;
		token = programTokenList.at(index).getString();
		index++;
	}
	if(index>0) index--;
	return index;
}

TNode* Parser::createVarOrConstNode(ParsingToken token){

	string nameOrValue = token.getString();
	TNode* node = new TNode();
	if(ParserUtils::isValidName(nameOrValue)){
		node->setTType(VARN);
	}
	else if(ParserUtils::isNumeric(nameOrValue)){
		node->setTType(CONSTN);
	}
	else{
		throw SyntaxErrorException(programTokenList.at(maxIndex).getLineNumber());
	}

	node->setNodeValue(nameOrValue);
	node->setStmtLine(token.getLineNumber());
	return node;
}

TType Parser::convertSymbolToTType(string symbol){
	if(symbol == "+"){
		return PLUSN;
	}
	else if(symbol == "-"){
		return MINUSN;
	}
	else if(symbol == "*"){
		return TIMESN;
	}
}

void Parser::updateMaxIndex(int newIndex){
	maxIndex = newIndex;
}


