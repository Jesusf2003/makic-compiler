#ifndef CMDLIB_H
#define CMDLIB_H

#include <cstdlib>
#include <cstdarg>
#include <string>
#include <cctype>
#include <optional>
#include <filesystem>

void Cmd_Error(const char *err, ...); // prints a error message

void Cmd_Copy(const std::string &from, const std::string &to);

#endif