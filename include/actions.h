#pragma once

#include <vector>
#include <string>
#include "graph.h"

std::string stringToLowercase(std::string text);
std::vector<std::vector<int>> createMatrix(int rows, int cols);
bool textValidation(std::string *numbers);
int strToInt(std::string numberString);
void convertNodes(std::vector<int> *ids, std::string numbers);
bool isValidValues(std::vector<int> &ids, int nNodes);
int countDigits(int number);
bool inputGenerate(std::vector<std::vector<int>> &graph);
bool inputUserProvided(std::vector<std::vector<int>> &graph);
bool changeGraphRepresentation(std::string *graphRepresentation);
void printGraph(std::vector<std::vector<int>> graph, std::string graphRepresentation);
void DFSforMatrix(std::vector<std::vector<int>> &graph, int startNode);
void BFS(std::vector<std::vector<int>> &graph, int startNode);
