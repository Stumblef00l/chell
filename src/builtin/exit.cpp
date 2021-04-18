#include <iostream>
#include <builtin/exit.hpp>

extern bool SUPPRESS_EXIT_SYSCALL;

void ExitInterface::execute(Command* cmd) {
    int argc = countArgs(cmd->argv);
    if(argc == 0)
        return;
    if(argc > 1) {
        std::cerr << "wish: error\n";
        return;
    }
    if(!SUPPRESS_EXIT_SYSCALL) {
        delete cmd;
        exit(0);
    }
}
