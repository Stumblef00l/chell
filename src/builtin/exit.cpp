#include <iostream>
#include <builtin/exit.hpp>

extern bool SUPPRESS_EXIT_SYSCALL;

void ExitInterface::execute(char **argv) {
    int argc = countArgs(argv);
    if(argc == 0)
        return;
    if(argc > 1) {
        std::cerr << "wish: error\n";
        return;
    }
    if(!SUPPRESS_EXIT_SYSCALL)
        exit(0);
}
