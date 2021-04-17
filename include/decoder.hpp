#pragma once
#include <command.hpp>

class Decoder {

    static char** splitCommands(char *line);
    static Command* parseSingleCommand(char *line); 
    static char** parseWhitespaces(char *line);
    static bool checkWhitespaces(char *line);
    static void freeParsedCommands(Command** parsedCommands);
    static void freeParsedArgs(char** argv);

public:
    static Command** decode(char *line);
};
