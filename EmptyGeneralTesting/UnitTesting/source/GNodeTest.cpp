#include <cppunit/config/SourcePrefix.h>

#include "GNodeTest.h"
#include "PKB.h"

#include <vector>
#include <string>

void GNodeTest::setUp() {
}

void GNodeTest::tearDown() {
}

CPPUNIT_TEST_SUITE_REGISTRATION(GNodeTest);

void GNodeTest::testGetAllPossibleEndNodes() {
	GNode* node1 = new GNode(1);
	GNode* node2 = new GNode(2);
	GNode* node3 = new GNode(3);
	GNode* node4 = new GNode(4);

	node1->addForwardNode(node2);
	node2->addForwardNode(node3);
	node2->addForwardNode(node4);

	vector<GNode*> nodes;
	node1->getAllPossibleEndNodes(node1->getLineNumber(), false, nodes);
	CPPUNIT_ASSERT(nodes.size() == 2);
	CPPUNIT_ASSERT(nodes[0] == node3);
	CPPUNIT_ASSERT(nodes[1] == node4);

	node4->addForwardNode(node1);
	vector<GNode*> nodes2;
	node1->getAllPossibleEndNodes(node1->getLineNumber(), false, nodes2);
	CPPUNIT_ASSERT(nodes2.size() == 2);
	CPPUNIT_ASSERT(nodes2[0] == node3);
	CPPUNIT_ASSERT(nodes2[1] == node1);

}
