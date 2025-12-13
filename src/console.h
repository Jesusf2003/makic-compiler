#include <stdlib.h>
#include "util.h"

typedef enum {
    LVL_MSG, LVL_ERROR, LVL_WARNING
} cmdlvl_e;

typedef enum {
    ERR_SYNTAX
} cmderror_e;

typedef enum {
    WARN_UNEXPECTED
} cmdwarn_e;

extern int myargc;
extern char **myargv;

/* GENERIC MESSAGES */
void Help();
void Version();

/* CONSOLE MESSAGES */
void Message(int errType, char *msg, va_list parms);
void Error(int errType, char *err, va_list parms);
void Warning(int warnType, char *msg, va_list parms);

// cmd
int cmd_parm(const char *parm);