#include <builtin/builtin.hpp>
#include <builtin/exit.hpp>
#include <builtin/cd.hpp>
#include <unistd.h>

// Define the command interfaces here
namespace BuiltinInterfaces {
    ExitInterface exitInterface;
    ChangeDirectoryInterface changeDirectoryInterface;
}

BuiltinModule::BuiltinModule() {
    cmdTable["exit"] = &BuiltinInterfaces::exitInterface;    
    cmdTable["cd"] = &BuiltinInterfaces::changeDirectoryInterface;
}

bool BuiltinModule::isBuiltin(Command* cmd) {
    if(cmd->outFile != NULL)
        return false;
    return (cmdTable.find(std::string_view(cmd->argv[0])) != BuiltinModule::cmdTable.end());
}
    
void BuiltinModule::dispatch(Command* cmd) {
    cmdTable[std::string_view(cmd->argv[0])]->execute(cmd);
}
