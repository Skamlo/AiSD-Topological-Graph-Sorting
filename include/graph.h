#pragma once

#include <vector>
#include <string>

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
    void BFS();
    void DFS();
    void DFSrecursive(std::vector<bool> &visited, int currentNode);
    void BFSmatrix(int startNode);
    void DFSmatrix(int startNode);
    void BFSlist(int startNode);
    void DFSlist(int startNode);
    void BFStable(int startNode);
    void DFStable(int startNode);
};
