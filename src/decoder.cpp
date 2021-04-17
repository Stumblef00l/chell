#include <decoder.hpp>
#include <string.h>
#include <stdlib.h>


Command** Decoder::decode(char *line) {
    if(line == NULL)
        return NULL;

    // Split parallel commands
    char **rawCmds = splitCommands(line);
    if(rawCmds == NULL)
        return NULL;

    // Count the number of parallel commands
    int cmdCt = 0;
    while(rawCmds[cmdCt] != NULL)
        cmdCt++;
    if(cmdCt == 0) {
        delete rawCmds;
        return NULL;
    }

    // Parse the commands
    Command** parsedCommands = new Command*[cmdCt + 1];
    int cmdIdx = 0;
    while(cmdIdx < cmdCt) {
        parsedCommands[cmdIdx] = parseSingleCommand(rawCmds[cmdIdx]);
        if(parsedCommands[cmdIdx] == NULL) {
            freeParsedCommands(parsedCommands);
            delete rawCmds;
            return NULL;
        }
        cmdIdx++;
    }
    parsedCommands[cmdIdx] = NULL;
    return parsedCommands;
}

char** Decoder::splitCommands(char *line) {
    int cmdCt = 0;
    for(int i = 0; line[i] != '\0'; i++) {
        if(line[i] == '&' || line[i] == '\n')
            cmdCt++;
    }
    if(cmdCt == 0)
        return NULL;

    char** splitCmds = new char*[cmdCt + 1];
    int cmdIdx = 0;
    while(cmdIdx < cmdCt) {
        char *newCmd = strsep(&line, "&\n");
        splitCmds[cmdIdx] = newCmd;
        cmdIdx++;
    }
    return splitCmds;
}

Command* Decoder::parseSingleCommand(char *line) {
    
    // Check for duplicate redirection operator
    bool foundRedirection = false;
    for(int i = 0; line[i] != '\0'; i++) {
        if(line[i] == '>') {
            if(foundRedirection)
                return NULL;
            foundRedirection = true;
        }
    }

    Command *parsedCmd = NULL;
    if(foundRedirection) {
        char *cmd = strsep(&line, ">");
        char *outFile = strsep(&line, ">");
        char **argv = parseWhitespaces(cmd);
        if(argv == NULL)
            return NULL;
        if(checkWhitespaces(outFile) || strlen(outFile) == 0) {
            freeParsedArgs(argv);
            delete argv;
            return NULL;
        }
        char *outFileCopy = new char[strlen(outFile) + 1];
        strcpy(outFileCopy, outFile);
        parsedCmd = new Command(argv, outFileCopy);
    } else {
        char **argv = parseWhitespaces(line);
        if(argv == NULL)
            return NULL;
        parsedCmd = new Command(argv);
    }
    return parsedCmd;
}

char** Decoder::parseWhitespaces(char *line) {
    int argc = 0;
    char prev = ' ';
    for(int i = 0; line[i] != '\0'; i++) {
        if(line[i] != ' ' && line[i] != '\n' && prev == ' ')
            argc++;
        prev = line[i];
    }
    char **argv = NULL;
    if(argc == 0)
        return argv;
    argv = new char*[argc + 1];

    int argIdx = 0;
    while(argIdx < argc) {
        char* newArg = strsep(&line, " \n");
        if(newArg == NULL)
            continue;
        else if(strlen(newArg) > 0) {
            argv[argIdx] = new char[strlen(newArg) + 1];
            strcpy(argv[argIdx], newArg);
            argIdx++;
        }
    }
    argv[argIdx] = NULL;
    return argv;
}

bool Decoder::checkWhitespaces(char *line) {
    for(int i = 0; line[i] != '\0'; i++)
        if(line[i] == ' ')
            return true;
    return false;
}

void Decoder::freeParsedCommands(Command** parsedCommands) {
    if(parsedCommands == NULL)
        return;
    int idx = 0;
    while(parsedCommands[idx] != NULL) {
        delete parsedCommands[idx];
        idx++;
    }
}

void Decoder::freeParsedArgs(char** argv) {
    if(argv == NULL)
        return;
    int idx = 0;
    while(argv[idx] != NULL) {
        delete argv[idx];
        idx++;
    }
}
