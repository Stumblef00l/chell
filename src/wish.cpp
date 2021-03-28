#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <wish.hpp>

Wish::Wish(int mode, char *batchFile)
    : mode(mode), batchFile(batchFile) {}

void Wish::run() {
    switch(mode) {
        case EXECUTION_MODES::INTERACTIVE:
            runInteractive();
            break;
        case EXECUTION_MODES::BATCH:
            runBatch();
            break;
        default:
            runInteractive();
            break;
    }
}

void Wish::runInteractive() {
    char *buff = NULL;
    size_t buffLen = 0;
    while(true) {
        std::cout << "wish> ";

        buff = NULL; buffLen = 0;
        int lineLength;
        if((lineLength = getline(&buff, &buffLen, stdin)) == -1) { 
            std::cerr << "An error has occurred\n";
            continue;
        } 
        char **argv = decoder.decode(buff);
        if(argv == NULL)
            continue;
        else if(builtinModule.isBuiltin(argv[0]))
            builtinModule.dispatch(argv);
        else
            dispatch(argv);
        delete argv;
        delete buff;
    }
}

void Wish::runBatch() {
    return;
}

void Wish::dispatch(char **argv) {
    if(argv == NULL)
        return;
    int wstatus;
    if(fork() == 0) {
        execvp(argv[0], argv);
        std::cerr << "An error has occured (ERRNO " << errno << ")\n";
    } else
        wait(&wstatus);
}
