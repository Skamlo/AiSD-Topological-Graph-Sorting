#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <stack>
#include "graph.h"
#include "actions.h"

#define PLACEHOLDER 0
#define GENERATE 1
#define USER_PROVIDED 2

int inputMode = PLACEHOLDER;

// main graph object
Graph graph;

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
        std::cout << "You did not specify the input mode.\n"
                  << std::endl;
        return 1;
    }

    if (inputMode == GENERATE)
    {
        if (!graph.inputGenerate())
        {
            std::cout << "Graph generation failed.\n";
            return 1;
        }
    }
    else if (inputMode == USER_PROVIDED)
    {
        if (!graph.inputUserProvided())
            return 1;
    }

    while (true)
    {
        std::string option;
        std::cout << "\naction> ";
        std::getline(std::cin, option);
        option = stringToLowercase(option);

        if (option == "print")
        {
            graph.print();
        }
        else if (option == "type")
        {
            graph.changeGraphRepresentation(graph.getNewGraphRepresentation());
        }
        else if (option == "type matrix")
        {
            graph.changeGraphRepresentation("matrix");
        }
        else if (option == "type list")
        {
            graph.changeGraphRepresentation("list");
        }
        else if (option == "type table")
        {
            graph.changeGraphRepresentation("table");
        }
        else if (option == "find")
        {
            graph.find();
        }
        else if (option == "breath-first search" || option == "breath-first" || option == "bfs")
        {
            graph.BFS();
        }
        else if (option == "depth-first search" || option == "depth-first" || option == "dfs")
        {
            graph.DFS();
        }
        else if (option == "khan" || option == "khan sort" || option == "khan-sort" || option == "ks")
        {
            std::cout << "Topological sorting of the graph is: ";
            graph.khanSort();
        }
        else if (option == "tarjans" || option == "tarjans sort" || option == "tarjans-sort" || option == "ts")
        {
            std::cout << "Topological sorting of the graph is: ";
            graph.tarjansSort();
        }
        else if (option == "export")
        {
            graph.exportToTiKZ();
        }
        else if (option == "help")
        {
            std::cout << "Help                  Show this message" << std::endl
                      << "Print                 Print the graph in a previously specified type" << std::endl
                      << "Type                  Change graph printing type" << std::endl
                      << "Find                  Find graph edges" << std::endl
                      << "Breath-first search   Print nodes in Breath-first order" << std::endl
                      << "Depth-first search    Print nodes in Depth-first order" << std::endl
                      << "Khan sort             Print nodes sorted by Khan Algorithm" << std::endl
                      << "Tarjans sort          Print nodes sorted by Tarjan's Algorithm" << std::endl
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
