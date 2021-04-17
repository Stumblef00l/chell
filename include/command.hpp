#pragma once
#include <iostream>
#pragma once
#include <iostream>

struct Command {
    char **argv;
    char* outFile;

    Command(char **argv, char* outFile = NULL);
};