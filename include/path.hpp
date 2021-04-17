#pragma once
#include <builtin/interface.hpp>

class Path {
    char **path;

public:

    Path();
    char* resolvePath(char* cmd);
    void changePath(char** args);
};
