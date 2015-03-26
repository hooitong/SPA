#pragma once

enum GNodeType {
    WHILE_NODE,
    IF_NODE,
    END_NODE,
    START_NODE
};

class GNode {
  public:
    GNode(void);
    ~GNode(void);
};