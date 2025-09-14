#include "cmd.h"

namespace cmd
{
    // custom args
    int cargc = 0;
    char **cargv = nullptr;

    void defaultExt(char *path, char *ext)
    {
        if (!path || !*path)
            return;
        char *src = path + strlen(path) - 1;
        while (src != path && *src != PATH_SEPARATOR && *src != '/' && *src != '\\')
        {
            if (*src == '.')
                return;
            src--;
        }
        strcat(path, ext);
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

    void stripFilename(char *path)
    {
        // get length of path string
        int length = strlen(path) - 1;
        while(length > 0 && path[length] != PATH_SEPARATOR)
            length--;
        path[length] = 0;
    }

    void stripExt(char *path)
    {
        int length = strlen(path) - 1;
        while (length > 0 && path[length] != '.')
            length--;
        if (length)
            path[length] = 0;
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
    
    void printError(int errorType, const char *err, ...)
    {
        const char *prefix;
        switch (errorType)
        {
            case 0: prefix = "Info: "; break;
            case 1: prefix = "Warn: "; break;
            case 2: prefix = "Error: "; break;
            default: prefix = "unknown: "; break;
        }
        fprintf(stderr, "%s", prefix);

        va_list args;
        va_start(args, err);
        vfprintf(stderr, err, args);
        va_end(args);

        fprintf(stderr, "\n");
        if (errorType == 2)
            exit(1);
    }

    void printInfo(const char *msg, ...)
    {
        fprintf(stdout, "Info: ");

        va_list args;
        va_start(args, msg);
        vfprintf(stdout, msg, args);
        va_end(args);

        fprintf(stdout, "\n");
    }
}