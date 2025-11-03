#include "console.h"

enum errType
{
    ERR_PARSEERRORS,
    ERR_BADEXTENSION
};

enum warnType
{
    WARN_ERROR,
    WARN_DEBUGGING
};

/*
*LogError: For abnormal program terminations
*/
void LogError(const char *error, ...)
{
    va_list argptr;
    printf("\n\x1B[31mError Found:\033[0m");
    va_start(argptr, error);
    vprintf(error, argptr);
    va_end(argptr);
    exit(1);
}

void logWarn(const char *error, ...)
{
    va_list argptr;
    printf("\n\x1B[31mWarnings Found:\033[0m");
    va_start(argptr, error);
    vprintf(error, argptr);
    va_end(argptr);
    exit(1);
}