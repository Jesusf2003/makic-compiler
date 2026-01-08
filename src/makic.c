#include "console.h"
#include "makic.h"

#define MAX_PATH_LENGTH 1024

size_t loadProgsFile(char *filename, void **bufferptr)
{
    FILE *f;
    size_t length;
    void *buffer;
    f = SafeOpenRead(filename);
    length = (size_t)fileLength(f);
    buffer = malloc(length + 1);
    if (!buffer) {
        fprintf(stderr, "Error: No se pudo asignar memoria para %s\n", filename);
        fclose(f);
        return 1;
    }
    ((char *)buffer)[length] = 0;
    SafeRead(f, buffer, length);
    fclose(f);
    *bufferptr = buffer;
    return (int)length;
}

/// Starts program
int main(int argc, char **argv)
{
    void *src = NULL; // saves source dir path
    char filename[MAX_PATH_LENGTH] = {0}; // saves full path of file
    char srcdir[MAX_PATH_LENGTH] = {0};
    const char *def_prog_name = "progs.src";

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
    // - makic -src <path>
    int parm = cmd_parm("-src");
    if (parm != 0)
    {
        if (parm + 1 < argc)
        {
            snprintf(srcdir, sizeof(srcdir), "%s", argv[parm + 1]);
            size_t len = strlen(srcdir);
            if (len > 0 && !IS_DIR_SEPARATOR(srcdir[len - 1]))
            {
                if (len < MAX_PATH_LENGTH - 1)
                {
                    srcdir[len] = DIR_SEPARATOR_CHAR;
                    srcdir[len + 1] = '\0';
                }
            }
            printf("Source directory: %s\n", srcdir);
        }
        else
        {
            fprintf(stderr, "Error: No source directory specified with -src.\n");
            return 1;
        }
    }
    int filep = cmd_parm("-filesrc");
    if (filep != 0 && (filep + 1) < argc)
    {
        def_prog_name = argv[filep + 1];
        printf("Custom source file: %s\n", def_prog_name);
    }
    snprintf(filename, sizeof(filename), "%s%s", srcdir, def_prog_name);
    printf("Loading %s\n", filename);
    loadProgsFile(filename, &src);
    if (src) free(src);
    return 0;
}
