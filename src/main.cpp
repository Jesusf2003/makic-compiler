#include <iostream>
#include <direct.h>

#include "shell.h"

#define MAX_INPUT 256

void cmdEcho(int argc, char **argv)
{
    if (argc == 1)
    {
        printf("Provide a text pls\n");
        return;
    }
    for (int i = 1; i < argc; i++)
    {
        printf("\n    Say(User): %s \n", argv[i]);
    }
    printf("\n");
}

void cmdQuit(int argc, char **argv)
{
    printf("See ya :)\n");
    exit(0);
}

void initCmds()
{
    shell::addCmd("echo", cmdEcho);
    shell::addCmd("quit", cmdQuit);
}

int main(int argc, char **argv)
{
    initCmds();

    char input[MAX_INPUT];
    std::cout << "\n"
              << "      Welcome user!" << "\n"
              << std::endl;

    while (true)
    {
        std::cout << "> ";
        if (!fgets(input, sizeof(input), stdin))
            break;
        shell::execCmd(input);
    }
    return 0;
}