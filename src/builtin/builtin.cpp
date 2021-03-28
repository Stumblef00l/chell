#include <builtin/builtin.hpp>
#include <builtin/exit.hpp>
#include <builtin/cd.hpp>

// Define the command interfaces here
namespace BuiltinInterfaces {
    ExitInterface exitInterface;
    ChangeDirectoryInterface changeDirectoryInterface;
}

BuiltinModule::BuiltinModule() {
    cmdTable["exit"] = &BuiltinInterfaces::exitInterface;    
    cmdTable["cd"] = &BuiltinInterfaces::changeDirectoryInterface;
}

bool BuiltinModule::isBuiltin(char *cmd) {
    return (cmdTable.find(std::string_view(cmd)) != BuiltinModule::cmdTable.end());
}
    
void BuiltinModule::dispatch(char **argv) {
    cmdTable[std::string_view(argv[0])]->execute(argv);
}