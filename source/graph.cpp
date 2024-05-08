#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include <queue>
#include <set>
#include <unordered_set>
#include <stack>
#include "graph.h"
#include "actions.h"

std::vector<std::vector<int>> Graph::createMatrix(int rows, int cols)
{
    return std::vector<std::vector<int>>(rows, std::vector<int>(cols));
}

std::vector<int> Graph::generateUniqueNumbers(int n, int k)
{
    // Check if the range is smaller than the number of required unique numbers
    if (k > n + 1)
    {
        std::cerr << "Error: Number of unique numbers required exceeds the range." << std::endl;
        return std::vector<int>();
    }

    // Create a vector to hold the generated numbers
    std::vector<int> numbers(n + 1);
    for (int i = 0; i <= n; ++i)
    {
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

    std::vector<int> indexes = generateUniqueNumbers(nNodesInUpperTriangle - 1, nNodesToFill);

    // create graph
    matrix = createMatrix(nNodes, nNodes);

    for (int i = 0; i < indexes.size(); i++)
    {
        for (int j = 0; j < nNodes - 1; j++)
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

    for (int i = 1; i <= nNodes; i++)
    {
        // print spaces before node number
        int iLenght = countDigits(i);
        for (int space = 0; space < 5 - iLenght; space++)
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
        for (int j = 0; j < ids.size(); j++)
        {
            matrix[i - 1][ids[j] - 1] = 1;
        }
    }

    return true;
}

void Graph::generateList()
{
    for (int r = 0; r < matrix.size(); r++)
    {
        std::vector<int> row;

        for (int c = 0; c < matrix.size(); c++)
        {
            if (matrix[r][c] == 1)
            {
                row.push_back(c + 1);
            }
        }

        list.push_back(row);
    }
}

void Graph::generateTable()
{
    for (int r = 0; r < matrix.size(); r++)
    {
        for (int c = 0; c < matrix.size(); c++)
        {
            if (matrix[r][c] == 1)
            {
                std::vector<int> edge;
                edge.push_back(r + 1);
                edge.push_back(c + 1);
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
    for (int i = 1; i <= matrix.size(); i++)
        std::cout << " " << i;

    std::cout << "\n--+-";
    for (int i = 1; i <= matrix.size(); i++)
        std::cout << "--";

    std::cout << "\n";
    for (int i = 0; i < matrix.size(); i++)
    {
        std::cout << i + 1 << " |";
        for (int j = 0; j < matrix.size(); j++)
        {
            std::cout << " " << matrix[i][j];
        }
        std::cout << "\n";
    }
}

void Graph::printList()
{
    for (int i = 0; i < list.size(); i++)
    {
        std::cout << i + 1 << ">";
        for (int j = 0; j < list[i].size(); j++)
        {
            std::cout << " " << list[i][j];
        }
        std::cout << "\n";
    }
}

void Graph::printTable()
{
    for (int i = 0; i < table.size(); i++)
    {
        std::cout << "\t[" << table[i][0] << ", " << table[i][1] << "]\n";
    }
}

void Graph::find()
{
    // read start node
    std::string startNodeStr;
    int startNode = 0;
    std::cout << "  from> ";
    std::getline(std::cin, startNodeStr);
    startNode = strToInt(startNodeStr);

    // read end node
    std::string endNodeStr;
    int endNode = 0;
    std::cout << "    to> ";
    std::getline(std::cin, endNodeStr);
    endNode = strToInt(endNodeStr);

    bool exist = false;

    if (graphRepresentation == "matrix")
        exist = isEdgeExistMatrix(startNode, endNode);
    else if (graphRepresentation == "list")
        exist = isEdgeExistList(startNode, endNode);
    else if (graphRepresentation == "table")
        exist = isEdgeExistTable(startNode, endNode);

    // print
    if (exist)
    {
        std::cout << "True: edge (" << startNode << ", " << endNode << ") exists in the Graph!\n";
    }
    else
    {
        std::cout << "False: edge (" << startNode << ", " << endNode << ") does not exist in the Graph!\n";
    }
}

bool Graph::isEdgeExistMatrix(int startNode, int endNode)
{
    if (matrix[startNode - 1][endNode - 1] == 1)
        return true;
    else
        return false;
}

bool Graph::isEdgeExistList(int startNode, int endNode)
{
    for (int i = 0; i < list[startNode].size(); i++)
    {
        if (list[startNode][i] == endNode)
            return true;
    }
    return false;
}

bool Graph::isEdgeExistTable(int startNode, int endNode)
{
    if (tableAlreadyCreated == false)
    {
        generateTable();
    }

    for (int i = 0; i < table.size(); i++)
    {
        if (table[i][0] == startNode && table[i][1] == endNode)
            return true;
    }

    return false;
}

void Graph::BFS()
{
    // read starting node
    // std::string startNodeStr;
    int startNode = 0;
    // std::cout << "start node> ";
    // std::getline(std::cin, startNodeStr);
    // startNode = strToInt(startNodeStr) - 1; // -1 because we start counting nodes from 1

    // print breath-first search
    if (graphRepresentation == "matrix")
    {
        BFSmatrix(startNode);
    }
    else if (graphRepresentation == "list")
    {
        BFSlist(startNode);
    }
    else if (graphRepresentation == "table")
    {
        BFStable(startNode);
    }
}

// !raczej usuniemy wybieranie noda bo to generuje potem problem niepotrzebny
void Graph::DFS()
{
    // read starting node
    std::string startNodeStr;
    int startNode = 0;
    // std::cout << "start node> ";
    // std::getline(std::cin, startNodeStr);
    // startNode = strToInt(startNodeStr) - 1; // -1 because we start counting nodes from 1

    // print depth-first search
    if (graphRepresentation == "matrix")
    {
        DFSmatrix(startNode);
    }
    else if (graphRepresentation == "list")
    {
        DFSlist(startNode);
    }
    else if (graphRepresentation == "table")
    {
        DFStable(startNode);
    }
}

// MATRIX REPRESENTATION
void Graph::DFSrecursiveMatrix(std::vector<bool> &visitedNodes, int currentNode)
{
    visitedNodes[currentNode] = true;
    std::cout << currentNode + 1 << " ";

    // going through nodes
    for (int neighbor = 0; neighbor < matrix.size(); ++neighbor)
    {
        if (matrix[currentNode][neighbor] == 1 && !visitedNodes[neighbor])
        {
            Graph::DFSrecursiveMatrix(visitedNodes, neighbor);
        }
    }

    // continue even if node has no successor
    for (int nextNode = currentNode + 1; nextNode < matrix.size(); ++nextNode)
    {
        if (!visitedNodes[nextNode])
        {
            Graph::DFSrecursiveMatrix(visitedNodes, nextNode);
            break;
        }
    }
}

void Graph::DFSmatrix(int startNode)
{
    int nNodes = matrix.size();
    std::vector<bool> visitedNodes(nNodes, false);
    Graph::DFSrecursiveMatrix(visitedNodes, startNode);
}

void Graph::BFSmatrix(int startNode) // !algorithm skips some nodes
{
    int numNodes = matrix.size();
    std::vector<bool> visitedNodes(numNodes, false);
    std::set<int> queue;

    queue.insert(startNode);
    visitedNodes[startNode] = true;

    while (!queue.empty())
    {
        int currentNode = *queue.begin();
        queue.erase(queue.begin());
        std::cout << currentNode + 1 << " ";

        bool hasUnvisitedNodes = false;

        for (int neighbor = 0; neighbor < numNodes; ++neighbor)
        {
            if (matrix[currentNode][neighbor] == 1 && !visitedNodes[neighbor])
            {
                queue.insert(neighbor);
                visitedNodes[neighbor] = true;
                hasUnvisitedNodes = true;
            }
        }

        if (!hasUnvisitedNodes)
        {
            for (int nextNode = currentNode + 1; nextNode < numNodes; ++nextNode)
            {
                if (!visitedNodes[nextNode])
                {
                    queue.insert(nextNode);
                    visitedNodes[nextNode] = true;
                    break;
                }
            }
        }
    }
}

// LIST REPRESENTATION
void Graph::BFSlist(int startNode) // !algorithm skips some nodes
{
    std::queue<int> queue;
    std::unordered_set<int> visited;

    queue.push(startNode);
    visited.insert(startNode);

    while (!queue.empty())
    {
        int currentNode = queue.front();
        queue.pop();
        std::cout << currentNode + 1 << " ";

        bool hasUnvisitedNodes = false;

        for (int neighbor : list[currentNode])
        {
            if (visited.find(neighbor) == visited.end())
            {
                queue.push(neighbor);
                visited.insert(neighbor);
                hasUnvisitedNodes = true;
            }
        }

        if (!hasUnvisitedNodes)
        {
            for (int nextNode = currentNode + 1; nextNode < matrix.size(); ++nextNode)
            {
                if (visited.find(nextNode) == visited.end())
                {
                    queue.push(nextNode);
                    visited.insert(nextNode);
                    break;
                }
            }
        }
    }
}

void Graph::DFSrecursiveList(int currentNode, std::unordered_set<int> &visited) //! algorithm prints out of range node
{
    visited.insert(currentNode);
    std::cout << currentNode + 1 << " ";

    for (int neighbor : list[currentNode])
    {
        if (visited.find(neighbor) == visited.end())
        {
            DFSrecursiveList(neighbor, visited);
        }
    }
}

void Graph::DFSlist(int startNode)
{
    std::unordered_set<int> visited;
    DFSrecursiveList(startNode, visited);

    for (int i = 0; i < list.size(); ++i)
    {
        if (visited.find(i) == visited.end())
        {
            DFSrecursiveList(i, visited);
        }
    }
}

// TABLE REPRESENTATION
void Graph::BFStable(int startNode) //! algorithm skips some nodes
{
    std::unordered_set<int> visited;
    std::queue<int> queue;

    queue.push(startNode);
    visited.insert(startNode);

    while (!queue.empty())
    {
        int currentNode = queue.front();
        queue.pop();
        std::cout << currentNode + 1 << " ";

        for (const auto &edge : table)
        {
            int u = edge[0];
            int v = edge[1];
            if (u == currentNode && visited.find(v) == visited.end())
            {
                queue.push(v);
                visited.insert(v);
            }
            else if (v == currentNode && visited.find(u) == visited.end())
            {
                queue.push(u);
                visited.insert(u);
            }
        }
    }
}

void Graph::DFStable(int startNode)
{
}
