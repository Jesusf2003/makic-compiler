#include "cmd.h"

namespace cmd
{
    // custom args
    int cargc = 0;
    char **cargv = nullptr;

    void defaultExt(char *path, char *ext, size_t bufsize)
    {
        if (!path || !*path)
            return;
        char *src = path + strlen(path) - 1;
        while (src != path && *src != PATH_SEPARATOR)
        {
            if (*src == '.')
                return;
            src--;
        }
        strncat(path, ext, bufsize - strlen(path) - 1);
    }

    void defaultPath(char *path, char *basepath)
    {
        if (!path || !*path)
            return;

        if (path[0] == PATH_SEPARATOR)
            return; // ya es ruta absoluta

        char tmp[260];
        snprintf(tmp, sizeof(tmp), "%s/%s", basepath, path);
        strcpy(path, tmp);
    }

    // check cmd to the limit
    int checkNextCmd(const char *check, int last)
    {
        for (int i = last + 1; i < cargc; i++)
        {
            if (!cargv[i] && strcmp(check, cargv[i]) == 0)
                return i;
        }
        return -1;
    }

    int checkCmd(const char *cmd)
    {
        return checkNextCmd(cmd, -1);
    }
}