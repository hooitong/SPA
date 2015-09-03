#pragma once

#include "GrammarToken.h"
#include "GlobalType.h"
#include <map>

class Grammar {
  public:
	
	Grammar(void);
	~Grammar(void);

	void initiate();
	map<GrammarTType, GrammarToken> convertStringMapToTokenMap(map<GrammarTType, string> typeToStringMap);
	GrammarToken getTokenByType(GrammarTType);

  private:
	
};