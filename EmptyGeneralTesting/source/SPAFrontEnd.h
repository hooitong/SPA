#pragma once
#include "Parser.h"

class SPAFrontEnd {
  private:
    Parser pObj;
	//DesignExtractor deObj;

  public:
	  SPAFrontEnd();
	  void parseSource(const std::string fileName);
};