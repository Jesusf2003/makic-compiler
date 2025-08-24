#ifndef CMDLIB_H
#define CMDLIB_H

#include <cctype>
#include <iostream>
#include <filesystem>
#ifdef WIN32
#include <direct.h>
#else
#include <unistd.h>
#endif

namespace cmdlib
{
    extern int cargc;
    extern char **cargv;
    int checkParm(char *check);
    void getWorkdir(char *out);
    void makeDir(char *path);
    void setDirFromPath(char *path);

    // paths
    char *expandPath(char *path);
    void defaultExt(char *path, char *ext, size_t bufsize);
    void defaultPath(char *path, size_t pathSize, char *basepath);

    // files
    FILE *safeOpenWrite(char *filename);
    FILE *safeOpenRead(char *filename);

    void safeRead(FILE *f, void* buffer, int count);
    void safeWrite(FILE *f, void *buffer, int count);

    int loadFile(char *filename, void **bufferptr);
    void saveFile(char *filename, void *buffer, int count);

    // utils
    void stripFilename(char *path);
    void stripExt(char *path);

    void extractFilePath(const char *path, char *dest, size_t destSize);
    void extractFileBase(const char *path, char *dest, size_t destSize);
    void extractFileExt(const char *path, char *dest, size_t destSize);

    int strncasecmp(const char *s1, const char *s2, int n);
    int strcasecmp(char *s1, char *s2);
    char *strToUpper(char *start);
    char *strtoLower(char *start);

    // files
    void createPath(const char *path);
    void copyFile(char *from, char *to);
}

#endif