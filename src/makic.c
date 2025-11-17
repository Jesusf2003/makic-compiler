#include "console.h"
#include "makic.h"

/// Starts program     
int main(int argc, char **argv)
{
    char *src;
    char filename[1024], srcdir[1024];
    
    for (int i = 1; i < argc; i++)
    {
        if (!strcmp("-h", argv[i]))
        {
            Help();
            return 0;
        }
        if (!strcmp("-v", argv[i]))
        {
            Version();
            return 0;
        }
        int srcp = !strcmp("-src", argv[i]);
        if (srcp && srcp < argc - 1)
        {
            strcpy(srcdir, argv[srcp + 1]);
            strcat(srcdir, "/");
            printf("Source directory: %s", srcdir);
            sprintf(filename, "%sprogs.src", srcdir);
        }
        else
        {
            strcpy(srcdir, "");
            return 0;
        }
    }
    return 0;
}