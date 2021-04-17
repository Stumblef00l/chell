#pragma once
#include <cstddef>
#include <builtin/interface.hpp>

class ChangeDirectoryInterface : public BuiltinCommandInterface {

public:
    void execute(Command* cmd);
};
