#include "cmdlib.h"

int main(int argc, char **argv)
{
    cmdlib::cargc = argc;
    cmdlib::cargv = argv;
    printf("Args: %d\n", cmdlib::cargc);
    for (int i = 0; i < cmdlib::cargc; i++)
    {
        printf("  %s\n", cmdlib::cargv[i]);
    }
    return 0;
}