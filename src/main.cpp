#include <iostream>
#include <direct.h>

#include "shell.h"
#include "cmd.h"

bool running = true;

inline void printLine(const char* prefix, const char *name, long size = -1)
{
    std::cout << prefix << " " << name;
    if (size >= 0)
        std::cout << " (" << size << " bytes)";
    std::cout << "\n";
}

inline void printArgs(int argc, char **argv, int start = 1, const char* sep = " ")
{
    for (int i = start; i < argc; i++)
    {
        if (i > start) std::cout << sep;
        std::cout << argv[i];
    }
}

void cmdLs(int argc, char **argv)
{
    char path[260] = ".";
    if (argc > 1)
        strcpy(path, argv[1]);

    // integrar defaultPath para añadir basepath
    cmd::defaultPath(path, ".");

    char pattern[260];
    snprintf(pattern, sizeof(pattern), "%s\\*.*", path);

    struct _finddata64i32_t fileinfo;
    intptr_t handle = _findfirst64i32(pattern, &fileinfo);
    if (handle == -1)
    {
        std::cout << "ls: cannot access '" << path << "'\n";
        return;
    }

    do
    {
        if (fileinfo.attrib & _A_SUBDIR)
            printLine("[DIR ]", fileinfo.name);
        else
            printLine("[FILE]", fileinfo.name, fileinfo.size);
    } while (_findnext64i32(handle, &fileinfo) == 0);

    _findclose(handle);
}

void cmdEcho(int argc, char **argv)
{
    if (argc == 1)
    {
        std::cout << "Provide a text pls\n";
        return;
    }
    std::cout << "  say(user): ";
    printArgs(argc, argv);
    std::cout << "\n";
}

void cmdQuit(int argc, char **argv)
{
    std::cout << "See ya :)\n";
    running = false;
}

void cmdHelp(int argc, char **argv)
{
    if (argc > 1)
    {
        std::cout << "Help for command: " << argv[1] << "\n";
        return;
    }
    std::cout << "Avaliable commands:\n";
    for (int i = 0; i < shell::cmdCount; i++)
    {
        std::cout << "  - " << shell::cmdList[i].name << "\n";
    }
}

struct CmdDef { const char* name; void (*func)(int, char**); };

CmdDef builtCmds[] = {
    { "echo",   cmdEcho },
    { "quit",   cmdQuit },
    { "ls",     cmdLs   },
    { "help",   cmdHelp }
};

void initCmds()
{
    for (auto& cmd : builtCmds)
    {
        shell::addCmd(cmd.name, cmd.func);
    }
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