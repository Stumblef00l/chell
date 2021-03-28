#pragma once
#include <cstddef>
#include <builtin/command.hpp>

class ChangeDirectoryInterface : public BuiltinCommandInterface {

public:
    void execute(char **argv);
};
