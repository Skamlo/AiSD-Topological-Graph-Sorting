#include <iostream>
#include <vector>
#include <string>
#include <random>
#include "graph.h"
#include "menuFunctions.h"


std::string stringToLowercase(std::string text)
{
    for (auto &x : text)
    {
        x = tolower(x);
    }

    return text;
}


bool textValidation(std::string *numbers) // Performs preprocessing data such as removing spaces
{
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
    for (int i = 0; i < numbers.size(); i++)
    {
        if (numbers[i] == ' ')
        {
            ids->push_back(currentNumber);
            currentNumber = 0;
        }
        else if (numbers[i] >= '0' && numbers[i] <= '9')
        {
            currentNumber = currentNumber * 10 + (numbers[i] - '0');
        }
    }
    ids->push_back(currentNumber);
}


bool isValidValues(std::vector<int> &ids, int nNodes)
{
    for (int i=0; i<ids.size(); i++)
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


bool inputGenerate(std::vector<Node> &nodes)
{
    // read number of nodes and saturation
    std::string nNodesStr;
    int nNodes = 0;

    std::string saturationStr;
    int saturation = 0;

    std::cout << "     nodes> ";
    std::getline(std::cin, nNodesStr);
    nNodes = strToInt(nNodesStr);

    std::cout << "saturation> ";
    std::getline(std::cin, saturationStr);
    saturation = strToInt(saturationStr);

    // do some magic
}


bool inputUserProvided(std::vector<Node> &nodes)
{
    // read number of nodes in graph
    std::string nNodesStr;
    int nNodes = 0;
    std::cout << "nodes> ";
    std::getline(std::cin, nNodesStr);
    nNodes = strToInt(nNodesStr);

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
        // std::cin >> idsString;
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

        // create node object
        Node node(i);
        for (int j=0; j<ids.size(); j++)
            node.addNeighbor(ids[j]);

        nodes.push_back(node);
    }

    return true;
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


void printGraph(std::vector<Node> nodes, std::string graphRepresentation)
{
    if (graphRepresentation == "list")
    {
        int nSpaces = countDigits(nodes.size());

        for (int i=0; i<nodes.size(); i++)
        {
            for (int j=0; j<nSpaces-countDigits(i+1)+1; j++)
                std::cout << " ";
            std::cout << i+1 << "> ";

            for (int j=0; j<nodes[i].getNeighbors().size(); j++)
            {
                std::cout << nodes[i].getNeighbors()[j] << " ";
            }
            std::cout << "\n";
        }
    }
    else if (graphRepresentation == "matrix")
    {
        // do some magic
    }
    else if (graphRepresentation == "table")
    {
        // do some magic
    }
}
