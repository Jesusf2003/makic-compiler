#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "common.h"

#define PATH_SEPARATOR '/'

namespace cmd
{
    extern int cargc;
    extern char **cargv;

    // sets data about file(path or extensions)
    void defaultExt(char *path, char *ext);
    void defaultPath(char *path, char *basepath);

    int checkNextCmd(const char *check, int last);
    int checkCmd(const char *cmd);
}