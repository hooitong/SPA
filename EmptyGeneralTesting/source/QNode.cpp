#include "QNode.h"
#include "GlobalType.h"
#include <iostream>
#include <vector>

using namespace std;

QNode::QNode(void) {
}

QNode::QNode(QNodeType type, string name) {
    this->type = type;
    this->name = name;
}

QNode::~QNode(void) {
}

QNodeType QNode::getQType() {
    return this->type;
}

string QNode::getString() {
    return this->name;
}

vector<QNode*> QNode::getChildren(void) {
    return this->childrenNodes;
}

void QNode::addChild(QNode* node) {
    this->childrenNodes.push_back(node);
}

bool QNode::isEqualSubtree(QNode* node) {
	/*std::cout << node->name << " " << this->name << endl;
	std::cout << node->type << " " << this->type << endl;
	std::cout << node->childrenNodes.size() << " " << this->childrenNodes.size() << endl;*/
	if (this->name != node->name || this->type != node->type) {
		return false;
	}
	if (this->childrenNodes.size() != node->childrenNodes.size()) {
		return false;
	}
	for (int i = 0; i < (int)node->childrenNodes.size(); ++i) {
		if (!(this->childrenNodes[i])->isEqualSubtree(node->childrenNodes[i])) {
			return false;
		}
	}
	return true;
}