#include "console.h"
#include "makic.h"

/// Starts program     
int main(int argc, char **argv)
{
    char *src;
    char filename[1024], srcdir[1024];

    if (argc < 2)
    {
        Version();
    }
    
    for (int i = 1; i < argc; i++)
    {
        if (!strcmp("-?", argv[i]) || !strcmp("-h", argv[i]) || !strcmp("-help", argv[i]))
        {
            Help();
            return 0;
        }
        if (!strcmp("-v", argv[i]) || !strcmp("-version", argv[i]))
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
        }
        else
        {
            strcpy(srcdir, "");
            return 0;
        }
    }
    return 0;
}