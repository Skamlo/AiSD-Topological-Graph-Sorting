#pragma once

#include <vector>
#include <string>
#include <unordered_set>

class Graph
{
public:
    // VARIABLES
    std::vector<std::vector<int>> matrix;
    std::vector<std::vector<int>> list;
    std::vector<std::vector<int>> table;

    std::string graphRepresentation = "matrix";

    bool listAlreadyCreated = false;
    bool tableAlreadyCreated = false;

    // METHODS
    // graphs creating
    std::vector<std::vector<int>> createMatrix(int rows, int cols);
    std::vector<int> generateUniqueNumbers(int n, int k);
    bool inputGenerate();
    bool inputUserProvided();
    void generateList();
    void generateTable();
    void changeGraphRepresentation();

    // printing
    void print();
    void printMatrix();
    void printList();
    void printTable();

    // finding edges
    void find();
    bool isEdgeExistMatrix(int startNode, int endNode);
    bool isEdgeExistList(int startNode, int endNode);
    bool isEdgeExistTable(int startNode, int endNode);

    // sorting algorithms
    /// functions to handle diffrent variants
    void BFS();
    void DFS();
    /// for matrix representation
    void DFSrecursiveMatrix(std::vector<bool> &visited, int currentNode);
    void DFSmatrix(int startNode);
    void BFSmatrix(int startNode);
    /// for list representation
    void BFSlist(int startNode);
    void DFSlist(int startNode);
    void DFSrecursiveList(int currentNode, std::unordered_set<int> &visited);
    /// for table representation
    void BFStable(int startNode);
    void DFStable(int startNode);
};
