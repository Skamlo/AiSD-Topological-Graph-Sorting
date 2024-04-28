#include <iostream>
#include <vector>

class Node {
private:
    int id;
    std::vector<Node*> neighbors;

public:
    // Constructor
    Node(int id) : id(id) {}

    // Destructor
    ~Node() {
        // Clearing the neighbors vector
        neighbors.clear();
    }

    // Method to add a neighbor to the node
    void addNeighbor(Node* neighbor) {
        neighbors.push_back(neighbor);
    }

    // Method to get the ID of the node
    int getId() const {
        return id;
    }

    // Method to get the neighbors of the node
    std::vector<Node*> getNeighbors() const {
        return neighbors;
    }
};



