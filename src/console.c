#include "makic.h"
#include <stdbool.h>

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