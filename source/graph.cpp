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

#include <chrono>
#include <fstream>

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

bool Graph::checkNums(std::string s)
{
    bool isAll = true;

    for (auto c : s)
    {
        if (!(c >= '0' && c <= '9'))
        {
            isAll = false;
        }
    }
    return isAll;
}

bool Graph::inputGenerate()
{
    // read number of nodes in graph
    std::string nNodesStr;
    int nNodes = 0;
    std::cout << "     nodes> ";
    std::getline(std::cin, nNodesStr);
    if (!checkNums(nNodesStr))
        return false;
    nNodes = strToInt(nNodesStr);
    nodesNumber = nNodes;

    // read saturation
    std::string saturationStr;
    int saturation = 0;
    std::cout << "saturation> ";
    std::getline(std::cin, saturationStr);
    if (!checkNums(saturationStr))
        return false;
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
    if (!checkNums(nNodesStr))
        return false;
    nNodes = strToInt(nNodesStr);
    nodesNumber = nNodes;

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

std::string Graph::getNewGraphRepresentation()
{
    std::string newRepresentation;
    std::cout << "type> ";
    std::getline(std::cin, newRepresentation);
    newRepresentation = stringToLowercase(newRepresentation);

    return newRepresentation;
}

void Graph::changeGraphRepresentation(std::string newRepresentation)
{
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
            for (int s = 0; s < countDigits(j + 1); s++)
            {
                std::cout << " ";
            }
            std::cout << matrix[i][j];
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

    std::ofstream outputFile{"output.csv", std::ios_base::app};
    const auto start{std::chrono::high_resolution_clock::now()};

    if (startNode <= 0 || startNode > nodesNumber || endNode <= 0 || endNode > nodesNumber)
    {
        std::cout << "Edge not exist in the Graph!\n";
    }
    else
    {
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
    const auto end{std::chrono::high_resolution_clock::now()};
    auto measureTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    outputFile << measureTime.count() << " find " << nodesNumber << " " << graphRepresentation << std::endl;
    outputFile.flush();
    outputFile.close();
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
    int startNode = 0;

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

void Graph::DFS()
{
    int startNode = 0;

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
void Graph::DFSrecursiveMatrix(std::vector<bool> &visitedNodes, int currentNode) //* DONE
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

void Graph::DFSmatrix(int startNode) //* DONE
{
    int nNodes = matrix.size();
    std::vector<bool> visitedNodes(nNodes, false);
    Graph::DFSrecursiveMatrix(visitedNodes, startNode);
}

void Graph::BFSmatrix(int startNode) //* DONE
{
    int numNodes = matrix.size();
    std::vector<bool> visited(numNodes, false);
    std::queue<int> queue;

    queue.push(startNode);
    visited[startNode] = true;

    while (!queue.empty())
    {
        int currentNode = queue.front();
        queue.pop();
        std::cout << currentNode + 1 << " ";

        // Traverse all nodes, not just neighbors of the current node
        for (int neighbor = 0; neighbor < numNodes; ++neighbor)
        {
            if (matrix[currentNode][neighbor] == 1 && !visited[neighbor])
            {
                queue.push(neighbor);
                visited[neighbor] = true;
            }
        }
    }

    // Handle unconnected nodes
    for (int i = 0; i < numNodes; ++i)
    {
        if (!visited[i])
        {
            queue.push(i);
            visited[i] = true;
            while (!queue.empty())
            {
                int currentNode = queue.front();
                queue.pop();
                std::cout << currentNode + 1 << " ";
                for (int neighbor = 0; neighbor < numNodes; ++neighbor)
                {
                    if (matrix[currentNode][neighbor] == 1 && !visited[neighbor])
                    {
                        queue.push(neighbor);
                        visited[neighbor] = true;
                    }
                }
            }
        }
    }
}
// LIST REPRESENTATION
void Graph::BFSlist(int startNode)
{
    std::vector<bool> visited(nodesNumber, false);
    std::queue<int> queue;

    queue.push(startNode);
    visited[startNode] = true;

    while (!queue.empty())
    {
        int currentNode = queue.front();
        queue.pop();

        std::cout << currentNode + 1 << " ";

        for (int neighbor : list[currentNode])
        {
            if (!visited[neighbor - 1])
            {
                queue.push(neighbor - 1);
                visited[neighbor - 1] = true;
            }
        }
    }

    // Handle unconnected nodes (if any)
    for (int i = 0; i < nodesNumber; ++i)
    {
        if (!visited[i])
        {
            queue.push(i);
            visited[i] = true;
            while (!queue.empty())
            {
                int currentNode = queue.front();
                queue.pop();
                std::cout << currentNode + 1 << " ";
                for (int neighbor : list[currentNode])
                {
                    if (!visited[neighbor - 1])
                    {
                        queue.push(neighbor - 1);
                        visited[neighbor - 1] = true;
                    }
                }
            }
        }
    }
}

void Graph::DFSrecursiveList(std::vector<bool> &visited, int currentNode)
{
    visited[currentNode] = true;
    std::cout << currentNode + 1 << " ";

    for (int i = 0; i < list[currentNode].size(); ++i)
    {
        int neighbor = list[currentNode][i] - 1;
        if (!visited[neighbor])
        {
            DFSrecursiveList(visited, neighbor);
        }
    }
}

void Graph::DFSlist(int startNode)
{
    std::vector<bool> visited(nodesNumber, false);

    for (int i = 0; i < nodesNumber; ++i)
    {
        if (!visited[i])
        {
            DFSrecursiveList(visited, i);
        }
    }
    std::cout << std::endl;
}

// TABLE REPRESENTATION
void Graph::BFStable(int startNode)
{
    std::vector<bool> visited(nodesNumber, false);
    std::queue<int> queue;

    for (int i = 0; i < table.size(); ++i)
    {
        int startNode = table[i][0];
        // int endNode = table[i][1];

        if (!visited[startNode - 1])
        {
            visited[startNode - 1] = true;
            queue.push(startNode - 1);

            while (!queue.empty())
            {
                int currentNode = queue.front();
                queue.pop();
                std::cout << currentNode + 1 << " ";

                for (int j = 0; j < table.size(); ++j)
                {
                    if (table[j][0] == currentNode + 1)
                    {
                        int neighbor = table[j][1];
                        if (!visited[neighbor - 1])
                        {
                            visited[neighbor - 1] = true;
                            queue.push(neighbor - 1);
                        }
                    }
                }
            }
        }
    }
}

void Graph::DFSrecursiveTable(std::vector<bool> &visited, int currentNode)
{
    visited[currentNode] = true;
    std::cout << currentNode + 1 << " ";

    for (int i = 0; i < table.size(); ++i)
    {
        if (table[i][0] == currentNode + 1)
        {
            int neighbor = table[i][1];
            if (!visited[neighbor - 1])
            {
                DFSrecursiveTable(visited, neighbor - 1);
            }
        }
    }
}

void Graph::DFStable(int startNode)
{
    std::vector<bool> visited(nodesNumber, false);

    for (int i = 0; i < table.size(); ++i)
    {
        int startNode = table[i][0];
        if (!visited[startNode - 1])
        {
            DFSrecursiveTable(visited, startNode - 1);
        }
    }
}

void Graph::khanSort()
{
    std::ofstream outputFile{"output.csv", std::ios_base::app};
    const auto start{std::chrono::high_resolution_clock::now()};
    if (graphRepresentation == "matrix")
    {
        khanSortMatrix();
    }
    else if (graphRepresentation == "list")
    {
        khanSortList();
    }
    else if (graphRepresentation == "table")
    {
        khanSortTable();
    }
    const auto end{std::chrono::high_resolution_clock::now()};
    auto measureTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    outputFile << measureTime.count() << " khan " << nodesNumber << " " << graphRepresentation << std::endl;
    outputFile.flush();
    outputFile.close();
}

void Graph::khanSortMatrix()
{
    // Count of incoming edges for each vertex
    std::vector<int> inDegree(nodesNumber, 0);
    for (int i = 0; i < nodesNumber; i++)
    {
        for (int j = 0; j < nodesNumber; j++)
        {
            if (matrix[i][j])
                inDegree[j]++;
        }
    }

    // Queue for vertices with in-degree 0
    std::queue<int> q;
    for (int i = 0; i < nodesNumber; i++)
    {
        if (inDegree[i] == 0)
            q.push(i);
    }

    // Topological order
    std::vector<int> topoOrder;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        topoOrder.push_back(u);

        for (int v = 0; v < nodesNumber; v++)
        {
            if (matrix[u][v])
            {
                inDegree[v]--;
                if (inDegree[v] == 0)
                    q.push(v);
            }
        }
    }

    // Print topological order
    for (int i = 0; i < topoOrder.size(); i++)
        std::cout << topoOrder[i] + 1 << " ";
    std::cout << std::endl;
}

void Graph::khanSortList()
{
    // Count of incoming edges for each vertex
    std::vector<int> inDegree(nodesNumber + 1, 0); // Increase size by 1

    // Update loop to start from 0 and end at nodesNumber
    for (int i = 0; i < nodesNumber; i++)
    {
        for (int j = 0; j < list[i].size(); j++)
        {
            int v = list[i][j];
            inDegree[v]++;
        }
    }

    // Queue for vertices with in-degree 0
    std::queue<int> q;
    for (int i = 0; i < nodesNumber; i++)
    {
        if (inDegree[i + 1] == 0) // Adjusted index
            q.push(i + 1);        // Adjusted index
    }

    // Topological order
    std::vector<int> topoOrder;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        topoOrder.push_back(u);

        for (int j = 0; j < list[u - 1].size(); j++) // Adjusted index
        {
            int v = list[u - 1][j];
            inDegree[v]--;
            if (inDegree[v] == 0)
                q.push(v);
        }
    }

    // Print topological order
    for (int i = 0; i < topoOrder.size(); i++)
        std::cout << topoOrder[i] << " ";
    std::cout << std::endl;
}

void Graph::khanSortTable()
{
    std::vector<int> inDegree(nodesNumber + 1, 0);
    std::vector<std::vector<int>> adjList(nodesNumber + 1);

    // Construct adjacency list
    for (const auto &edge : table)
    {
        adjList[edge[0]].push_back(edge[1] + 1);
        inDegree[edge[1] + 1]++;
    }

    std::queue<int> q;
    for (int i = 1; i <= nodesNumber; ++i)
    {
        if (inDegree[i] == 0)
            q.push(i);
    }

    std::vector<int> topoOrder;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        topoOrder.push_back(u);

        for (int v : adjList[u])
        {
            inDegree[v]--;
            if (inDegree[v] == 0)
                q.push(v);
        }
    }

    // Check for remaining unvisited nodes
    for (int i = 1; i <= nodesNumber; ++i)
    {
        if (inDegree[i] != 0)
            topoOrder.push_back(i);
    }

    for (int i = 0; i < topoOrder.size(); ++i)
        std::cout << topoOrder[i] << " ";
    std::cout << std::endl;
}

void Graph::tarjansSort()
{
    std::ofstream outputFile{"output.csv", std::ios_base::app};
    const auto start{std::chrono::high_resolution_clock::now()};
    if (graphRepresentation == "matrix")
    {
        tarjansSortMatrix();
    }
    else if (graphRepresentation == "list")
    {
        tarjansSortList();
    }
    else if (graphRepresentation == "table")
    {
        tarjansSortTable();
    }
    const auto end{std::chrono::high_resolution_clock::now()};
    auto measureTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    outputFile << measureTime.count() << " tarjan " << nodesNumber << " " << graphRepresentation << std::endl;
    outputFile.flush();
    outputFile.close();
}

void Graph::dfsTarjansSort(int u, std::vector<bool> &visited, std::stack<int> &stack)
{
    visited[u] = true;

    for (int v = 0; v < nodesNumber; ++v)
    {
        if (matrix[u][v] && !visited[v])
            dfsTarjansSort(v, visited, stack);
    }

    stack.push(u);
}

void Graph::dfsTarjansSortList(int u, std::vector<bool> &visited, std::vector<std::vector<int>> &adjacencyList, std::stack<int> &stack)
{
    if (visited[u]) // If already visited, return
        return;

    visited[u] = true;

    for (int v : adjacencyList[u])
    {
        int neighbor = v - 1;
        dfsTarjansSortList(neighbor, visited, adjacencyList, stack); // Recurse on neighbors
    }

    stack.push(u); // Push node onto the stack after all its neighbors are visited
}

void Graph::dfsTarjanSortTable(int u, std::vector<int> &low, std::vector<int> &index, std::vector<bool> &onStack, std::stack<int> &stack)
{
    static int currentIndex = 1; // Start index from 1
    index[u] = currentIndex;
    low[u] = currentIndex;
    currentIndex++;
    stack.push(u);
    onStack[u] = true;

    for (int v : table[u - 1]) // Adjust index to 0-based
    {
        int neighbor = v; // No need to subtract 1
        if (index[neighbor] == -1)
        {
            dfsTarjanSortTable(neighbor, low, index, onStack, stack);
            low[u] = std::min(low[u], low[neighbor]);
        }
        else if (onStack[neighbor])
        {
            low[u] = std::min(low[u], index[neighbor]);
        }
    }

    if (low[u] == index[u])
    {
        while (!stack.empty())
        {
            int v = stack.top();
            stack.pop();
            onStack[v] = false;
            if (v == u)
                break;
        }
    }
}

void Graph::tarjansSortMatrix()
{
    std::vector<bool> visited(nodesNumber, false);
    std::stack<int> stack;

    for (int i = 0; i < nodesNumber; ++i)
    {
        if (!visited[i])
            dfsTarjansSort(i, visited, stack);
    }

    while (!stack.empty())
    {
        std::cout << stack.top() + 1 << " ";
        stack.pop();
    }
    std::cout << std::endl;
}

void Graph::tarjansSortList()
{
    std::vector<bool> visited(nodesNumber, false);
    std::stack<int> stack;

    for (int i = 0; i < nodesNumber; ++i)
    {
        if (!visited[i])
            dfsTarjansSortList(i, visited, list, stack);
    }

    while (!stack.empty())
    {
        std::cout << stack.top() + 1 << " ";
        stack.pop();
    }
    std::cout << std::endl;
}

void Graph::tarjansSortTable()
{
    // Increase the size of vectors to accommodate 1-based indexing
    std::vector<int> low(nodesNumber + 1, -1);
    std::vector<int> index(nodesNumber + 1, -1);
    std::vector<bool> onStack(nodesNumber + 1, false);
    std::stack<int> stack;

    for (int i = 1; i <= nodesNumber; ++i)
    {
        if (index[i] == -1)
        {
            dfsTarjanSortTable(i, low, index, onStack, stack);
        }
    }

    while (!stack.empty())
    {
        std::cout << stack.top() + 1 << " ";
        stack.pop();
    }
    std::cout << std::endl;
}

void Graph::exportToTiKZ()
{
    int nodeCount = matrix.size();

    // Opening TikZ environment with graphdrawing library
    std::cout << "\\begin{tikzpicture}[>=stealth, vertex/.style={circle, draw, minimum size=17pt, inner sep=0pt}]" << std::endl;
    std::cout << "\\usegdlibrary{spring}" << std::endl; // Include graphdrawing library with spring layout

    // Define vertices
    std::cout << "  \\graph[spring layout, node distance=1.5cm, nodes={vertex}]{ " << std::endl;

    // Print vertices
    for (int i = 0; i < nodeCount; ++i)
    {
        std::cout << "    " << i + 1 << " [" << i + 1 << "];" << std::endl;
    }

    // Print edges
    for (int i = 0; i < nodeCount; ++i)
    {
        for (int j = 0; j < nodeCount; ++j)
        {
            if (matrix[i][j] == 1 && j > i) // Avoid printing edges twice
            {
                std::cout << "    " << i + 1 << " -> " << j + 1 << ";" << std::endl;
            }
        }
    }

    // Closing TikZ environment
    std::cout << "  };" << std::endl;
    std::cout << "\\end{tikzpicture}" << std::endl;
}