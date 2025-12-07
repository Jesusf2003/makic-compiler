#include <stdlib.h>
#include "util.h"

typedef enum {
    CMD_RED,
    CMD_GREEN,
    CMD_YELLOW,
    CMD_CYAN
} cmdcolors_e;

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

/**
 * @name Help
 * Shows help info
 */
void Help();

/**
 * @name Version
 * Shows version info
 */
void Version();

/* CONSOLE MESSAGES */
/**
 * @name Error
 * Shows a error message
 * @param errType Type of error
 * @param err Message
 * @param parms Other params to print message with value
 */
void Message(int errType, char *msg, va_list parms);
void Error(int errType, char *err, va_list parms);
void Warning(int warnType, char *msg, va_list parms);

// cmd
/**
 * Search parms in command line
 * @param argc arg counter
 * @param argv arg var list
 * @param parm parm to search (e.j.: -src)
 */
int cmd_parm(const char *parm);