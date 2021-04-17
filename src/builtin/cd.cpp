#include <iostream>
#include <unistd.h>
#include <builtin/cd.hpp>

void ChangeDirectoryInterface::execute(Command* cmd) {
    int argc = countArgs(cmd->argv);
    if(argc == 0)
        return;
    if(argc > 2) {
        std::cerr << "wish: error\n";
        return;
    }
    if(chdir(cmd->argv[1]) != 0) {
        std::cerr << "wish: error\n";
        return;
    }
}
