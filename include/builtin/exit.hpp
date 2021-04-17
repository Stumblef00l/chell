#pragma once
#include <cstddef>
#include <builtin/interface.hpp>

class ExitInterface : public BuiltinCommandInterface {

public:
    void execute(Command* argv);
};
