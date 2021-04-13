#include <decoder.hpp>
#include <string.h>
#include <stdlib.h>

char** Decoder::decode(char *line) {
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
    argv = (char**)malloc(sizeof(char*) * (argc + 1));
    int argIdx = 0;
    while(true) {
        char* newArg = strsep(&line, " \n");
        if(newArg == NULL) {
            argv[argIdx] = newArg;
            break;
        }
        else if(strlen(newArg) > 0) {
            argv[argIdx] = (char*)malloc(sizeof(char) * (strlen(newArg) + 1));
            strcpy(argv[argIdx], newArg);           
            argIdx++;
        }
    }
    return argv;
}
