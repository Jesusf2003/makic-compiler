#include "shell.h"
#include "cmd.h"

#include <cstdio>
#include <cstdlib>
#include <string>

namespace shell
{
    void addCmd(const char *name, void (*function)(int argc, char **argv))
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
        // Vinculamos a los globales del namespace cmd
        cmd::cargc = 0;
        static char *argvStorage[16]; // almacenamiento fijo
        cmd::cargv = argvStorage;

        char *p = input;
        while (*p && cmd::cargc < 16)
        {
            while (*p && isspace(*p))
                p++;
            if (!*p)
                break;

            cmd::cargv[cmd::cargc++] = p;

            while (*p && !isspace(*p))
                p++;
            if (*p)
                *p++ = '\0';
        }

        if (cmd::cargc == 0)
            return;

        for (int i = 0; i < cmdCount; i++)
        {
            if (strcmp(cmd::cargv[0], cmdList[i].name) == 0)
            {
                cmdList[i].function(cmd::cargc, cmd::cargv);
                return;
            }
        }

        cmd::printError(0, "Unknown command: %s", cmd::cargv[0]);
    }
}