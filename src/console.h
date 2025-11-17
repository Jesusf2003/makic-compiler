#include <string.h>
#include <stdio.h>

typedef enum {
    CMD_RED,
    CMD_GREEN,
    CMD_YELLOW
} cmdcolors_e;

/* GENERIC MESSAGES */
/**
 * @name Usage
 * Shows usage info
 */
void Usage();

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
void Error(int errType, char *err, va_list parms);