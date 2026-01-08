#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>

#define __thisfunc__ __func__

#define DIR_SEPARATOR_CHAR '\\'
#define DIR_SEPARATOR_STR  "\\"

#define IS_DIR_SEPARATOR(c) ((c) == '/' || (c) == '\\')

// file system
FILE *SafeOpenRead(const char *filename);
void SafeRead(FILE *f, void *buffer, size_t count);
long fileLength(FILE *f);
void CreatePath(char *path);