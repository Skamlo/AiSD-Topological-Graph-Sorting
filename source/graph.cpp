#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include "graph.h"
#include "actions.h"


std::vector<std::vector<int>> createMatrix(int rows, int cols)
{
    return std::vector<std::vector<int>>(rows, std::vector<int>(cols));
}


std::vector<int> generateUniqueNumbers(int n, int k) {
    // Check if the range is smaller than the number of required unique numbers
    if (k > n + 1) {
        std::cerr << "Error: Number of unique numbers required exceeds the range." << std::endl;
        return std::vector<int>();
    }

    // Create a vector to hold the generated numbers
    std::vector<int> numbers(n + 1);
    for (int i = 0; i <= n; ++i) {
        numbers[i] = i;
    }

    // Shuffle the vector
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(numbers.begin(), numbers.end(), g);

    // Take first k elements
    std::vector<int> result(numbers.begin(), numbers.begin() + k);

    return result;
}


bool inputGenerate(std::vector<std::vector<int>>* graph)
{
    // read number of nodes in graph
    std::string nNodesStr;
    int nNodes = 0;
    std::cout << "     nodes> ";
    std::getline(std::cin, nNodesStr);
    nNodes = strToInt(nNodesStr);

    // read saturation
    std::string saturationStr;
    int saturation = 0;
    std::cout << "saturation> ";
    std::getline(std::cin, saturationStr);
    saturation = strToInt(saturationStr);

    // check if saturation is in correct range
    if (saturation < 0 || saturation > 100)
    {
        std::cout << "Saturation must be between 0 and 100.\n";
        return false;
    }

    int nNodesInUpperTriangle = nNodes * (nNodes - 1) / 2;
    int nNodesToFill = nNodesInUpperTriangle * saturation / 100;

    std::vector<int> indexes = generateUniqueNumbers(nNodesInUpperTriangle-1, nNodesToFill);

    // create graph
    *graph = createMatrix(nNodes, nNodes);

    for (int i=0; i<indexes.size(); i++)
    {
        for (int j=0; j<nNodes-1; j++)
        {
            if (indexes[i] + 1 < nNodes - 1 - j)
            {
                (*graph)[j][j + 2 + indexes[i]] = 1;
                break;
            }
            else
            {
                indexes[i] -= (nNodes - 1 - j);
            }
        }
    }

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
