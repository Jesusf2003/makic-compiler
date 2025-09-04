#include "shell.h"

#include <cstdio>
#include <cstdlib>
#include <string>

namespace shell
{
    void addCmd(char *name, void (*function)(int argc, char **argv))
    {
        if (cmdCount < MAX_COMMANDS)
        {
            strncpy(cmdList[cmdCount].name, name, sizeof(cmdList[cmdCount].name) - 1);
            cmdList[cmdCount].name[sizeof(cmdList[cmdCount].name) - 1] = '\0';
            cmdList[cmdCount].function = function;
            cmdCount++;
        }
    }

    void execCmd(char *input)
    {
        char *argv[16];
        int argc = 0;

        char *p = input;
        while (*p && argc < 16)
        {
            while (*p && isspace(*p)) p++;
            if (!*p) break;
            argv[argc++] = p;
            while (*p && !isspace(*p)) p++;
            if (*p) *p++ = '\0';
        }

        if (argc == 0)
            return;
        
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