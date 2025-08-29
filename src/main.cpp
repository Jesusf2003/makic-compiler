#include <iostream>
#include <direct.h>

#include "cmd.h"

#define MAX_NUM_ARGVS 128
#define MAX_PATH 1024

static char cwd[MAX_PATH];

void cmdEcho(int argc, char **argv)
{
    for (int i = 1; i < argc; i++)
    {
        printf("%s ", argv[i]);
    }
    printf("\n");
}

void cmdQuit(int argc, char** argv) {
    printf("See ya :)\n");
    exit(0);
}

void initCommands()
{
    cmd::addCommand("echo", cmdEcho);
    cmd::addCommand("quit", cmdQuit);
}

int main(int argc, char **argv)
{
    // initialize commands
    initCommands();
    char input[256];
    std::cout << "Welcome user!" << std::endl;
    while (true)
    {
        std::cout << "> ";
        if (!fgets(input, sizeof(input), stdin))
            break;
        cmd::execCommand(input);
    }
    return 0;
}