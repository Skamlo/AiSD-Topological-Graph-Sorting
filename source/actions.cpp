#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <stack>
#include <queue>
#include <set>
#include "graph.h"
#include "actions.h"

std::string stringToLowercase(std::string text)
{
    for (auto &x : text)
    {
        x = tolower(x);
    }

    return text;
}

bool textValidation(std::string *numbers)
{
    /*
        Performs preprocessing data such as removing spaces
    */
    std::string newNumbers;
    int lastIndex = -1;
    for (int i = 0; i < numbers->size(); i++)
    {
        if ((*numbers)[i] == ' ')
        {
            if (lastIndex != -1)
            {
                if (newNumbers[lastIndex] != ' ')
                {
                    newNumbers += ' ';
                    lastIndex += 1;
                }
            }
        }
        else if ((*numbers)[i] >= '0' && (*numbers)[i] <= '9')
        {
            newNumbers += (*numbers)[i];
            lastIndex += 1;
        }
        else
        {
            return false;
        }
    }
    *numbers = newNumbers;
    return true;
}

int strToInt(std::string numberString)
{
    int numberInt = 0;
    for (int i = 0; i < numberString.length(); i++)
    {
        numberInt *= 10;
        numberInt += numberString[i] - '0';
    }
    return numberInt;
}

void convertNodes(std::vector<int> *ids, std::string numbers)
{
    int currentNumber = 0;
    bool anyNode = false;
    for (int i = 0; i < numbers.size(); i++)
    {
        if (numbers[i] == ' ')
        {
            ids->push_back(currentNumber);
            currentNumber = 0;
        }
        else if (numbers[i] >= '0' && numbers[i] <= '9')
        {
            anyNode = true;
            currentNumber = currentNumber * 10 + (numbers[i] - '0');
        }
    }

    if (anyNode)
        ids->push_back(currentNumber);
}

bool isValidValues(std::vector<int> &ids, int nNodes)
{
    for (int i = 0; i < ids.size(); i++)
    {
        if (ids[i] > nNodes)
            return false;
    }
    return true;
}

int countDigits(int number)
{
    int nDigits = 0;
    while (number > 0)
    {
        nDigits++;
        number /= 10;
    }
    return nDigits;
}

bool changeGraphRepresentation(std::string *graphRepresentation)
{
    std::string newRepresentation;
    std::cout << "type> ";
    std::getline(std::cin, newRepresentation);
    newRepresentation = stringToLowercase(newRepresentation);

    if (newRepresentation == "list")
        *graphRepresentation = "list";
    else if (newRepresentation == "matrix")
        *graphRepresentation = "matrix";
    else if (newRepresentation == "table")
        *graphRepresentation = "table";
    else
    {
        std::cout << "This graph type does not exist.\n";
        return 0;
    }
    std::cout << "Graph type was successfully changed.\n";
    return 1;
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

void DFSforMatrix(std::vector<std::vector<int>> &graph, int startNode)
{
    int numNodes = graph.size();
    std::vector<bool> visited(numNodes, false); // Tablica odwiedzin

    // Wywołaj DFS rekurencyjnie dla startowego wierzchołka
    DFSRecursive(graph, visited, startNode);
}

// nie jestem pewny czy to dziala

void BFS(std::vector<std::vector<int>> &graph, int startNode)
{
    int numNodes = graph.size();
    std::vector<bool> visited(numNodes, false); // Tablica odwiedzin
    std::set<int> queue;                        // Zbiór do przechowywania wierzchołków

    // Rozpoczęcie BFS od startowego wierzchołka
    queue.insert(startNode);
    visited[startNode] = true;

    while (!queue.empty())
    {
        int currentNode = *queue.begin();
        queue.erase(queue.begin());
        std::cout << currentNode + 1 << " "; // Wyświetlenie odwiedzonego wierzchołka

        // Przetwarzanie sąsiednich wierzchołków
        for (int neighbor = 0; neighbor < numNodes; ++neighbor)
        {
            if (graph[currentNode][neighbor] == 1 && !visited[neighbor])
            {
                queue.insert(neighbor);
                visited[neighbor] = true;
            }
        }
    }
}