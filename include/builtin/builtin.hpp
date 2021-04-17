#pragma once
#include <string>
#include <unordered_map>
#include <builtin/interface.hpp>
#include <command.hpp>

class BuiltinModule {

    typedef std::unordered_map<std::string_view, BuiltinCommandInterface*> BuiltinCmdTable;
    BuiltinCmdTable cmdTable;
public:
    
    BuiltinModule();
    bool isBuiltin(Command* cmd);
    void dispatch(Command* argv);
};
