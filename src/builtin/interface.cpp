#include <cstddef>
#include <builtin/interface.hpp>

int BuiltinCommandInterface::countArgs(char **argv) {
    int argc = 0;
    while(argv[argc] != NULL)
        argc++;
    return argc;
}
