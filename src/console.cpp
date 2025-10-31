#include "console.h"

enum errType : int
{
    ERR_PARSEERRORS,
    ERR_BADEXTENSION
};

enum warnType : int
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
    std::cerr << "\n\x1B[31mError Found:\033[0m" << std::endl;
    va_start(argptr, error);
    vprintf(error, argptr);
    va_end(argptr);
    exit(1);
}

void logWarn(const char *error, ...)
{
    va_list argptr;
    std::cerr << "\n\x1B[31mWarnings Found:\033[0m" << std::endl;
    va_start(argptr, error);
    vprintf(error, argptr);
    va_end(argptr);
    exit(1);
}