#include "QueryPreprocessor.h"

#include <string>
#include <vector>
#include <iostream>

#include "Exception.h"
#include "QueryTree.h"

static string designEntity[] = {"procedure","stmtLst", "stmt", "assign", "call", "while", "if", "variable", "constant", "prog_line"};
static const int num = 10;
static QueryTree* tree;

/**************************General *********************************/

QueryPreprocessor::QueryPreprocessor(void) {
}

QueryPreprocessor::~QueryPreprocessor(void) {
}

QueryTree* QueryPreprocessor::parseQuery(string query) {
	// cout << endl << "=====RUNNNING CASE -> " << query << endl;
    try {
        queryTree = new QueryTree();
        QNode* root = queryTree->createNode(QUERY, "");
        queryTree->setAsRoot(root);
		
		//conditionListNode = queryTree->createNode(CONDITIONLIST, "");
		//queryTree->addChild(root, conditionListNode);

        int select_index = query.find("Select");

        if (select_index == string::npos) {
            return NULL;
        }
        
        string declaration_string = trim(query.substr(0,select_index));
		declaration = new QueryPreprocessorDeclaration(declaration_string);

		result = new QueryPreprocessorResult(declaration);
		condition = new QueryPreprocessorCondition(declaration);

		int first_condition_index = getFirstConditionIndex(query, select_index);

		string result_string = trim(query.substr(select_index + 6, first_condition_index - (select_index + 6)));
		string condition_string = trim(query.substr(first_condition_index, query.length() - first_condition_index));

		resultListNode = result->getResultTree(result_string);
		queryTree->addChild(root, resultListNode);

		conditionListNode = condition->getConditionTree(condition_string);
		queryTree->addChild(root, conditionListNode);

		if (!declaration->isValidDeclaration()) {
			return NULL;
		}
		if (!result->isValidResult()) {
			return NULL;
		}
		if (!condition->isValidCondition()) {
			return NULL;
		}

        return queryTree;
    } catch (exception e) {
        return NULL;
    }
}

int QueryPreprocessor::getFirstConditionIndex(string query, int start_index) {
	int first_index = query.length();
	int first_index_such_that = query.find("such that", start_index);
	int first_index_pattern = query.find("pattern", start_index);
	int first_index_with = query.find("with", start_index);
	if (first_index_such_that != string::npos) {
		first_index = min(first_index, first_index_such_that);
	}
	if (first_index_pattern != string::npos) {
		first_index = min(first_index, first_index_pattern);
	}
	if (first_index_with != string::npos) {
		first_index = min(first_index, first_index_with);
	}
	return first_index;
}
/**************************Tools *********************************/
bool QueryPreprocessor::isIdent(string ident) {
    if(ident.length() == 0)
        return false;

    if(isalpha(ident.at(0))) {
        for(size_t i = 1; i < ident.length(); i++) {
            if(!isalnum(ident.at(i)) && !(ident.at(i) == '#') && !(isalpha(ident.at(i)))) {
                return false;
            }
        }
        return true;
    }

    return false;
}
bool QueryPreprocessor::checkInteger(string number) {

    if(number.length() == 0)
        return false;
    for(size_t i = 0; i < number.length(); i++) {
        if(!isdigit(number.at(i))) {
            return false;
        }
    }
    return true;
}
bool QueryPreprocessor::isElem(string elem) {
    return (isIdent(elem) || isAttReference(elem));
}
bool QueryPreprocessor::isAttReference(string attReference) {

    int p = attReference.find(".");
    if(p == string::npos) return false;
    string s =  attReference.substr(0,p);
    string attribute = attReference.substr(p+1,attReference.length() - p - 1);
    return (isIdent(s)&&isAttributeName(attribute));

}
bool QueryPreprocessor::checkVarReference(string varReference) {
    if(varReference.at(0) == '\"' && varReference.at(varReference.length() -1) == '\"') {
        varReference = varReference.substr(1,varReference.length() - 2);
    } else {
        return false;
    }
    return (isIdent(varReference));
}
bool QueryPreprocessor::isDesignEntityType(string entity) {
    for(int i = 0; i < 10; i++) {
        if(entity == designEntity[i])
            return true;

    }
    return false;
}
bool QueryPreprocessor::checkFactor(string factor) {
    factor = trim(factor);
    if(factor  == "") return false;

    return checkInteger(factor) || isIdent(factor);
}

/**************************With  *********************************/
bool QueryPreprocessor::isAttributeName(string attName) {
    if((attName == "procName") || (attName == "varName") || (attName == "value") || (attName == "stmt#")) {
        return true;
    } else {
        return false;
    }
}
bool QueryPreprocessor::checkAttribute(string attribute) {
	//"with" attrCond
	//attrCond : attrCompare ("and" attrCompare)
	//attrCompare : ref '=' ref
	//ref must be same type
	//ref :attrRef| synonym | ""IDENT"" |Integer
	//attrRef: synonym'.'attrName
	QNode* attributeNode = queryTree->createNode(ATTRIBUTE,"");
    QNode* leftHandSide;
    QNode* rightHandSide;

	//attribute = trim(attribute);
	//pes = pointer of equal sign
	int pes = attribute.find("=");
	if(pes == string::npos) return false;
    string ref1 = trim(attribute.substr(0, pes)); // checked
	string ref2 = trim(attribute.substr(pes+1, attribute.length() - pes -1)); //checked
	/*
	string intOrStrType;
    bool flag1 = false;
    bool flag2 = false;
    string ref1_prefix, ref1_postfix, ref2_prefix, ref2_postfix;
	string ref1_type, ref2_type;

    int unsigned p1 = ref1.find(".");
    if(p1<ref1.size()){
        //means its attrRef
        ref1_prefix = trim(ref1.substr(0,p1));
        ref1_postfix = trim(ref1.substr(p1+1,ref1.size()-p1-1));
        attribute e = attributeTable[ref1_postfix];
        //get_type see which design entity it is declared
        ref1_type = get_type(ref1_prefix);
		for(unsigned int i=0;i<e.prefix_type.size();i++){
			if(ref1_type == e.prefix_type[i]){
            flag1 = true;
            intOrStrType = e.intOrStrType;
			break;
			}
		}
        

    }else{
        if(check_Integer(ref1)){
            ref1_prefix = ref1;
			//ref1_type = "integer";
            intOrStrType = "integer";
            flag1 = true;
        }else if(check_synonym(ref1)){
            string temp_type = get_type(ref1);
            if(temp_type == "prog_line"){
                ref1_prefix = ref1;
				//ref1_type = "prog_line";
                intOrStrType = "integer";
                flag1 = true;
            }
        }else{
            if(ref1[0]=='"' && ref1[ref1.size()-1]=='"'){
				ref1_prefix = ref1.substr(1,ref1.size()-2); //strip ""
                //ref1_type = "string";
                intOrStrType = "string";
                flag1 = true;
            }
        }
    }

    unsigned int p2 = ref2.find(".");
    if(p2<ref2.size()){
        ref2_prefix = trim(ref2.substr(0,p2));
        ref2_postfix = trim(ref2.substr(p2+1,ref2.size()-p2-1));
        attribute e = attributeTable[ref2_postfix];
        ref2_type = get_type(ref2_prefix);
		for(unsigned int i=0;i<e.prefix_type.size();i++){
		
			if(ref2_type == e.prefix_type[i]){
				if(intOrStrType!=e.intOrStrType)
					return false;
				flag2 = true;
				break;
			}
		}
    }else{
        if(check_Integer(ref2)){
            ref2_prefix = ref2;
            ref2_type = "integer";
            if(intOrStrType != "integer")
                return false;
            flag2 = true;
        }else if(check_synonym(ref2)){
            //get_type see which design entity it is declared
            ref2_type = get_type(ref2);
            if(ref2_type == "prog_line"){
                ref2_prefix = ref2;
                if(intOrStrType != "integer")
                    return false;
                flag2 = true;
            }
        }else{
            if(ref2[0]=='"' && ref2[ref2.size()-1]=='"'){
				ref2_prefix = ref2.substr(1,ref2.size()-2);
                ref2_type = "string";
                if(intOrStrType != "string")
                    return false;
                flag2 = true;
            }
        }
    }

    if(flag1&&flag2){
       
        --attr_compare* compare = new attr_compare(ref1_prefix,ref1_type,ref2_prefix,ref2_type,intOrStrType);

		bool b1 = ref1_type=="string"||ref1_type=="integer";
		bool b2 = ref2_type=="string"||ref2_type=="integer";
		if(b1||b2)
			constant_relations.push_front(compare);
        else 
			relations.push_front(compare);
        --
        return true;
    }
    else return false;
	*/
	/*if(isAttReference(ref1)&& isAttReference(ref2)){

	}else if(checkVarReference(ref1) && checkVarReference(ref2)){
		leftHandSide = queryTree->createNode(VAR,ref1);
		rightHandSide = queryTree->createNode(PROGLINESYNONYM,ref2);
	}else if(isIdent(ref1) &&  isIdent(ref2)){
		//check with table
		bool synonym, synonym = false; 
		for(size_t i = 0; i<refDeclared.size(); i++) {
			if(ref1 == refDeclared.at(i).synonym && refDeclared.at(i).type =="prog_line") {
				 synonym = true;
			}
        }
		for(size_t i = 0; i<refDeclared.size(); i++) {
			if(ref2 == refDeclared.at(i).synonym && refDeclared.at(i).type =="prog_line") {	
				synonym = true;
			}
        }
		leftHandSide = queryTree->createNode(PROGLINESYNONYM,ref1);
		rightHandSide = queryTree->createNode(PROGLINESYNONYM,ref2);
 
	}else if(checkInteger(ref1) && checkInteger(ref2)){
		leftHandSide = queryTree->createNode(INTERGER,ref1);
		rightHandSide = queryTree->createNode(INTERGER,ref2);
	}
	*/
	//rightHandSide = queryTree->createNode(EXPRESSION,exprRemoveQuote);
    //queryTree->addChild(withNode,assignSynonymNode);
    //queryTree->addChild(withNode,leftHandSide);
    //queryTree->addChild(withNode,rightHandSide);
    //queryTree->addChild(conditionsNode,patternNode);

    return false;
}

/**************************Pattern *********************************/
/*
bool QueryPreprocessor::checkWhile(string pattern) {
	//while : synonym "("varRef "," "_" ")"
    pattern = trim(pattern);
    //pointer of open bracket
    int pob = pattern.find("(");
    if(pob == string::npos) return false;
    string synonym = trim(pattern.substr(0,pob));

	if (declaration->getSynonymType(synonym) != "while") {
		return false;
	}
    if (isIdent(synonym)) {
        //pointer of comma
        int pc = pattern.find(",");
        if(pc == string::npos) return false;
        string varRef = trim(pattern.substr(pob + 1, pc - pob - 1));
        QNode* patternNode = queryTree->createNode(PATTERN,"");
        QNode* whileSynonymNode = queryTree->createNode(WHILESYNONYM,synonym);
        QNode* leftHandSide = parseVarRef(varRef);
        QNode* rightHandSide;
        if (leftHandSide == NULL) {
            return false;
        }
        int pcb = pattern.find_last_of(")");
        if(pcb == string::npos || pcb != pattern.length() - 1) {
            return false;
        }
        string expr = trim(pattern.substr(pc + 1, pcb - pc - 1));
        string exprRemoveQuote = "";
        if (expr == "_") {
            exprRemoveQuote = "_";
        } else {
            return false;
        }
        rightHandSide = queryTree->createNode(EXPRESSION,exprRemoveQuote);
        queryTree->addChild(patternNode,whileSynonymNode);
        queryTree->addChild(patternNode,leftHandSide);
        queryTree->addChild(patternNode,rightHandSide);
        queryTree->addChild(conditionListNode,patternNode);
        return true;
    }
    return false;
}
bool QueryPreprocessor::checkIf(string pattern) {
    //if : synonym "("varRef "," "_" "," "_" ")"
    pattern = trim(pattern);
    //pointer of open bracket
    int pob = pattern.find("(");
    if(pob == string::npos) return false;
    string synonym = trim(pattern.substr(0,pob));

	if (declaration->getSynonymType(synonym) != "if") {
		return false;
	}
    if (isIdent(synonym)) {
        //pointer of comma
        int pc = pattern.find(",");
		//pointer of second comma
		int psc = pattern.find(",",pc + 1, 1);
        if(pc == string::npos || psc == string::npos) return false;
        string varRef = trim(pattern.substr(pob + 1, pc - pob - 1));
        QNode* patternNode = queryTree->createNode(PATTERN,"");
        QNode* ifSynonymNode = queryTree->createNode(IFSYNONYM,synonym);
        QNode* leftHandSide = parseVarRef(varRef);
        QNode* rightHandSide;
        if (leftHandSide == NULL) {
            return false;
        }
        int pcb = pattern.find_last_of(")");
        if(pcb == string::npos || pcb != pattern.length() - 1) {
            return false;
        }
        string expr = trim(pattern.substr(pc + 1, psc - pc - 1)); 
		string expr2 = trim(pattern.substr(psc + 1,pcb - psc - 1));
        string exprRemoveQuote = "";
        if (expr == "_" && expr2 == "_") {
            exprRemoveQuote = "_";
        } else {
            return false;
        }
        rightHandSide = queryTree->createNode(EXPRESSION,exprRemoveQuote);
        queryTree->addChild(patternNode,ifSynonymNode);
        queryTree->addChild(patternNode,leftHandSide);
        queryTree->addChild(patternNode,rightHandSide);
        queryTree->addChild(conditionListNode,patternNode);
        return true;
    }
    return false;
}
bool QueryPreprocessor::checkAssign(string pattern, string patternName) {
    pattern = trim(pattern);
    //pointer of open bracket
    int pob = pattern.find("(");
    if(pob == string::npos) return false;
    string synonym = trim(pattern.substr(0,pob));
    if(isIdent(synonym)) {
        //pointer of comma
        int pc = pattern.find(",");
        if(pc == string::npos) return false;
        string varRef = trim(pattern.substr(pob + 1, pc - pob - 1));
        QNode* patternNode = queryTree->createNode(PATTERN,"");
        QNode* assignSynonymNode = queryTree->createNode(ASSIGNSYNONYM,synonym);
        QNode* leftHandSide = parseVarRef(varRef);
        QNode* rightHandSide;
        if (leftHandSide == NULL) {
            return false;
        }
        int pcb = pattern.find_last_of(")");
        if(pcb == string::npos || pcb != pattern.length() - 1) {
            return false;
        }
        string expr = trim(pattern.substr(pc + 1, pcb - pc - 1));
        string exprRemoveQuote = "";
        if (expr == "_") {
            exprRemoveQuote = "_";
        } else if ((int)expr.length() == 0) {
            return false;
        } else if ((expr.at(0) == '_' && expr.at(expr.length()-1) == '_') || (expr.at(0) == '\"' && expr.at(expr.length()-1) == '\"')) {
            for (int i = 0; i < (int)expr.size(); ++i) {
                if (expr.at(i) != '\"') {
                    exprRemoveQuote += expr.at(i);
                }
                if (expr.at(i) == '_' && i > 0 && i < (int)expr.length() - 1) {
                    return false;
                }
            }
        } else {
            return false;
        }
        rightHandSide = queryTree->createNode(EXPRESSION,exprRemoveQuote);
        queryTree->addChild(patternNode,assignSynonymNode);
        queryTree->addChild(patternNode,leftHandSide);
        queryTree->addChild(patternNode,rightHandSide);
        queryTree->addChild(conditionListNode,patternNode);
        return true;
    }
    return false;
}
//check_pattern
bool QueryPreprocessor::checkPattern(string pattern) {
    int p = pattern.find("(");
    string patternName = trim(pattern.substr(0,p));
	if (declaration->isDeclaredSynonym(patternName)) {
		string type = declaration->getSynonymType(patternName);
        if (type == "while") {
            return checkWhile(pattern);
        } else if (type == "if") {
            return checkIf(pattern);
        } else if (type == "assign") {
            return checkAssign(pattern, patternName);
        }
    }
    return false;
}
*/
/************************** Others *********************************/

string QueryPreprocessor::trim(string s) {
    int firstNotSpace = 0;
    while (firstNotSpace < (int)s.length() && (s.at(firstNotSpace) == ' ' || s.at(firstNotSpace) == '\t' || s.at(firstNotSpace) == '\n')) {
        ++firstNotSpace;
    }
    if (firstNotSpace == (int)s.length()) {
        return "";
    }
    int lastNotSpace = (int)s.length() - 1;
    while (lastNotSpace >= 0 && (s.at(lastNotSpace) == ' ' || s.at(lastNotSpace) == '\t' || s.at(lastNotSpace) == '\n')) {
        --lastNotSpace;
    }
    s = s.substr(firstNotSpace,lastNotSpace - firstNotSpace + 1);
    return s;
}

int QueryPreprocessor::find(string long_string, string substring_to_find, int start_search_index) {
	bool is_inside_quotes = false;
	int number_of_open_brackets = 0;
	for (int i = start_search_index; i < long_string.length(); ++i) {
		if (i + substring_to_find.length() > long_string.length()) {
			return string::npos;
		}
		if (long_string.at(i) == '"') {
			is_inside_quotes = !is_inside_quotes;
		} else if (long_string.at(i) == '(') {
			++number_of_open_brackets;
		} else if (long_string.at(i) == ')') {
			--number_of_open_brackets;
		}
		if (!is_inside_quotes && number_of_open_brackets == 0) {
			bool is_string_match = true;
			for (int j = 0; j < substring_to_find.length(); ++j) {
				if (long_string.at(i + j) != substring_to_find.at(j)) {
					is_string_match = false;
					break;
				}
			}
			if (is_string_match) {
				return i;
			}
		}
	}
}

int QueryPreprocessor::find(string long_string, string substring_to_find) {
	return find(long_string, substring_to_find, 0);
}

