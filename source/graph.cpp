#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include "graph.h"
#include "actions.h"


std::vector<std::vector<int>> Graph::createMatrix(int rows, int cols)
{
    return std::vector<std::vector<int>>(rows, std::vector<int>(cols));
}


std::vector<int> Graph::generateUniqueNumbers(int n, int k)
{
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


bool Graph::inputGenerate()
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
    matrix = createMatrix(nNodes, nNodes);

    for (int i=0; i<indexes.size(); i++)
    {
        for (int j=0; j<nNodes-1; j++)
        {
            if (indexes[i] + 1 < nNodes - 1 - j)
            {
                matrix[j][j + 2 + indexes[i]] = 1;
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


bool Graph::inputUserProvided()
{
    // read number of nodes in graph
    std::string nNodesStr;
    int nNodes = 0;
    std::cout << "nodes> ";
    std::getline(std::cin, nNodesStr);
    nNodes = strToInt(nNodesStr);

    // create graph
    matrix = createMatrix(nNodes, nNodes);

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
            matrix[i-1][ids[j]-1] = 1;
        }
    }

    return true;
}


void Graph::generateList()
{
    for (int r=0; r<matrix.size(); r++)
    {
        std::vector<int> row;

        for (int c=0; c<matrix.size(); c++)
        {
            if (matrix[r][c] == 1)
            {
                row.push_back(c+1);
            }
        }

        list.push_back(row);
    }
}


void Graph::generateTable()
{
    for (int r=0; r<matrix.size(); r++)
    {
        for (int c=0; c<matrix.size(); c++)
        {
            if (matrix[r][c] == 1)
            {
                std::vector<int> edge;
                edge.push_back(r+1);
                edge.push_back(c+1);
                table.push_back(edge);
            }
        }
    }
}


void Graph::changeGraphRepresentation()
{
    std::string newRepresentation;
    std::cout << "type> ";
    std::getline(std::cin, newRepresentation);
    newRepresentation = stringToLowercase(newRepresentation);

    if (newRepresentation == "matrix")
    {
        graphRepresentation = "matrix";
        std::cout << "Graph type was successfully changed.\n";
    }
    else if (newRepresentation == "list")
    {
        graphRepresentation = "list";
        if (listAlreadyCreated == false)
        {
            generateList();
            listAlreadyCreated = true;
        }
        std::cout << "Graph type was successfully changed.\n";
    }
    else if (newRepresentation == "table")
    {
        graphRepresentation = "table";
        if (tableAlreadyCreated == false)
        {
            generateTable();
            tableAlreadyCreated = true;
        }
        std::cout << "Graph type was successfully changed.\n";
    }
    else
    {
        std::cout << "This graph type does not exist.\n";
    }
}


void Graph::print()
{
    if (graphRepresentation == "matrix")
    {
        printMatrix();
    }
    else if (graphRepresentation == "list")
    {
        printList();
    }
    else if (graphRepresentation == "table")
    {
        printTable();
    }
}


void Graph::printMatrix()
{
    std::cout << "  |";
    for(int i=1; i<=matrix.size(); i++)
        std::cout << " " << i;

    std::cout << "\n--+-";
    for(int i=1; i<=matrix.size(); i++)
        std::cout << "--";

    std::cout << "\n";
    for(int i=0; i<matrix.size(); i++)
    {
        std::cout << i+1 << " |";
        for(int j=0; j<matrix.size(); j++)
        {
            std::cout << " " << matrix[i][j];
        }
        std::cout << "\n";
    }
}


void Graph::printList()
{
    for (int i=0; i<list.size(); i++)
    {
        std::cout << i+1 << ">";
        for (int j=0; j<list[i].size(); j++)
        {
            std::cout << " " << list[i][j];
        }
        std::cout << "\n";
    }
}


void Graph::printTable()
{
    for (int i=0; i<table.size(); i++)
    {
        std::cout << "\t[" << table[i][0] << ", " << table[i][1] << "]\n";
    }
}


// DFS FOR MATRIX HERE

void DFSRecursive(const std::vector<std::vector<int>> &graph, std::vector<bool> &visited, int currentNode)
{
    // Oznacz bieżący wierzchołek jako odwiedzony
    visited[currentNode] = true;
    std::cout << currentNode + 1 << " "; // Wyświetl bieżący wierzchołek

    // Przeszukaj sąsiednie wierzchołki
    for (int neighbor = 0; neighbor < graph.size(); ++neighbor)
    {
        if (graph[currentNode][neighbor] == 1 && !visited[neighbor])
        {
            // Wywołaj rekurencyjnie DFS dla nieodwiedzonego sąsiada
            DFSRecursive(graph, visited, neighbor);
        }
    }
}


// void DFSforMatrix(std::vector<std::vector<int>> &graph, int startNode)
// {
//     int numNodes = graph.size();
//     std::vector<bool> visited(numNodes, false); // Tablica odwiedzin

//     // Wywołaj DFS rekurencyjnie dla startowego wierzchołka
//     DFSRecursive(graph, visited, startNode);
// }

// // nie jestem pewny czy to dziala

// void BFS(std::vector<std::vector<int>> &graph, int startNode)
// {
//     int numNodes = graph.size();
//     std::vector<bool> visited(numNodes, false); // Tablica odwiedzin
//     std::set<int> queue;                        // Zbiór do przechowywania wierzchołków

//     // Rozpoczęcie BFS od startowego wierzchołka
//     queue.insert(startNode);
//     visited[startNode] = true;

//     while (!queue.empty())
//     {
//         int currentNode = *queue.begin();
//         queue.erase(queue.begin());
//         std::cout << currentNode + 1 << " "; // Wyświetlenie odwiedzonego wierzchołka

//         // Przetwarzanie sąsiednich wierzchołków
//         for (int neighbor = 0; neighbor < numNodes; ++neighbor)
//         {
//             if (graph[currentNode][neighbor] == 1 && !visited[neighbor])
//             {
//                 queue.insert(neighbor);
//                 visited[neighbor] = true;
//             }
//         }
//     }
// }