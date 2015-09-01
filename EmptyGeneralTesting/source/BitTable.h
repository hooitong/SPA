#pragma once

#include <map>
#include <vector>


class BitTable{
  private:
     std::map<int, std::vector<bool>> vectorList;
     void padVector(std::vector<bool> vector, int length);

  public:
    void putRelation(int parent, int child);
    std::vector<bool>* getChildren(int parent);
    bool containsChild(int parent, int child);
    std::vector<int> toVector(int parent);
};