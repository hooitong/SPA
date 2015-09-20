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
	//cout << endl << "=====RUNNNING CASE -> " << query << endl;
    try {
        queryTree = new QueryTree();
        QNode* root = queryTree->createNode(QUERY, "");
        queryTree->setAsRoot(root);

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
			//cout << "declaration fails" << endl;
			return NULL;
		}
		if (!result->isValidResult()) {
			//cout << "result fails" << endl;
			return NULL;
		}
		if (!condition->isValidCondition()) {
			//cout << "condition fails" << endl;
			return NULL;
		}

        return queryTree;
    } catch (exception e) {
		//cout << "exception happens" << endl;
		//cout << e.what() << endl;
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
	return string::npos;
}

int QueryPreprocessor::find(string long_string, string substring_to_find) {
	return find(long_string, substring_to_find, 0);
}

