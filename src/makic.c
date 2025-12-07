#include "console.h"
#include "makic.h"

#define MAX_PATH_LENGTH 1024

int loadProgsFile(char *filename, void **bufferptr)
{
    FILE *f;
    size_t length;
    void *buffer;
    printf("Trying to open %s file...\n", filename);
    f = openRead(filename);
    length = (size_t)fileLength(f);
    buffer = malloc(length + 1);
    if (!buffer)
        printf("%s failed for %lu bytes.\n", __thisfunc__, (unsigned long long)length);
    ((char *)buffer)[length] = 0;
    read(f, buffer, length);
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

    myargc = argc;
    myargv = argv;

    srcdir[0] = '\0';
    filename[0] = '\0';

    if (argc < 2)
    {
        Version();
        Help();
        return 0;
    }

    for (int i = 1; i < argc; i++)
    {
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
        if (cmd_parm("-src"))
        {
            if (i + 1 >= argc)
            {
                printf("No source dirname specified with -src");
            }

            strncpy(srcdir, argv[i + 1], MAX_PATH_LENGTH - 1);
            srcdir[MAX_PATH_LENGTH - 1] = '\0';

            int srcp = strlen(srcdir);
            if (srcp > 0 && !IS_DIR_SEPARATOR(srcdir[srcp - 1]))
            {
                if (srcp < MAX_PATH_LENGTH - 1)
                {
                    srcdir[srcp] = DIR_SEPARATOR_CHAR;
                    srcdir[srcp + 1] = '\0';
                }
                else
                {
                    printf("Advertencia: La ruta de origen es demasiado larga y se truncó antes de añadir el separador.\n");
                }
            }

            printf("Source directory: %s\n", srcdir);
            i++;
        }
    }
    strncpy(filename, srcdir, MAX_PATH_LENGTH - 1);
    filename[MAX_PATH_LENGTH - 1] = '\0';

    nameptr = strchr(filename, '\0');

    const char *default_name = "progs.src";
    size_t remaining_len = MAX_PATH_LENGTH - (nameptr - filename);

    if (remaining_len > 0) 
    {
        strncpy(nameptr, default_name, remaining_len - 1);
        nameptr[remaining_len - 1] = '\0'; // Asegurar terminación
    } else {
        printf("Error interno: La ruta de origen es demasiado larga para adjuntar 'progs.src'.");
    }
    loadProgsFile(filename, &src);
    return 0;
}
