#pragma once
#include <iostream>

struct Command {
    char **argv;
    FILE* outputStream;

    Command(char **argv, FILE* outputStream = stdout);
};