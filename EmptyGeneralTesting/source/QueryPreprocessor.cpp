#include "QueryTree.h"
#include "QueryPreprocessor.h"
#include <string>
#include <iostream>
using namespace std;

	static string designEntity[] = {"procedure","stmtLst", "stmt", "assign", "call", "while", "if", "variable", "constant", "prog_line"};
	QueryTree* QueryPreprocessor::parseQuery(string query){

    return NULL;
	}

	bool QueryPreprocessor::checkAttributeName(string attName){
		if((attName == "procName") || (attName == "varName") || (attName == "value") || (attName == "stmt#")){
			return true;
		}else{
			return false;
		}
	}

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

	bool QueryPreprocessor::checkElem(string elem){
		return (checkIdent(elem) || checkAttReference(elem));
	}

	bool QueryPreprocessor::checkVarReference(string varReference){

		if(varReference.at(0) == '\"' && varReference.at(varReference.length()) == '\"'){
			string s = varReference.substr(1,s.length() - 2);
			return (checkIdent(s) || s == "_" );
		}else{
			return false;
		}
	}

	bool QueryPreprocessor::checkDesignEntity(string entity){
		for(int i = 0; i < 10; i++){
			if(entity  == designEntity[i])
				return true;

		}
		return false;
	}

	bool QueryPreprocessor::checkTuple(string tuple){

		tuple = trim(tuple);

		if(checkElem(tuple)){

			if(existsRef(tuple)){



				return true;
			}
			if(checkAttReference(tuple)){

				int p = tuple.find(".");
				string s = tuple.substr(0,p);
				if(existsRef(s)){




				}

			}

		}else{
			if((tuple.at(0) == '<') && (tuple.at(tuple.length() - 1) == '>')){



			}


		}

	}
	
	string QueryPreprocessor::trim(string s){
		
		int p = s.find_first_not_of(" ");
		if(p > s.length()){
			s.erase(s.begin(), s.end() -p);
		}else{
			return "";
		}
		int p = s.find_last_not_of(" ");
		s.erase(s.begin() + p +1 ,s.end());

	}

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

	bool QueryPreprocessor::trimAndCheckClause(string clause, int num){
		clause = trim(clause);
		clause = clause.substr(num,clause.size() -num);
	}
	bool QueryPreprocessor::splitAndCheckClause(string clause, int num){
		int p = clause.find(" and ");
		if(p < clause.length()){
			string s1 = trim(clause.substr(0,p));
			string s2 = trim(clause.substr(p+5,clause.size()-p-5));

		switch(num){
			case 4:
				if(!checkAttribute(s1))
					return false;
				break;
			case 7:
				if(!checkPattern(s1))
					return false;
				break;
			case 9:
				if(!checkRelation(s1))
					return false;
				break;
			default:
				return false;
				break;
			}
		return splitAndCheckClause(s2, num);
	
		}else{

		switch(num){
			case 4:
				return checkAttribute(clause);
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
	bool QueryPreprocessor::checkAttribute(string attribute){
		return true;
	}
	bool QueryPreprocessor::checkPattern(string pattern){
		int p = pattern.find("(");
		string synonym = trim(pattern.substr(0,p));
		string type = getType(synonym);
		if(type == "while"){
			return checkWhile(pattern);
		}else if(type == "if"){
			return checkIf(pattern);
		}else if(type == "assign"){
			return checkAssign(pattern);
		}
		return false;
	}
	bool QueryPreprocessor::checkRelation(string relation){
		int p1 = relation.find("(");
		string relationType = trim(relation.substr(0,p1));
		int p2 = relation.find(",");
		string relationType = trim(relation.substr(p1+1,p2-p1-1));
		int p3 = relation.find(")");
		string relationType = trim(relation.substr(p2+1,p3-p2-1));

	}
	
	bool QueryPreprocessor::checkWhile(string pattern){

	}

	bool QueryPreprocessor::checkIf(string pattern){

	}

	bool QueryPreprocessor::checkAssign(string pattern){

	}




