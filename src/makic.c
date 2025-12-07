#include "console.h"
#include "makic.h"

#define MAX_PATH_LENGTH 1024

void loadProgsFile(char *filename, void **bufferptr)
{
    printf("Loading %s file...\n", filename);
}

/// Starts program     
int main(int argc, char **argv)
{
    char *src, filename[MAX_PATH_LENGTH], srcdir[MAX_PATH_LENGTH];

    if (argc < 2)
    {
        Version();
        Help();
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
        if (!strcmp("-src", argv[i]))
        {
            if (i + 1 >= argc)
            {
                printf("No source dirname specified with -src\n");
                return 1;
            }
            strncpy(srcdir, argv[i + 1], MAX_PATH_LENGTH - 1);
            srcdir[MAX_PATH_LENGTH - 1] = '\0';
            int srcp = strlen(srcdir);
            if (srcp > 0 && srcdir[srcp - 1] != DIR_SEPARATOR_CHAR)
            {
                if (srcp < MAX_PATH_LENGTH - 1)
                {
                    srcdir[srcp] = DIR_SEPARATOR_CHAR;
                    srcdir[srcp + 1] = '\0';
                } else {
                    printf("The specified path is so much long.\n");
                }
            }
            printf("Source dir: %s\n", srcdir);
            strncpy(filename, srcdir, MAX_PATH_LENGTH);
            filename[MAX_PATH_LENGTH - 1] = '\0';
            printf("%sprogs.src", filename);
            i++;
        }
        else
        {
            strcpy(srcdir, "");
            return 0;
        }
    }
    return 0;
}
