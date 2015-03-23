#pragma once
#include <string>
#include <vector>
#include "GlobalType.h"

using namespace std;

class QNode {
private:
	QNodeType type;
	string name;
	vector<QNode*> childrenNodes;

public:
	QNode(void);
	QNode(QNodeType, string);
	~QNode(void);

	QNodeType getQType();
	string getString();
	vector<QNode*> getChildren();

	void addChild(QNode* node);
};