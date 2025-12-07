#include "util.h"

// File system
FILE *openRead(const char *filename)
{
    FILE *f = NULL;
    if (filename == NULL)
    {
        fprintf(stderr, "Error: Filename is NULL\n");
        return NULL;
    }
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

void read(FILE *f, void *buffer, size_t count)
{
    if (f == NULL) printf("SafeRead llamado con FILE* NULL.");
    if (buffer == NULL && count > 0) printf("SafeRead llamado con buffer NULL.");
    size_t bytes_read = fread(buffer, 1, count, f);
    if (bytes_read != count)
    {
        if (ferror(f)) {
            printf("Fallo de lectura I/O: error al leer %zu bytes. Causa: %s", count, strerror(errno));
        } else if(feof(f))
        {
            printf("Fallo de lectura: archivo terminó inesperadamente (EOF). Solicitado: %zu, Leído: %zu", count, bytes_read);
        } else 
        {
            printf("Fallo de lectura desconocido.");
        }
    }
}