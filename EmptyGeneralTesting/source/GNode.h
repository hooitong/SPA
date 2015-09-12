#pragma once

#include "GlobalType.h"

class GNode {
private:	
	PROGLINE lineNumber;
	GNode* forwardMainNode;
	GNode* forwardSideNode;
	GNode* backNode;

public:
	GNode(PROGLINE lineNumber);
	~GNode(void);

	PROGLINE getLineNumber();
	GNode* getNextMain();
	GNode* getNextSide();
	GNode* getPrev();
	void setNextMain(GNode* main);
	void setNextSide(GNode* side);
	void setPrev(GNode* prev);
};