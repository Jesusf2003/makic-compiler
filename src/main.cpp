#include <iostream>
#include <direct.h>

#include "shell.h"
#include "cmd.h"

#define MAX_INPUT       256
#define MAX_PATH        260

bool running = true;
char path[MAX_PATH] = ".";

void cmdExit(int argc, char **argv)
{
    running = false;
    cmd::printInfo("Exiting shell...");
}

int main(int argc, char **argv)
{
    char input[MAX_INPUT];
    cmd::cargc = argc;
    cmd::cargv = argv;
    shell::addCmd("quit", cmdExit);
    std::cout << "Hola :)" << std::endl;
    while (running)
    {
        std::cout << "> ";
        if (!fgets(input, sizeof(input), stdin))
            break;
        shell::execCmd(input);
    }
    return 0;
}