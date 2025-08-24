#include "cmdlib.h"
#include <iostream>

int main(int argc, char const *argv[]) {
    auto buf = cmdlib::loadFile("Mod.fgd");
    std::cout << buf.data << std::endl;
    std::cout << buf.length << std::endl;
    return 0; // nunca llega aquí porque exit(1) cierra el programa
}
