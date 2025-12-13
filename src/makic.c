#include "console.h"
#include "makic.h"

#define MAX_PATH_LENGTH 1024

int loadProgsFile(char *filename, void **bufferptr)
{
    FILE *f; size_t length; void *buffer;

    printf("Reading progs.src file...\n");
    f = SafeOpenRead(filename);
    length = (size_t) fileLength(f);
    buffer = malloc(length + 1);
    if (!buffer) fprintf(stderr, "%s failed for %lu bytes.\n", __thisfunc__, (unsigned long)length);
    ((char *)buffer)[length] = 0;
    SafeRead(f, buffer, length);
    printf("%s\n", (char*)buffer);
    fclose(f);
    *bufferptr = buffer;
    return length;
}

/// Starts program
int main(int argc, char **argv)
{
    void *src = NULL; // saves source dir path
    char *nameptr;
    char filename[MAX_PATH_LENGTH]; // saves full path of file
    char srcdir[MAX_PATH_LENGTH];
    const char *default_name = "progs.src";

    myargc = argc;
    myargv = argv;

    srcdir[0] = '\0';
    filename[0] = '\0';

    if (argc < 2)
    {
        Version();
        printf("Usage: makic -src <path>\n");
        Help();
        return 0;
    }

    if (cmd_parm("-?") || cmd_parm("-h") || cmd_parm("-help"))
    {
        Help();
        return 0;
    }
    if (cmd_parm("-v") || cmd_parm("-version"))
    {
        Version();
        return 0;
    }
    int parm = cmd_parm("-src");
    if (parm != 0)
    {
        if (parm + 1 >= argc)
        {
            printf("No source dirname specified with -src.\n");
        }
        strncpy(srcdir, argv[parm + 1], MAX_PATH_LENGTH - 1);
        srcdir[MAX_PATH_LENGTH - 1] = '\0';
        int srcp = strlen(srcdir);
        if (srcp > 0 && !IS_DIR_SEPARATOR(srcdir[srcp - 1]))
        {
            if (srcp < MAX_PATH_LENGTH - 1)
            {
                srcdir[srcp] = DIR_SEPARATOR_CHAR;
                srcdir[srcp + 1] = '\0';
            }
            strncpy(filename, srcdir, MAX_PATH_LENGTH - 1);
            filename[MAX_PATH_LENGTH - 1] = '\0';
            nameptr = strchr(filename, '\0');
        }
        printf("Source directory: %s\n", srcdir);
    }
    snprintf(filename, MAX_PATH_LENGTH, "%s%s", srcdir, default_name);
    loadProgsFile(filename, &src);
    free(src);
    return 0;
}
