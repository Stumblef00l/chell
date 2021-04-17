#include <command.hpp>

Command::Command(char **argv, FILE *outputStream = stdout): argv(argv), outputStream(outputStream) {}