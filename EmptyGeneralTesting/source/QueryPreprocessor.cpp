#include "QueryPreprocessor.h"

#include <string>
#include <vector>

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
    try {
        queryTree = new QueryTree();
        QNode* root = queryTree->createNode(QUERY, "");
        queryTree->setAsRoot(root);
        resultListNode = queryTree->createNode(RESULTLIST, "");
        /*suchthatListNode = queryTree->createNode(SUCHTHATLIST, "");
        patternListNode = queryTree->createNode(PATTERNLIST, "");*/
        queryTree->addChild(root, resultListNode);
        /*queryTree->addChild(root, suchthatListNode);
        queryTree->addChild(root, patternListNode);*/
		conditionsNode = queryTree->createNode(CONDITIONLIST, "");
		queryTree->addChild(root, conditionsNode);

        int p = query.find("Select");

        if(p == string::npos) {
            return NULL;
        }

        string result_cl;
        string declaration = trim(query.substr(0,p));
        if(!checkConditionExists(query)) {
            if(checkDeclaration(declaration)) {
                result_cl = trim(query.substr(p+6, query.length()-p-6));
                if (!checkTuple(result_cl)) {
                    return NULL;
                }
            } else {
                return NULL;
            }
            return queryTree;
        }

        map<int,int>::iterator it = posOfConds.begin();
        //pointer  to first condition/clause
        int ptf = it -> first;

        result_cl = trim(query.substr(p+6, ptf-p-6));
        if(!(checkDeclaration(declaration) && checkTuple(result_cl))) {
            return NULL;
        }

        while (ptf < (int)query.length()) {
            int type = it -> second;
            ++it;
            int pts;
            if (it == posOfConds.end()) {
                pts = query.length();
            } else {
                pts = it -> first;
            }
            string clause = trim(query.substr(ptf, pts - ptf));
            if (!trimAndCheckClause(clause, type)) {
                return NULL;
            }
            ptf = pts;
        }
        return queryTree;
    } catch (exception e) {
        return NULL;
    }
}

bool QueryPreprocessor::checkConditionExists(string query) {
    string query1;
    query1 = query;
    for(int i = 0; i < query1.length(); i++) {
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

    while(pst != string::npos) {
        posOfConds.insert(pair<int,int>(pst, 9));
        pst = query.find("such that",pst + 1);
    }
    while(pst1 != string::npos) {
        posOfConds1.insert(pair<int,int>(pst1, 9));
        pst1 = query1.find("such that",pst1 + 1);
    }

    while(pp != string::npos) {
        posOfConds.insert(pair<int,int>(pp, 7));
        pp = query.find("pattern", pp + 1);
    }

    while(pp1 != string::npos) {
        posOfConds1.insert(pair<int,int>(pp1, 7));
        pp1 = query1.find("pattern", pp1 + 1);
    }

    while(pw != string::npos) {
        posOfConds.insert(pair<int,int>(pw, 4));
        pw = query.find("with", pw + 1);
    }

    while(pw1 != string::npos) {
        posOfConds1.insert(pair<int,int>(pw1, 4));
        pw1 = query1.find("with", pw1 + 1);
    }
    if(posOfConds.size() != posOfConds1.size()) {
        return false;
    }

    return true;
}

bool QueryPreprocessor::trimAndCheckClause(string clause, int num) {
    clause = trim(clause);
    clause = clause.substr(num,clause.size()-num);

    return splitAndCheckClause(clause, num);
}

bool QueryPreprocessor::splitAndCheckClause(string clause, int num) {
    clause = trim(clause);
    int p = clause.find(" and ");
    // there doesn't exist "and"

    if(p != string::npos) {
        string s1 = trim(clause.substr(0,p));
        string s2 = trim(clause.substr(p+5,clause.size()-p-5));

        bool valid = true;
        switch(num) {
        case 4:
            valid = valid && checkAttribute(s1);
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

    } else {

        switch(num) {
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
/**************************Tools *********************************/
bool QueryPreprocessor::checkIdent(string ident) {
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
bool QueryPreprocessor::checkElem(string elem) {
    return (checkIdent(elem) || checkAttReference(elem));
}
bool QueryPreprocessor::checkAttReference(string attReference) {

    int p = attReference.find(".");
    if(p == string::npos) return false;
    string s =  attReference.substr(0,p);
    string attribute = attReference.substr(p+1,attReference.length() - p - 1);
    return (checkIdent(s)&&checkAttributeName(attribute));

}
bool QueryPreprocessor::checkVarReference(string varReference) {
    if(varReference.at(0) == '\"' && varReference.at(varReference.length() -1) == '\"') {
        varReference = varReference.substr(1,varReference.length() - 2);
    } else {
        return false;
    }
    return (checkIdent(varReference));
}
bool QueryPreprocessor::checkDesignEntity(string entity) {
    for(int i = 0; i < 10; i++) {
        if(entity == designEntity[i])
            return true;

    }
    return false;
}
bool QueryPreprocessor::checkFactor(string factor) {
    factor = trim(factor);
    if(factor  == "") return false;

    return checkInteger(factor) || checkIdent(factor);
}

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
        }
    }
    return NULL;
}

QNode* QueryPreprocessor::parseVarRef(string argument) {
    if (argument == "_") {
        return queryTree->createNode(ANY,"");
    } else if (argument.at(0) == '\"' && argument.at((int)argument.size()-1) == '\"') {
        return queryTree->createNode(VAR,trim(argument.substr(1,(int)argument.size()-2)));
    } else if (existsRef(argument)) {
        if (getType(argument) == "variable") {
            return queryTree->createNode(VARIABLESYNONYM,argument);
        }
    }
    return NULL;
}

QNode* QueryPreprocessor::parseEntRef(string argument) {
    if (argument == "_") {
        return queryTree->createNode(ANY,"");
    } else if (isdigit(argument.at(0))) {
        return queryTree->createNode(CONST,argument);
    } else if (argument.at(0) == '\"' && argument.at((int)argument.size()-1) == '\"') {
        return queryTree->createNode(VAR,trim(argument.substr(1,(int)argument.size()-2)));
    } else if (existsRef(argument)) {
        if (getType(argument) == "stmt") {
            return queryTree->createNode(STMTSYNONYM,argument);
        } else if (getType(argument) == "while") {
            return queryTree->createNode(WHILESYNONYM,argument);
        } else if (getType(argument) == "assign") {
            return queryTree->createNode(ASSIGNSYNONYM,argument);
        } else if (getType(argument) == "prog_line") {
            return queryTree->createNode(PROGLINESYNONYM,argument);
        } else if (getType(argument) == "variable") {
            return queryTree->createNode(VARIABLESYNONYM,argument);
        }
    }
    return NULL;
}

QNode* QueryPreprocessor::parseEntRefNoUnderscore(string argument) {
	if (argument == "_") {
		return NULL;
	}
	return parseEntRef(argument);
}

/**************************Use Declaration *********************************/
bool QueryPreprocessor::existsRef(string reference) {
    for(size_t i = 0; i<refDeclared.size(); i++) {
        if(reference == refDeclared.at(i).synonym) {
            return true;
        }
    }
    return false;
}
string QueryPreprocessor::getType(string synonym) {
    for(size_t i = 0; i<refDeclared.size(); i++) {
        if(synonym == refDeclared.at(i).synonym) {
            return refDeclared.at(i).type;
        }
    }
    return "";
}

/**************************With  *********************************/
bool QueryPreprocessor::checkAttributeName(string attName) {
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
	/*if(checkAttReference(ref1)&& checkAttReference(ref2)){

	}else if(checkVarReference(ref1) && checkVarReference(ref2)){
		leftHandSide = queryTree->createNode(VAR,ref1);
		rightHandSide = queryTree->createNode(PROGLINESYNONYM,ref2);
	}else if(checkIdent(ref1) &&  checkIdent(ref2)){
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


/**************************Relation *********************************/
bool QueryPreprocessor::checkRelation(string relation) {
    int p1 = relation.find("(");
    string relationType = trim(relation.substr(0,p1));
    int p2 = relation.find(",");
    string argument1 = trim(relation.substr(p1+1,p2-p1-1));
    int p3 = relation.find(")");
    string argument2 = trim(relation.substr(p2+1,p3-p2-1));

    QNode* relationNode = queryTree->createNode(RELATION,relationType);
    QNode* leftHandSide;
    QNode* rightHandSide;

    if (relationType == "Modifies") {
        leftHandSide = parseEntRefNoUnderscore(argument1);
        rightHandSide = parseVarRef(argument2);
    } else if (relationType == "Uses") {
        leftHandSide = parseEntRefNoUnderscore(argument1);
        rightHandSide = parseVarRef(argument2);
    } else if (relationType == "Parent" || relationType == "Parent*") {
        leftHandSide = parseStmtRef(argument1);
        rightHandSide = parseStmtRef(argument2);
    } else if (relationType == "Follows" || relationType == "Follows*") {
        leftHandSide = parseStmtRef(argument1);
        rightHandSide = parseStmtRef(argument2);
    } else {
        return false;
    }

    if (leftHandSide == NULL || rightHandSide == NULL) {
        return false;
    }

    queryTree->addChild(relationNode,leftHandSide);
    queryTree->addChild(relationNode,rightHandSide);
    queryTree->addChild(conditionsNode,relationNode);

    return true;
}

/**************************Pattern *********************************/
bool QueryPreprocessor::checkWhile(string pattern) {
	//while : synonym "("varRef "," "_" ")"
    pattern = trim(pattern);
    //pointer of open bracket
    int pob = pattern.find("(");
    if(pob == string::npos) return false;
    string synonym = trim(pattern.substr(0,pob));

	if(getType(synonym)!="while") return false;
    if(checkIdent(synonym)) {
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
        queryTree->addChild(conditionsNode,patternNode);
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

	if(getType(synonym)!="if") return false;
    if(checkIdent(synonym)) {
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
        queryTree->addChild(conditionsNode,patternNode);
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
    if(checkIdent(synonym)) {
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
        queryTree->addChild(conditionsNode,patternNode);
        return true;
    }
    return false;
}
//check_pattern
bool QueryPreprocessor::checkPattern(string pattern) {
    int p = pattern.find("(");
    string patternName = trim(pattern.substr(0,p));
    if (existsRef(patternName)) {
        string type = getType(patternName);
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

/**************************declaration  *********************************/
bool QueryPreprocessor::checkDeclaration(string declaration) {
    //psc = pointer of semicolon
    declaration = trim(declaration);
    if(declaration == "") {
        return true;
    }
    int psc = declaration.find(";");
    string declar_clause = declaration.substr(0, psc);
    while(psc != string::npos) {
        declar_clause = trim(declar_clause);
        //ps = pointer of space
        int ps = declar_clause.find(" ");
        string type = trim(declar_clause.substr(0,ps));
        if(checkDesignEntity(type)) {
            size_t pc = ps;
            do {
                //pc = pointer of comma
                int pnc = declar_clause.find(",", pc + 1);
                if (pnc == string::npos) {
                    pnc = declar_clause.length();
                }
                string synonym = trim(declar_clause.substr(pc + 1, pnc - pc - 1));
                if(checkIdent(synonym) && (!existsRef(synonym))) {
                    entity e = {type, synonym};
                    refDeclared.push_back(e);
                } else {
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
        if(pnsc < declaration.length()) {
            declar_clause = declaration.substr(psc + 1, pnsc - psc -1);
        }
        psc = pnsc;
    }
    return true;
}

/**************************result  *********************************/

bool QueryPreprocessor::addTuple(string single_tuple) {
    single_tuple = trim(single_tuple);
    if (!existsRef(single_tuple)) {
        return false;
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
    } else {
        return false;
    }
    queryTree->addChild(resultListNode, resultNode);
    return true;
}

bool QueryPreprocessor::checkTuple(string tuple) {
    tuple = trim(tuple);
    if(checkElem(tuple)) {
        if(existsRef(tuple)) {
            return addTuple(tuple);
        } else {
            return false;
        }
    } else if (tuple.at(0) == '<') {
        tuple = trim(tuple.substr(1,(int)tuple.size() - 2));
        int pt = 0;
        while (pt < (int)tuple.size()) {
            int nextpt = tuple.find(',',pt);
            if (nextpt == string::npos) {
                nextpt = (int)tuple.size();
            }
            string single_tuple = trim(tuple.substr(pt,nextpt-pt));
            if (!addTuple(single_tuple)) {
                return false;
            }
            pt = nextpt + 1;
        }
        return true;
    }
    return false;
}
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



