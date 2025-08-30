#include "cmd.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>

#define MAX_COMMANDS 128

namespace cmd
{
    // custom args
    int cargc = 0;
    char **cargv = nullptr;

    // check cmd to the limit
    int checkNextCommand(const char *check, int last)
    {
        for (int i = last + 1; i < cargc; i++)
        {
            if (!cargv[i])
                continue;
            if (strcmp(check, cargv[i]) == 0)
                return i;
        }
        return 0;
    }
    int checkCommand(const char *cmd)
    {
        return checkNextCommand(cmd, 0);
    }
}