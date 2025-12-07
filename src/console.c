#include "console.h"

void Usage()
{
    printf("usage: makic -src <directory>\n");
}

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