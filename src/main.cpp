#include <iostream>
#include <direct.h>

#include "shell.h"

#define MAX_INPUT 256

void cmdEcho(int argc, char **argv)
{
    if (argc == 1)
    {
        std::cout << "Provide a text pls\n";
        return;
    }
    for (int i = 1; i < argc; i++)
    {
        std::cout << "  say(user): " << argv[i] << "\n";
    }
    std::cout << std::endl;
}

bool running = true;

void cmdQuit(int argc, char **argv)
{
    std::cout << "See ya :)\n";
    running = false;
}

void cmdHelp(int argc, char **argv)
{
    std::cout << "Avaliable commands:\n";
    for (int i = 0; i < shell::cmdCount; i++) {
        std::cout << "  - " << shell::cmdList[i].name << "\n";
    }
}

void initCmds()
{
    shell::addCmd("echo", cmdEcho);
    shell::addCmd("quit", cmdQuit);
    shell::addCmd("help", cmdHelp);
}

int main(int argc, char **argv)
{
    initCmds();
    char input[MAX_INPUT];
    while (running)
    {
        std::cout << "> ";
        if (!fgets(input, sizeof(input), stdin))
            break;
        shell::execCmd(input);
    }
    return 0;
}