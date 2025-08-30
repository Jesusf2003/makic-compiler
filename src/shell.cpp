#include "shell.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>

namespace shell
{

    struct Command
    {
        char *name;
        void (*function)(int argc, char **argv);
    };

    inline static Command cmdList[MAX_COMMANDS];
    inline static int cmdCount = 0;

    void addCmd(char *name, void (*function)(int argc, char **argv))
    {
        if (cmdCount < MAX_COMMANDS)
        {
            cmdList[cmdCount].name = name;
            cmdList[cmdCount].function = function;
            cmdCount++;
        }
    }
    void execCmd(char *input)
    {
        char *argv[16];
        int argc = 0;

        char *token = strtok(input, " \t\n");
        while (token && argc < 16)
        {
            argv[argc++] = token;
            token = strtok(NULL, " \t\n");
        }

        if (argc == 0)
            return;

        // Buscar comando en la lista
        for (int i = 0; i < cmdCount; i++)
        {
            if (strcmp(argv[0], cmdList[i].name) == 0)
            {
                cmdList[i].function(argc, argv);
                return;
            }
        }
        printf("Unknown command: %s\n", argv[0]);
    }
}