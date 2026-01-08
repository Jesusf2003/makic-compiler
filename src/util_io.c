#include "util.h"

// File system
FILE *SafeOpenRead(const char *filename)
{
    FILE *f = NULL;
    f = fopen(filename, "rb");
    if (f == NULL)
    {
        fprintf(stderr, "Error at open file '%s': %s\n", filename, strerror(errno));
        return NULL;
    }
    return f;
}

long fileLength(FILE *f)
{
    long pos, end;
    pos = ftell(f);
    fseek(f, 0, SEEK_END);
    end = ftell(f);
    fseek(f, pos, SEEK_SET);
    return end;
}

void SafeRead(FILE *f, void *buffer, size_t count)
{
    if (fread(buffer, 1, count, f) != (size_t)count) printf("Failed read failure");
}

void CreatePath(char *path)
{
    char *ofs;
    for (ofs = path + 1; *ofs; ofs++)
    {
        if (*ofs == '/')
        {
            *ofs = 0;
        }
    }
}