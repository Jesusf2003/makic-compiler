#include <cstdio>
#include <cstdlib>
#include <cstdarg>
#include <cstring>

#define PATH_SEPARATOR '/'

namespace cmd
{
    extern int cargc;
    extern char **cargv;

    // sets data about file(path or extensions)
    void defaultExt(char *path, char *ext);
    void defaultPath(char *path, char *basepath);

    void stripFilename(char *path);
    void stripExt(char *path);

    void extractFilePath(char *path, char *dest);
    void extractFileBase(char *path, char *dest);
    void extractFileExt(char *path, char *dest);

    int checkNextCmd(const char *check, int last);
    int checkCmd(const char *cmd);

    void printError(int errType, const char *err, ...);
    void printInfo(const char *msg, ...);

    int getFileLength(FILE *f);
    int getFileTime(char *path);
}