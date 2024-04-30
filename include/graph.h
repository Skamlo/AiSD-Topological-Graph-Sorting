# pragma once

#include <vector>

class Node {
private:
    int nodeId;
    std::vector<int> neighbors;
public:
    Node(int id);
    ~Node();
    void addNeighbor(int neighbor);
    int getId();
    std::vector<int> getNeighbors();
};