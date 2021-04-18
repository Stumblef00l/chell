#include <command.hpp>

Command::Command(char **argv, char* outFile): argv(argv), outFile(outFile) {}

Command::~Command() { 
    if(argv != NULL) {
        int idx = 0;
        while(argv[idx] != NULL) {
            delete[] argv[idx];
            idx++;
        }
        delete[] argv;
    }
    if(outFile != NULL)
        delete[] outFile;
}
