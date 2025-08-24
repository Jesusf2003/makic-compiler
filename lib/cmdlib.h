#ifndef CMDLIB_H
#define CMDLIB_H

#include <cctype>
#include <iostream>
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
    char* expandPath(char *path);

    // utils
    int strncasecmp(const char *s1, const char *s2, int n);
    int strcasecmp(char *s1, char *s2);
    char *strToUpper(char *start);
    char *strtoLower(char *start);
}

#endif