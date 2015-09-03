#include "Tokenizer.h"

ifstream _stream;

Tokenizer::Tokenizer(){
}

Tokenizer::Tokenizer(string fileName){
    _stream.open(fileName);
}



vector<ParsingToken> Tokenizer::start(){
	vector<ParsingToken> programTokenList;
	string str;
    int currLineIndex = 0;

    while (getline(_stream, str)) {

		int lineIndex = -1;
		if(Tokenizer::isCodeBody(str)){
			currLineIndex++;
			lineIndex = currLineIndex;
		}

		Tokenizer::tokenizeLine(str, lineIndex, programTokenList);
		
    }

	_stream.close();
	return programTokenList;
}

void Tokenizer::tokenizeLine(string line, int lineIndex, vector<ParsingToken> &tokenList) {
    line = Tokenizer::appendWhiteSpace(line);
	vector<string> tokens;
	tokens = ParserUtils::split(line, ' ');
	for(int i = 0; i<tokens.size(); i++){
		if(tokens[i].size() >= 2 && tokens[i].at(0) == '\\' && tokens[i].at(1) == '\\'){
			return; //return immediately as the rest of the line is commented
		}
		else{
			tokenList.push_back(ParsingToken::ParsingToken(tokens[i], lineIndex));
		}
	}
}

string Tokenizer::appendWhiteSpace(string input){
  	
	vector<string> symbolList;
	symbolList.push_back(";");
	symbolList.push_back("{");
	symbolList.push_back("}");
	symbolList.push_back("(");
	symbolList.push_back(")");
	symbolList.push_back("*");
	symbolList.push_back("+");
	symbolList.push_back("=");
	for(int i=0; i <= symbolList.size() - 1 ; i++){
		ParserUtils::replaceAll(input, symbolList[i], " " + symbolList[i] + " ");
	}

	regex e ("[[:space:]]+");
	const string format=" ";
	input = regex_replace(input,e,format,regex_constants::format_default);

	return input;

}

bool Tokenizer::isCodeBody(string code){
	bool foundAlpha = false;
	ParserUtils::replaceAll(code," ","");

	for(std::string::iterator it = code.begin(); it != code.end(); ++it) {
		if (isalpha(*it)){
			foundAlpha = true;
			break;
		} 
	}


	if(!foundAlpha || foundAlpha && code.find("procedure") == 0){
		return false;
	}
	else{
		return foundAlpha;
	}

}
