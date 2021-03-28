#pragma once
#include <string>
#include <unordered_map>
#include <builtin/command.hpp>

class BuiltinModule {

    typedef std::unordered_map<std::string, BuiltinCommandInterface*> BuiltinCmdTable;
    BuiltinCmdTable cmdTable;
public:

    BuiltinModule();
    bool isBuiltin(char *cmd);
    void dispatch(char **argv);
};
