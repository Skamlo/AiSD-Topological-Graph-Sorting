#pragma once

#include <vector>
#include <string>

std::vector<std::vector<int>> createMatrix(int rows, int cols);
bool inputGenerate(std::vector<std::vector<int>>* graph);
bool inputUserProvided(std::vector<std::vector<int>>* graph);
void printGraph(std::vector<std::vector<int>> graph, std::string graphRepresentation);
