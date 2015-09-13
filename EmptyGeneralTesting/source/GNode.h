#pragma once

#include "GlobalType.h"
#include <vector>

class GNode {
private:	
	PROGLINE lineNumber;
	vector<GNode*> forwardNodes;
	vector<GNode*> backNode;

public:
	GNode(PROGLINE lineNumber);
	~GNode(void);

	PROGLINE getLineNumber();
	vector<GNode*> getForwardNodes();
	vector<GNode*> getPrevNode();
	void addForwardNode(GNode* forward);
	void addPrevNode(GNode* prev);
};