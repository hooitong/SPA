#include "QueryTree.h"
#include "QueryPreprocessor.h"
#include <string>
#include <iostream>
#include "Exception.h"
#include <vector>
using namespace std;

	
	static string designEntity[] = {"procedure","stmtLst", "stmt", "assign", "call", "while", "if", "variable", "constant", "prog_line"};
	static const int num = 10;
	static QueryTree* tree;

	/**************************General *********************************/

	QueryPreprocessor::QueryPreprocessor(void) {
	}

	QueryPreprocessor::~QueryPreprocessor(void) {
	}

	QueryTree* QueryPreprocessor::parseQuery(string query){
		try {
			queryTree = new QueryTree();
			QNode* root = queryTree->createNode(QUERY, "");
			queryTree->setAsRoot(root);
			resultListNode = queryTree->createNode(RESULTLIST, "");
			suchthatListNode = queryTree->createNode(SUCHTHATLIST, "");
			patternListNode = queryTree->createNode(PATTERNLIST, "");
			queryTree->addChild(root, resultListNode);
			queryTree->addChild(root, suchthatListNode);
			queryTree->addChild(root, patternListNode);
	//		cout << "Created Root node and children "<< endl;

			int p = query.find("Select");
		
			if(p == string::npos){
				throw InvalidSelectException(); 
			}
		
			string result_cl;
			string declaration = query.substr(0,p);
			//cout << "Checking if  conditions / clauses exists and collecting pointers"<< endl;
			if(!checkConditionExists(query)){
				//cout << " conditions / clauses don't exists "<< endl;
				//cout << " checking if Declaration is correct"<< endl;
				if(checkDeclaration(declaration)){
				  //   cout << " Declaration is correct "<< endl;
					 result_cl = query.substr(p+6, query.length()-p-6);
					// cout << " Going to check result "<< endl;
					 checkTuple(result_cl);
				}else{
					 throw InvalidQueryDeclarationException() ;
				}
				return queryTree;
			}

			map<int,int>::iterator it = posOfConds.begin();
			//pointer  to first condition/clause
			int ptf = it -> first;
			int type = it -> second;

			result_cl = query.substr(p+6, ptf-p-6);
		
			if(!(checkDeclaration(declaration) && checkTuple(result_cl))){
				throw InvalidQueryDeclarationException();
			}
			it++;
			//pointer to second condition/clause
			int pts;
			if(it != posOfConds.end()) pts = it-> first;

			while( it != posOfConds.end()){
				//cout << " Looping through conditions "<< endl;
				string clause = query.substr(ptf, pts - ptf);
				if(trimAndCheckClause(clause, type)){
					ptf = pts;
					type = it->second;
				}else{
					throw InvalidClauseSyntaxException();
				}
				it++;
				if(it != posOfConds.end()) pts = it->first;
			}
		
			string clause = query.substr(ptf, query.length() - ptf);
			if(!trimAndCheckClause(clause, type)) {
				throw InvalidClauseSyntaxException();
			}
			return queryTree;
		} catch (exception e) {
			return NULL;
		}
	}

	bool QueryPreprocessor::checkConditionExists(string query){
		string query1;
		query1 = query;
		for(int i = 0; i < query1.length(); i++){
			query1[i] = tolower(query1[i]);
		}
		//pointer of such that condition
		int pst = query.find("such that");
		int pst1 = query1.find("such that");
		//pointer of pattern condition
		int pp = query.find("pattern");
		int pp1 = query1.find("pattern");
		//pointer of with condition
		int pw = query.find("with");
		int pw1 = query.find("with");
	
		if(pst == string::npos && pp == string::npos && pw == string::npos) {
			return false;
		}

		while(pst != string::npos){
			posOfConds.insert(pair<int,int>(pst, 9));
			pst = query.find("such that",pst + 1);
		}
		while(pst1 != string::npos){
			posOfConds1.insert(pair<int,int>(pst1, 9));
			pst1 = query1.find("such that",pst1 + 1);
		}

		while(pp != string::npos){
			posOfConds.insert(pair<int,int>(pp, 7));
			pp = query.find("pattern", pp + 1);
		}

		while(pp1 != string::npos){
			posOfConds1.insert(pair<int,int>(pp1, 7));
			pp1 = query1.find("pattern", pp1 + 1);
		}

		while(pw != string::npos){
			posOfConds.insert(pair<int,int>(pw, 4));
			pw = query.find("with", pw + 1);
		}

		while(pw1 != string::npos){
			posOfConds1.insert(pair<int,int>(pw1, 4));
			pw1 = query1.find("with", pw1 + 1);
		}
		//cout << posOfConds.size() <<endl;
		//cout << posOfConds1.size() <<endl;
		if(posOfConds.size() != posOfConds1.size()){
			throw InvalidCaseClauseException();
		}

		return true;
	}
	bool QueryPreprocessor::trimAndCheckClause(string clause, int num){
		clause = trim(clause);
		clause = clause.substr(num,clause.size()-num);

		return splitAndCheckClause(clause, num);

	}
	bool QueryPreprocessor::splitAndCheckClause(string clause, int num){
		clause = trim(clause);
		int p = clause.find(" and ");
		// there doesn't exist "and"
		
		if(p != string::npos){
			string s1 = trim(clause.substr(0,p));
			string s2 = trim(clause.substr(p+5,clause.size()-p-5));

			bool valid = true;
			switch(num){
				case 4:
					return false;
					//return checkAttribute(s1);
					break;
				case 7:
					valid = valid && checkPattern(s1);
					break;
				case 9:
					valid = valid && checkRelation(s1);
					break;
				default:
					return false;
					break;
				}
			return valid && splitAndCheckClause(s2, num);
	
		}else{

			switch(num){
				case 4:
					return false;
					//return checkAttribute(clause);
					break;
				case 7:
					return checkPattern(clause);
					break;
				case 9:
					return checkRelation(clause);
					break;
				default:
					return false;
					break;
			}

		}	

	}
/**************************Tools *********************************/
	bool QueryPreprocessor::checkIdent(string ident){
		if(ident.length() == 0)
			return false;

		if(isalpha(ident.at(0))){
			for(size_t i = 1; i < ident.length(); i++){
				if(!isalnum(ident.at(i)) && !(ident.at(i) == '#')){
					 return false;
				}
			}
			return true;
		}

		return false;
	}
	bool QueryPreprocessor::checkInteger(string number){

		if(number.length() == 0)
			return false;
		for(size_t i = 0; i < number.length(); i++){
			if(!isdigit(number.at(i))){
				return false;
			}
		}
		return true;
	}
	bool QueryPreprocessor::checkAttReference(string attReference){

		int p = attReference.find(".");
		if(p == string::npos) return false;
		string s =  attReference.substr(0,p);
		string attribute = attReference.substr(p+1,attReference.length() - p - 1);
		return (checkIdent(s)&&checkAttributeName(attribute));

	}
	bool QueryPreprocessor::checkVarReference(string varReference){
		//cout << "checking VarReference"<<endl;
		if(varReference.at(0) == '\"' && varReference.at(varReference.length() -1) == '\"'){
			 varReference = varReference.substr(1,varReference.length() - 2);	
			 //cout << "have quotations "<<endl;
		} else {
			//cout << "no quotations "<<endl;
			return false;
		}
		//cout << "checking Ident for varReference "<<endl;
		return (checkIdent(varReference));
	}
	bool QueryPreprocessor::checkDesignEntity(string entity){
		for(int i = 0; i < 10; i++){
			if(entity  == designEntity[i])
				return true;

		}
		return false;
	}
	bool QueryPreprocessor::checkFactor(string factor){
		factor = trim(factor);
		if(factor  == "") return false;

		return checkInteger(factor) || checkIdent(factor);
	}

/**************************Use Declaration *********************************/
	bool QueryPreprocessor::existsRef(string reference){
		for(size_t i = 0; i<refDeclared.size();i++){
			if(reference == refDeclared.at(i).synonym){
				return true;
			}
		}

		return false;
	}
	string QueryPreprocessor::getType(string synonym){
		for(size_t i = 0; i<refDeclared.size();i++){
			if(synonym == refDeclared.at(i).synonym){
				return refDeclared.at(i).type;
			}
		}
		return "";
	}

/**************************With  *********************************/
	bool QueryPreprocessor::checkAttributeName(string attName){
		if((attName == "procName") || (attName == "varName") || (attName == "value") || (attName == "stmt#")){
			return true;
		}else{
			return false;
		}
	}
	bool QueryPreprocessor::checkAttribute(string attribute){
		return true;
	}

/**************************Relation *********************************/
	QNode* QueryPreprocessor::parseStmtRef(string argument) {
		if (argument == "_") {
			return queryTree->createNode(ANY,"");
		} else if (isdigit(argument.at(0))) {
			return queryTree->createNode(CONST,argument);
		} else if (existsRef(argument)) {
			if (getType(argument) == "stmt") {
				return queryTree->createNode(STMTSYNONYM,argument);
			} else if (getType(argument) == "while") {
				return queryTree->createNode(WHILESYNONYM,argument);
			} else if (getType(argument) == "assign") {
				return queryTree->createNode(ASSIGNSYNONYM,argument);
			} else if (getType(argument) == "prog_line") {
				return queryTree->createNode(PROGLINESYNONYM,argument);
			} else {
				throw UnmatchedSynonymException();
			}
		} else {
			throw UndeclaredException(); 
		}
		return NULL;
	}

	QNode* QueryPreprocessor::parseEntRef(string argument) {
		QNode* right;
		//cout << "******************parsingEntRef*******************************" <<endl;
		if (argument == "_") {
			return queryTree->createNode(ANY,"");
		} else if (argument.at(0) == '\"' && argument.at((int)argument.size()-1) == '\"') {
			right = queryTree->createNode(VAR,trim(argument.substr(1,(int)argument.size()-2)));
			return right;
		} else if (existsRef(argument) && getType(argument) == "variable") {
			return queryTree->createNode(VARIABLESYNONYM,argument);
		}
		return NULL;
	}

	bool QueryPreprocessor::checkRelation(string relation){
		int p1 = relation.find("(");
		string relationType = trim(relation.substr(0,p1));
		int p2 = relation.find(",");
		string argument1 = trim(relation.substr(p1+1,p2-p1-1));
		int p3 = relation.find(")");
		string argument2 = trim(relation.substr(p2+1,p3-p2-1));

		int index  = findIndexOfTable(relationType);

		QNode* relationNode = queryTree->createNode(RELATION,relationType);
		QNode* leftHandSide;
		QNode* rightHandSide;

		leftHandSide = parseStmtRef(argument1);

		if (index == 0) { //Modifies or Uses for now
			rightHandSide = parseEntRef(argument2);
		} else if (index == 2 || index == 3) { //Parent and Follow for now
			rightHandSide = parseStmtRef(argument2);
		} else {
			//TODO. Not covered in CS3201
			return false;
		}

		queryTree->addChild(relationNode,leftHandSide);
		queryTree->addChild(relationNode,rightHandSide);
		queryTree->addChild(suchthatListNode,relationNode);

		return true;
	}
	int QueryPreprocessor::findIndexOfType(string type){
		for(int i = 0; i < num; i++){
			if(designEntity[i] == type){
				return i;
			}
		}

		return -1;
	}
	int QueryPreprocessor::findIndexOfTable(string relationType){
		if((relationType == "Modifies") || (relationType == "Uses")){
			return 0;
		}else if(relationType == "Calls" || relationType == "Calls*"){
			return 1;
		}else if(relationType == "Parent" || relationType == "Parent*"){
			return 2;
		}else if(relationType == "Follows" || relationType == "Follows*" || relationType == "Next" || relationType == "Next*" ){
			return 3;
		}else if(relationType == "Affects" || relationType == "Affects*"){
			return 4;
		}
		return 5;

	}

/**************************Pattern *********************************/
	bool QueryPreprocessor::checkWhile(string pattern){
		return true;
	}
	bool QueryPreprocessor::checkIf(string pattern){
		//add pattern node
		return true;
	}
	bool QueryPreprocessor::checkAssign(string pattern, string patternName){	
		//cout << "******************************check Assign pattern ************************************************" << endl;
		pattern = trim(pattern);
		//pointer of open bracket
		int pob = pattern.find("(");
		if(pob == string::npos) return false;
		string synonym = trim(pattern.substr(0,pob));
		if(checkIdent(synonym)){
			//pointer of comma
			int pc = pattern.find(",");
			if(pc == string::npos) return false;
			string varRef = trim(pattern.substr(pob + 1, pc - pob - 1));
			string varRefType;
			QNode* patternNode = queryTree->createNode(PATTERN,"");
			QNode* assignSynonymNode = queryTree->createNode(ASSIGNSYNONYM,synonym);
			QNode* leftHandSide;
			QNode* rightHandSide;
			//cout << "Checking VARREF" << endl;
			//cout << "VARREF1 :" << varRef <<endl;
			if(checkVarReference(varRef)){
			//	cout << "VARREF2 :" << varRef <<endl;
				leftHandSide = queryTree->createNode(VAR,varRef.substr(1,(int)varRef.size()-2));
			} else if (varRef == "_") {
				leftHandSide = queryTree->createNode(ANY,"");
			} else if (checkIdent(varRef) && existsRef(varRef) && getType(varRef) == "variable") {
				leftHandSide = queryTree->createNode(VARIABLESYNONYM,varRef);
			} else {
				return false;
			}
			int pcb = pattern.find_last_of(")");
			if(pcb == string::npos || pcb != pattern.length() - 1) return false;
			string expr = trim(pattern.substr(pc + 1, pcb - pc - 1));
			string exprRemoveQuote = "";
			for (int i = 0; i < (int)expr.size(); ++i) {
				if (expr.at(i) != '\"') {
					exprRemoveQuote += expr.at(i);
				}
			}
			rightHandSide = queryTree->createNode(EXPRESSION,exprRemoveQuote);
			//cout << "*****************************end Assign pattern ****************************" << endl;
			queryTree->addChild(patternNode,assignSynonymNode);
			queryTree->addChild(patternNode,leftHandSide);
			queryTree->addChild(patternNode,rightHandSide);
			queryTree->addChild(patternListNode,patternNode);
			return true;
		}
		return false;
	}

	bool QueryPreprocessor::checkPattern(string pattern){
		int p = pattern.find("(");
		string patternName = trim(pattern.substr(0,p));
		string type = getType(patternName);
		if(type == "while"){
			return false;
			//return checkWhile(pattern);
		}else if(type == "if"){
			return false;
			//return checkIf(pattern);
		}else if(type == "assign"){
			return checkAssign(pattern, patternName);
		}
		return false;
	}

/**************************declaration  *********************************/
	bool QueryPreprocessor::checkDeclaration(string declaration){
		//psc = pointer of semicolon
		//cout << "*************************checkDeclaration******************************"  << endl;
		declaration = trim(declaration);
		if(declaration == "") return true;
		int psc = declaration.find(";");
		//cout << "Getting the first declaration"  << endl;
		string declar_clause = trim(declaration.substr(0, psc));
		while(psc != string::npos){
			//cout << "Looping through the declarations"  << endl;
			declar_clause = trim(declar_clause);
			//ps = pointer of space
			int ps = declar_clause.find(" ");
			string type = declar_clause.substr(0,ps);
			if(checkDesignEntity(type)){
				 size_t pc = ps;
				do{
				//	cout << "Looping through each variable of the declaration clause"  << endl;
					//pc = pointer of comma
					int pnc = declar_clause.find(",", pc + 1);
					if (pnc == string::npos) {
						pnc = declar_clause.length();
					}
					string synonym = trim(declar_clause.substr(pc + 1, pnc - pc - 1));
					if(checkIdent(synonym) && (!existsRef(synonym))){
						entity e = {type, synonym};
						refDeclared.push_back(e);
					}else{
						return false;
					}
					pc = pnc;
				} while (pc < declar_clause.size());

			} else {
				return false;
			}
			//pnsc = pointer of next semicolon
			size_t pnsc = declaration.find(";", psc+1);
			if(pnsc == string::npos) {
				break;
			}
			if(pnsc < declaration.length()){
				declar_clause = declaration.substr(psc + 1, pnsc - psc -1);
			}
			psc = pnsc;

		}
		//cout << "*************************checkDeclaration  end ******************************"  << endl;
		return true;


	}

/**************************result  *********************************/

	bool QueryPreprocessor::addTuple(string single_tuple) {
		single_tuple = trim(single_tuple);
		if (!existsRef(single_tuple)) {
			throw UndeclaredException();
		}
		string type = getType(single_tuple);
		QNode* resultNode;
		if (type == "assign") {
			resultNode = queryTree->createNode(ASSIGNSYNONYM, single_tuple);
		} else if (type == "stmt") {
			resultNode = queryTree->createNode(STMTSYNONYM, single_tuple);
		} else if (type == "while") {
			resultNode = queryTree->createNode(WHILESYNONYM, single_tuple);
		} else if (type == "variable") {
			resultNode = queryTree->createNode(VARIABLESYNONYM, single_tuple);
		} else if (type == "constant") {
			resultNode = queryTree->createNode(CONSTSYNONYM, single_tuple);
		} else if (type == "prog_line") {
			resultNode = queryTree->createNode(PROGLINESYNONYM, single_tuple);
		} else if (type == "procedure") {
			resultNode = queryTree->createNode(PROCEDURESYNONYM, single_tuple);
		} else if (type == "if") {
			resultNode = queryTree->createNode(IFSYNONYM, single_tuple);
		}else{
			throw UnmatchedSynonymException();
		}
		queryTree->addChild(resultListNode, resultNode);
		return true;
	}

	bool QueryPreprocessor::checkTuple(string tuple){
		tuple = trim(tuple);
		//cout << " checking if tuple is elem"<< endl;
		if(checkElem(tuple)){
			//cout << " tuple is elem"<< endl;

			//cout << " checking if tuple is exists in declaration"<< endl;
			if(existsRef(tuple)){
				return addTuple(tuple);
			}else{
				throw InvalidResultSyntaxException();
			}
		} else if (tuple.at(0) == '<') {
			tuple = tuple.substr(1,(int)tuple.size() - 2);
			int pt = 0;
			while (pt < (int)tuple.size()) {
				int nextpt = tuple.find(',',pt);
				if (nextpt == string::npos) {
					nextpt = (int)tuple.size();
				}	
				string single_tuple = tuple.substr(pt,nextpt-pt);
				if (!addTuple(single_tuple)) {
					return false;
				}
				pt = nextpt + 1;
			}
			return true;
		} else {
			throw InvalidResultSyntaxException();
		}
		return false;
	}	
	bool QueryPreprocessor::checkElem(string elem){
		//return true;
		return (checkIdent(elem) || checkAttReference(elem));
	}
/************************** Others *********************************/

	string QueryPreprocessor::trim(string s){
		//cout << " Before trim :" << s << endl;
		int firstNotSpace = 0;
		while (firstNotSpace < (int)s.length() && (s.at(firstNotSpace) == ' ' || s.at(firstNotSpace) == ' \t' ) ) {
			++firstNotSpace;
		}
		if (firstNotSpace == (int)s.length()) {
			return "";
		}
		int lastNotSpace = (int)s.length() - 1;
		while (lastNotSpace >= 0 && (s.at(lastNotSpace) == ' ' || s.at(lastNotSpace) == '\t')) {
			--lastNotSpace;
		}
		s = s.substr(firstNotSpace,lastNotSpace - firstNotSpace + 1);
		//cout << " After trim :" << s << endl;
		return s;
	}



