#pragma once

#include "GlobalType.h"
#include <vector>

class GNode {
private:	
	PROGLINE lineNumber;
	vector<GNode*> forwardNodes;
	GNode* backNode;

public:
	GNode(PROGLINE lineNumber);
	~GNode(void);

	PROGLINE getLineNumber();
	vector<GNode*> getForwardNodes();
	GNode* getPrevNode();
	void addForwardNode(GNode* forward);
	void setPrevNode(GNode* prev);
};