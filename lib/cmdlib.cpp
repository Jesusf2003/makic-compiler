#include "cmdlib.h"

void Msg_Err(const char *err, ...) {
    va_list args;                           // Lista de argumentos
    va_start(args, err);                    // Empieza a leer los argumentos

    std::cerr << "You have an error!!!\n";  // Cabezal
    vfprintf(stderr, err, args);            // imprimir en stderr
    va_end(args);                           // Termina de leer los argumentos

    std::cerr << "\n";
    exit(1);                                // salir con código de error
}
