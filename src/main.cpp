#include <iostream>
#include <direct.h>

#include "cmd.h"
#include "shell.h"

#define MAX_INPUT 256

void initCmds()
{
}

int main(int argc, char **argv)
{
    initCmds();

    char input[MAX_INPUT];
    std::cout << "\n" << "      Welcome user!" << "\n" << std::endl;

    while (true)
    {
        std::cout << "> ";
        if (!fgets(input, sizeof(input), stdin))
            break;
        // must execute a run function
    }
    return 0;
}