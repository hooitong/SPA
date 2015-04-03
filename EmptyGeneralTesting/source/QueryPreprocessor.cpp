#include "QueryTree.h"
#include "QueryPreprocessor.h"
#include <string>
#include <iostream>
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
		//add root node
		
		//QNode* node = tree.createNode(QUERY, "query");
		//tree.setAsRoot(node);
		//QNode* resultNode = tree.createNode(RESULTLIST, "result");
		//QNode* suchthatNode = tree.createNode(SUCHTHATLIST, "such that");
		//QNode* patternListNode = tree.createNode(PATTERNLIST, "pattern");
		//getRoot
		//tree.addchild(Root, resultNode);
		//tree.addchild(Root, suchthatNode);
		//tree.addchild(Root, patternListNode);


		cout << "Created Root node and children "<< endl;

		int p = query.find("Select");
		if(p == -1){
			cout << "error";
		}
		string result_cl;
		string declaration = query.substr(0,p);
		cout << "Checking if  conditions / clauses exists and collecting pointers"<< endl;
		if(!checkConditionExists(query)){
			cout << " conditions / clauses don't exists "<< endl;
			cout << " checking if Declaration is correct"<< endl;
			if(checkDeclaration(declaration)){
			     cout << " Declaration is correct "<< endl;
				 result_cl = query.substr(p+6, query.length()-p-6);
				 cout << " Going to check result "<< endl;
				 checkTuple(result_cl);
			}else{
				 cout << "error";				
			}
		}

		
		map<int,int>::iterator it = posOfConds.begin();
		//pointer  to first condition/clause
		int ptf = it -> first;
		int type = it -> second;

		result_cl = query.substr(p+6, ptf-p-6);
		
		if(!(checkDeclaration(declaration) && checkTuple(result_cl))){
			cout << "error";
		}
		it++;
		//pointer to second condition/clause
		int pts;
		if(it != posOfConds.end()) pts = it-> first;


		while( it != posOfConds.end()){

			  cout << " Looping through conditions "<< endl;
			string clause = query.substr(ptf, pts - ptf);
			if(trimAndCheckClause(clause, type)){
				ptf = pts;
				type = it->second;
			}else{
				cout << "error";
			}
			it++;
			if(it != posOfConds.end()) pts = it->first;
		}
		
		string clause = query.substr(ptf, query.length() - ptf);
		if(!trimAndCheckClause(clause, type)) cout << "error";


		
		return NULL;
	}
	bool QueryPreprocessor::checkConditionExists(string query){
		//pointer of such that condition
		int pst = query.find("such that");
		//pointer of pattern condition
		int pp = query.find("pattern");
		//pointer of with condition
		int pw = query.find("with");
		int l = query.length();
		if(pst > l && pp > l && pw> l) return false;

		while(pst < l){
			posOfConds.insert(pair<int,int>(pst, 9));
			pst = query.find("such that",pst + 1);
		}

		while(pp < l){
			posOfConds.insert(pair<int,int>(pp, 7));
			pp = query.find("pattern", pp + 1);
		}

		while(pw < l){
			posOfConds.insert(pair<int,int>(pw, 4));
			pw = query.find("with", pw + 1);
		}

		return true;
	}
	bool QueryPreprocessor::trimAndCheckClause(string clause, int num){
		clause = trim(clause);
		clause = clause.substr(num,clause.size()-num);

		return splitAndCheckClause(clause, num);

	}
	bool QueryPreprocessor::splitAndCheckClause(string clause, int num){
		int p = clause.find(" and ");
		// there doesn't exist "and"
		
		if(p < clause.length()){
			string s1 = trim(clause.substr(0,p));
			string s2 = trim(clause.substr(p+5,clause.size()-p-5));

			switch(num){
				case 4:
					return false;
					//return checkAttribute(s1);
					break;
				case 7:
					return checkPattern(s1);
					break;
				case 9:
					checkRelation(s1);
					break;
				default:
					return false;
					break;
				}
			return splitAndCheckClause(s2, num);
	
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
			for(int i = 1; i < ident.length(); i++){
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
		for(int i = 0; i < number.length(); i++){
			if(!isdigit(number.at(i))){
				return false;
			}
		}
		return true;
	}
	bool QueryPreprocessor::checkAttReference(string attReference){

		int p = attReference.find(".");
		if(p == -1) return false;
		string s =  attReference.substr(0,p);
		string attribute = attReference.substr(p+1,attReference.length() - p - 1);
		return (checkIdent(s)&&checkAttributeName(attribute));

	}
	bool QueryPreprocessor::checkVarReference(string varReference){

		if(varReference.at(0) == '\"' && varReference.at(varReference.length()) == '\"'){
			 varReference = varReference.substr(1,varReference.length() - 2);			
		}
		return (checkIdent(varReference) || varReference == "_" );
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
		for(int i = 0; i<refDeclared.size();i++){
			if(reference == refDeclared.at(i).synonym){
				return true;
			}
		}

		return false;
	}
	string QueryPreprocessor::getType(string synonym){
		for(int i = 0; i<refDeclared.size();i++){
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
	bool QueryPreprocessor::checkRelation(string relation){
		int p1 = relation.find("(");
		string relationType = trim(relation.substr(0,p1));
		int p2 = relation.find(",");
		string argument1 = trim(relation.substr(p1+1,p2-p1-1));
		int p3 = relation.find(")");
		string argument2 = trim(relation.substr(p2+1,p3-p2-1));

		int index  = findIndexOfTable(relationType);
		bool arg1_flag = false;
		bool arg2_flag = false;

		string type1 = getType(argument1);
		if(table[index][findIndexOfType(type1)]){
			if(checkIdent(argument1) || argument1 == "_"){
				arg1_flag = true;
			}else if((table[index][10] == 1) && (argument1[0] == '"') && (argument1[argument1.length()-1] == '"' )){
				argument1 = trim(argument1.substr(1,argument1.length() -2));
				
			}else if(table[index][11] == 1 && checkInteger(argument1)){
				arg1_flag = true;
			}
		}
		
		string type2 = getType(argument2);
		if(table[index][findIndexOfType(type2)+12]){
			if(checkIdent(argument2) || argument2 == "_"){
				arg2_flag = true;
			}else if(table[index][22] == 1 && argument2[0] == '"' && argument1[argument2.length()-1] == '"' ){
				argument2 = trim(argument2.substr(1,argument1.length() -2));
				if(checkIdent(argument2)){
					arg2_flag = true;
				}
		
			}else if(table[index][23] == 1 && checkInteger(argument2)){
				arg2_flag = true;
			}
		}

		if(arg1_flag == true && arg2_flag == true){
				cout <<"creating relation node : " <<relationType << endl; 
				cout <<"argument1 : " << argument1  << ":" << type1 << endl; 
				cout <<"argument2 : " << argument2  << ":" << type2 << endl; 
				
				// find root and get SUCHTHATLIST node
				// Qnode* relationNode = tree.createNode(RELATION, relationType);
				// type1 and type2 have to be converted to enum
				// Qnode* argumentNode1 = tree.createNode(type1, argument1);
				// Qnode* argumentNode2 = tree.createNode(type2, argument2 );
				// tree.addChild(relationNode, argumentNode1);
				// tree.addChild(relationNode, argumentNode2);
			return true;
		}
		return false;


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
		cout << "******************************check Assign pattern ************************************************" << endl;
		pattern = trim(pattern);
		//pointer of open bracket
		int pob = pattern.find("(");
		if(pob > pattern.length()) return false;
		string synonym = trim(pattern.substr(0,pob));
		if(checkIdent(synonym)){
			//pointer of comma
			int pc = pattern.find(",");
			if(pc > pattern.length()) return false;
			string varRef = trim(pattern.substr(pob + 1, pc - pob - 1));
			string varRefType;
			if(checkVarReference(varRef)){
				//countinue to check expression-spec
				//pointer to close bracket
				int pcb = pattern.find_last_of(")");
				if(pcb > pattern.length() || pcb != pattern.length() - 1) return false;
				string expr = trim(pattern.substr(pob + 1, pcb - pob - 1));
				if(expr == "_"){
					cout <<"pattern 1" << endl; 
					

				}else if(expr.at(0) == '_' && expr.at(expr.length()-1) == '_' && expr.at(1) == '\"' && expr.at(expr.length()-2) == '\"') {
					expr = trim(expr.substr(2 , expr.length() - 4));
					//pointer of plus
					int pp = expr.find("+");
					if(pp > expr.length()){
						if(!checkFactor(expr)) return false;
						cout <<" pattern 2" << endl;
					}else{

						string expr1 = trim(expr.substr(0,pp));
						string expr2 = trim(expr.substr(pp + 1,expr.length() - pp -1 ));
						if(!(checkFactor(expr1) && checkFactor(expr2))) return false;
							cout <<"pattern 3" << endl; 						

					}
				}else{
					return false;
				}
				cout <<"creating pattern node : " <<patternName << endl; 
				cout <<" ( " << synonym << "," << expr << ")"<< endl; 
				// find root and get PATTERNLIST node
				// Qnode* patternNode = tree createNode(PATTERN, patternName);
				// Qnode* varNode = tree createNode(VAR, synonym);
				// Qnode* exprNode = tree createNode(EXPRESSION, expr);
				// tree.addChild(patternListNode, patternNode);
				// tree.addChild(patternNode, varNode);
				// tree.addChild(patternNode, exprNode);

				cout << "*****************************end Assign pattern ****************************" << endl;
				return true;
			}
		}
		return false;
	}
	/*
	bool QueryPreprocessor::checkExpression(string expression){

		expression = trim(expression);
		if((expression.at(0) == '_') && (expression.at(expression.length() - 1) == '_')){
			expression = expression.substr(1,expression.length() -2);
			

		}else if((expression.at(0) == '"') && (expression.at(expression.length() - 1) == '"')){
		}else{
			return false;
		}
	}*/
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
		cout << "*************************checkDeclaration******************************"  << endl;
		declaration = trim(declaration);
		if(declaration == "") return true;
		int psc = declaration.find(";");
		cout << "Getting the first declaration"  << endl;
		string declar_clause =  trim(declaration.substr(0, psc));
		while(psc < declaration.length()){
			cout << "Looping through the declarations"  << endl;
			declar_clause = trim(declar_clause);
			//ps = pointer of space
			int ps = declar_clause.find(" ");
			string type = declar_clause.substr(0,ps);
			if(checkDesignEntity(type)){
				int pc = ps;
				do{
					cout << "Looping through each variable of the declaration clause"  << endl;
				//pc = pointer of comma
					int pnc = declar_clause.find(",", pc + 1);
					if(pnc - pc <= 1) return false;
					string synonym;
					if(pnc>declaration.size()){
						synonym = trim(declar_clause.substr(pc + 1, declar_clause.length() - pc - 1));
					}else{
						synonym = trim(declar_clause.substr(pc + 1, pnc - pc - 1));
					}
					if(checkIdent(synonym) && (!existsRef(synonym))){
						entity e  = {type, synonym};
						refDeclared.push_back(e);
					}else{
						return false;
					}

				int pc = pnc;
				}while(pc < refDeclared.size());

			}else{
				return false;
			}
			//pnsc = pointer of next semicolon
			int pnsc = declaration.find(";", psc+1);
			if(pnsc - psc <= 1) return false;
			if(pnsc < declaration.length()){
				declar_clause = declaration.substr(psc + 1, pnsc - psc -1);
			}
			psc = pnsc;

		}
		cout << "*************************checkDeclaration  end ******************************"  << endl;
		return true;


	}

/**************************result  *********************************/

	bool QueryPreprocessor::checkTuple(string tuple){


		tuple = trim(tuple);
		cout << " checking if tuple is elem"<< endl;
		if(checkElem(tuple)){
			cout << " tuple is elem"<< endl;

			cout << " checking if tuple is exists in declaration"<< endl;
			if(existsRef(tuple)){
				cout << " creating result node"<< endl;
				
				string type = getType(tuple); 
				//get root and find RESULTLIST node
				//conver type to enum
				//Qnode* resultNode = tree.createNode(type, tuple);
				//tree.addChild(resultListNode, node);

				cout << tuple << ":" << type << endl;
			
				return true;
			}

		}else{
			cout << "error";
		}
		return false;
	}	
	bool QueryPreprocessor::checkElem(string elem){
		return (checkIdent(elem) || checkAttReference(elem));
	}
/************************** Others *********************************/
	void QueryPreprocessor::buildTable(){

	int table[10][24] =
	{
        {1,0,1,1,1,1,1,0,0,1,1,1,0,0,0,0,0,0,0,1,0,0,1,0},
        {0,0,0,0,1,0,0,0,0,0,1,1,0,0,0,0,1,0,0,0,0,0,1,1},
		{0,0,1,0,0,1,1,0,0,1,0,1,0,0,1,1,1,1,1,0,0,1,0,1},
		{0,0,1,1,1,1,1,0,0,1,0,1,0,0,1,1,1,1,1,0,0,1,0,1},
		{0,0,1,1,0,0,0,0,0,1,0,1,0,0,1,1,0,0,0,0,0,1,0,1}
    };

	}
	string QueryPreprocessor::trim(string s){
		  cout << " Before trim :" << s << endl;
		int p = s.find_first_not_of(" ");
		if(p > s.length()){
			s.erase(s.begin(), s.end() -p);
		}else{
			return "";
		}
		 p = s.find_last_not_of(" ");
		s.erase(s.begin() + p + 1 ,s.end());
		cout << " After trim :" << s << endl;
		return s;
	}



