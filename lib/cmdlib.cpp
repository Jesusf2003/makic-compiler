#include "cmdlib.h"
#include <iostream>

extern int myargc;
extern char **myargv;

void Cmd_Error(const char *err, ...) {
    va_list args;                           // Lista de argumentos
    va_start(args, err);                    // Empieza a leer los argumentos

    std::cerr << "************ ERROR ************\n";  // Cabezal
    vfprintf(stderr, err, args);            // imprimir en stderr
    va_end(args);                           // Termina de leer los argumentos

    std::cerr << "\n";
    exit(1);                                // salir con código de error
}

void Cmd_Copy(const std::string& from, const std::string& to)
{
    try {
        std::filesystem::create_directories(std::filesystem::path(to).parent_path());
        std::filesystem::copy_file(from, to, std::filesystem::copy_options::overwrite_existing);
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error at copy file" << e.what() << "\n";
    }
}