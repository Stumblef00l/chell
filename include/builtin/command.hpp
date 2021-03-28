#pragma once

class BuiltinCommandInterface {

public:
    int countArgs(char **args);
    virtual void execute(char **args) = 0;
};
