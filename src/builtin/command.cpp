#include <cstddef>
#include <builtin/command.hpp>

int BuiltinCommandInterface::countArgs(char **argv) {
    int argc = 0;
    while(argv[argc] != NULL)
        argc++;
    return argc;
}
