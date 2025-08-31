#include "cmd.h"

namespace cmd
{
    // custom args
    int cargc = 0;
    char **cargv = nullptr;

    void defaultExt(char *path, char *ext)
    {
        if (!path || !*path) return;
        char *src = path + strlen(path) - 1;
        while (src != path && *src != PATH_SEPARATOR)
        {
            if (*src == '.') return;
            src--;
        }
        strcat(path, ext);
    }

    void defaultPath(char *path, char *basepath)
    {
        char temp[128];
        if (path[0] == PATH_SEPARATOR)
            return;
        strcpy(temp, path);
        strcpy(path, basepath);
        strcat(path, temp);
    }

    // check cmd to the limit
    int checkNextCmd(const char *check, int last)
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
    int checkCmd(const char *cmd)
    {
        return checkNextCmd(cmd, 0);
    }
}