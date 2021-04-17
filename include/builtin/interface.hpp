#pragma once
#include <command.hpp>

class BuiltinCommandInterface {

public:
    int countArgs(char **args);
    virtual void execute(Command* args) = 0;
};
