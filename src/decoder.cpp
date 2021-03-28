#include <decoder.hpp>
#include <string.h>

char** Decoder::decode(char *line) {
    int argc = 1;
    char prev = ' ';
    for(int i = 0; line[i] != '\0'; i++) {
        if(line[i] != ' ' && line[i] != '\n' && prev == ' ')
            argc++;
        prev = line[i];
    }
    char **argv = new char*[sizeof(char*) * argc];
    int argIdx = 0;
    while(true) {
        argv[argIdx] = strsep(&line, " \n");
        if(argv[argIdx] == NULL)
            break;
        else if(strlen(argv[argIdx]) > 0)
            argIdx++;
    }
    return argv;
}