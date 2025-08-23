#include "cmdlib.h"

int main(int argc, char const *argv[]) {
    Msg_Err("Error: %s, %s, %s\n", "hola", "gola", "nolan");
    return 0; // nunca llega aquí porque exit(1) cierra el programa
}
