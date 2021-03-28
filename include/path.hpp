#pragma once
#include <builtin/command.hpp>

class Path {
    char **path;

public:

    Path();
    char* resolvePath(char* cmd);
    void changePath(char** args);
};
