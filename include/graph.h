#pragma once

#include <vector>
#include <string>

class Graph
{
public:
    // variables
    std::vector<std::vector<int>> matrix;
    std::vector<std::vector<int>> list;
    std::vector<std::vector<int>> table;

    std::string graphRepresentation = "matrix";

    bool listAlreadyCreated = false;
    bool tableAlreadyCreated = false;

    // methods
    std::vector<std::vector<int>> createMatrix(int rows, int cols);
    std::vector<int> generateUniqueNumbers(int n, int k);
    bool inputGenerate();
    bool inputUserProvided();
    void generateList();
    void generateTable();
    void changeGraphRepresentation();
    void print();
    void printMatrix();
    void printList();
    void printTable();
};
