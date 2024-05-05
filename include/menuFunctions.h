#pragma once

#include <vector>
#include "graph.h"

std::string stringToLowercase(std::string text);
bool inputGenerate(std::vector<Node> &nodes);
bool inputUserProvided(std::vector<Node> &nodes);
bool changeGraphRepresentation(std::string *graphRepresentation);
void printGraph(std::vector<Node> nodes, std::string graphRepresentation);
