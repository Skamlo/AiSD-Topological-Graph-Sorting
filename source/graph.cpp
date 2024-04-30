#include <vector>
#include "graph.h"


// Constructor
Node::Node(int id)
{
    nodeId = id;
}

// Destructor
Node::~Node()
{
    neighbors.clear();
}

// Method to add a neighbor to the node
void Node::addNeighbor(int neighbor)
{
    neighbors.push_back(neighbor);
}

// Method to get the ID of the node
int Node::getId()
{
    return nodeId;
}

// Method to get the neighbors of the node
std::vector<int> Node::getNeighbors()
{
    return neighbors;
}
