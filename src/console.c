#include "console.h"
#include <stdarg.h>
#include <stdint.h>

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

static bool setFlag_all(const char *name, bool on, uint32_t *flags, char *list, size_t listSize)
{}

bool setFlag(const char *flag, bool opt)
{}
bool setWarn(const char *flag, bool opt)
{}
bool setWerror(const char *flag, bool opt)
{}
bool setOptim(const char *flag, bool opt)
{}

void Message(int errType, char *msg, va_list parms)
{
}

void Error(int errtype, char *err, va_list parms)
{
}

void Warning(int errType, char *err, va_list parms)
{
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