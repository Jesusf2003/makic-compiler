#include <stdio.h>
#include <iostream>
#include <stdarg.h>
#include <stdlib.h>

#define ANSI_COLOR_RED      "\x1b[31m"
#define ANSI_COLOR_BRIGHT_RED "\x1b[91m" // Rojo brillante
#define ANSI_COLOR_GREEN    "\x1b[32m"
#define ANSI_COLOR_YELLOW   "\x1b[33m"
#define ANSI_COLOR_RESET    "\x1b[0m"

// syntax errors/warns

// compiler errors/warn

// parm errors/warn

// resume errors/warn if is added -Wall

void LogError(const char *error, ...);
void logWarn(const char *error, ...);