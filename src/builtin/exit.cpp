#include <iostream>
#include <builtin/exit.hpp>

void ExitInterface::execute(char **argv) {
    int argc = countArgs(argv);
    if(argc == 0)
        return;
    if(argc > 1) {
        std::cerr << "wish: error\n";
        return;
    }
    exit(0);
}
