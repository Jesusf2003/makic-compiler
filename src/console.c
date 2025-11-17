#include "console.h"

void Usage()
{
    printf("usage: makic -src <directory>\n");
}

void Help()
{
    printf("makic [OPTIONS] ... [FLAGS] ...\n");
}

void Version()
{
    printf("MakiC 0.0.1 - (Work In Progress)\n");
}

void Error(int errtype, char *err, va_list parms)
{
    printf("Error founded:\n");
}