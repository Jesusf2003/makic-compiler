#ifndef CMDLIB_H
#define CMDLIB_H

#include <iostream>
#include <cstdlib>
#include <cstdarg>
#include <string>

//
// Validations
//
void Msg_Info(const char* info);
void Msg_Err(const char* err, ...); // prints a error message

#endif