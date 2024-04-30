#include <iostream>
#include <vector>
#include <cstring>
#include "graph.h"
#include "menuFunctions.h"

#define PLACEHOLDER 0
#define GENERATE 1
#define USER_PROVIDED 2

std::vector<Node> nodes;

int inputMode = PLACEHOLDER;

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
    if (inputMode == GENERATE)
        if (!inputGenerate(nodes))
            return 1;
    else if (inputMode == USER_PROVIDED)
        std::cout << "It works!\n";
        if (!inputUserProvided(nodes))
            return 1;

    

    return 0;
}
