#include <iostream>
#include <vector>
#include <string>
#include <random>
#include "graph.h"
#include "actions.h"


std::vector<std::vector<int>> createMatrix(int rows, int cols)
{
    return std::vector<std::vector<int>>(rows, std::vector<int>(cols));
}


bool inputGenerate(std::vector<std::vector<int>>* graph)
{
    // do some magic

    return true;
}


bool inputUserProvided(std::vector<std::vector<int>>* graph)
{
    // read number of nodes in graph
    std::string nNodesStr;
    int nNodes = 0;
    std::cout << "nodes> ";
    std::getline(std::cin, nNodesStr);
    nNodes = strToInt(nNodesStr);

    // create graph
    *graph = createMatrix(nNodes, nNodes);

    for (int i=1; i<=nNodes; i++)
    {
        // print spaces before node number
        int iLenght = countDigits(i);
        for (int space=0; space < 5-iLenght; space++)
            std::cout << " ";

        // read ids connected to current node
        std::string idsString = "";
        std::vector<int> ids;
        std::cout << i << "> ";
        std::getline(std::cin, idsString);

        if (!textValidation(&idsString))
        {
            std::cout << "Incerrect input value.\n";
            return false;
        }

        convertNodes(&ids, idsString);

        // values validation
        if (!isValidValues(ids, nNodes))
        {
            std::cout << "Node id out of range.\n";
            return false;
        }

        // insert value to matrix
        for(int j=0; j < ids.size(); j++)
        {
            (*graph)[i-1][ids[j]-1] = 1;
        }
    }

    return true;
}

void printGraph(std::vector<std::vector<int>> graph, std::string graphRepresentation)
{
    if (graphRepresentation == "list")
    {
        for(int i=0; i<graph.size(); i++)
        {
            // print spaces before node number
            int iLenght = countDigits(i+1);
            for (int space=0; space < 6-iLenght; space++)
                std::cout << " ";

            // nodes
            std::cout << i+1 << ">";
            for(int j=0; j<graph.size(); j++)
            {
                if(graph[i][j] == 1)
                    std::cout << " " << j+1;
            }

            std::cout << "\n";
        }
    }
    else if (graphRepresentation == "matrix")
    {
        std::cout << "  |";
        for(int i=1; i<=graph.size(); i++)
            std::cout << " " << i;

        std::cout << "\n--+-";
        for(int i=1; i<=graph.size(); i++)
            std::cout << "--";

        std::cout << "\n";
        for(int i=0; i<graph.size(); i++)
        {
            std::cout << i+1 << " |";
            for(int j=0; j<graph.size(); j++)
            {
                std::cout << " " << graph[i][j];
            }
            std::cout << "\n";
        }
    }
    else if (graphRepresentation == "table")
    {
        for (int i=0; i<graph.size(); i++)
        {
            for (int j=0; j<graph.size(); j++)
            {
                if(graph[i][j] == 1)
                    std::cout << "   [" << i+1 << ", " << j+1 << "]\n";
            }
        }
    }
}
