#pragma once
#include <cstddef>
#include <builtin/command.hpp>

class ExitInterface : public BuiltinCommandInterface {

public:
    void execute(char **argv);
};