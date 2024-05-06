#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include "graph.h"
#include "actions.h"

#define PLACEHOLDER 0
#define GENERATE 1
#define USER_PROVIDED 2

int inputMode = PLACEHOLDER;
std::string graphRepresentation = "matrix"; // list, matrix or table

int main(int argc, char *argv[])
{
    // input mode
    if (argc >= 2)
    {
        if (!std::strcmp(argv[1], "--generate") || !std::strcmp(argv[1], "-g"))
            inputMode = GENERATE;
        else if (!std::strcmp(argv[1], "--user-provided") || !std::strcmp(argv[1], "-up"))
            inputMode = USER_PROVIDED;
        else
        {
            std::cout << "You incorrect specify the input mode.\n";
            return 1;
        }
    }
    else
    {
        std::cout << "You did not specify the input mode.\n" << std::endl;
        return 1;
    }

    // value input
    std::vector<std::vector<int>> graph;
    bool sucess = false;

    if (inputMode == GENERATE)
    {
        if (!inputGenerate(&graph))
            return 1;
    }
    else if (inputMode == USER_PROVIDED)
    {
        if (!inputUserProvided(&graph))
            return 1;
    }

    while(true)
    {
        std::string option;
        std::cout << "\naction> ";
        std::getline(std::cin, option);
        option = stringToLowercase(option);

        if (option == "print")
        {
            printGraph(graph, graphRepresentation);
        }
        else if (option == "type")
        {
            changeGraphRepresentation(&graphRepresentation);
        }
        else if (option == "find")
        {
            
        }
        else if (option == "breath-first search" || option == "breath-first")
        {
            
        }
        else if (option == "depth-first search" || option == "depth-first")
        {
            
        }
        else if (option == "help")
        {
            std::cout << "Help                  Show this message" << std::endl
                      << "Print                 Print the graph in a previously specified type" << std::endl
                      << "Type                  Change graph printing type" << std::endl
                      << "Find                  Find graph edges" << std::endl
                      << "Breath-first search   Print nodes in Breath-first order" << std::endl
                      << "Depth-first search    Print nodes in Depth-first order" << std::endl
                      << "Exit                  Exits the program" << std::endl;
        }
        else if (option == "exit")
        {
            break;
        }
        else
        {
            std::cout << "This command does not exist." << std::endl;
        }
    }

    return 0;
}
