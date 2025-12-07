#include "console.h"

int myargc;
char **myargv;

void Help()
{
    printf("makic -[OPTIONS] ...\n");
    printf("options:\n");
    printf("    -h, -help       Show help.\n");
    printf("    -v, -version    Show Version.\n");
    printf("    -src <path>     Set source dir.\n");
}

void Version()
{
    printf("MakiC 0.0.0 - (Work In Progress)\n");
}

void Error(int errtype, char *err, va_list parms)
{
    printf("Error founded:\n");
}

int cmd_parm(const char *parm)
{
    if (myargv == NULL || parm == NULL) return 0;
    for (int i = 1; i < myargc; i++)
    {
        if (myargv[i] == NULL) continue;
        if (!strcmp(parm, myargv[i])) return i;
    }
    return 0;
}