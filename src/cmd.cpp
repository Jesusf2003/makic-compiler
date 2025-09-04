#include "cmd.h"

namespace cmd
{
    // custom args
    int cargc = 0;
    char **cargv = nullptr;

    void defaultExt(char *path, char *ext, size_t bufsize)
    {
        if (!path || !*path) return;
        char *src = path + strlen(path) - 1;
        while (src != path && *src != PATH_SEPARATOR)
        {
            if (*src == '.') return;
            src--;
        }
        strncat(path, ext, bufsize - strlen(path) - 1);
    }

    void defaultPath(char *path, char *basepath, size_t bufsize)
    {
        // reduces overflow risks
        char temp[128];
        if (path[0] == PATH_SEPARATOR)
            return;
        // recieves a buffer size with less size
        strncpy(temp, path, sizeof(temp) - 1);
        temp[sizeof(temp) -1] = '\0';
        snprintf(path, bufsize, "%s%s", basepath, temp);
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