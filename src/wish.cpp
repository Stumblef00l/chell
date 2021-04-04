#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <wish.hpp>

Wish::Wish(int mode, char *batchFile)
    : mode(mode), 
      batchFile(batchFile),
      buffLen(0),
      errorCode(EXECUTION_ERROR::NOERR),
      processedCount(0) {}

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
    while(true) {
        std::cout << "wish> ";
        errorCode = EXECUTION_ERROR::NOERR;
        processInputStream(stdin);
    }
}

void Wish::runBatch() {
    FILE *inputStream = fopen(batchFile, "r");
    if(inputStream == NULL) {
        std::cerr << "wish: No such command file\n";
        errorCode = EXECUTION_ERROR::NOFILE;
        exit(1);
    }
    while(errorCode == EXECUTION_ERROR::NOERR) {
        processedCount++;
        processInputStream(inputStream);
    }
    fclose(inputStream);
}

void Wish::processInputStream(FILE* inputStream) {
    char* buff = NULL;
    int lineLength;
    if((lineLength = getline(&buff, &buffLen, inputStream)) == -1) { 
        std::cerr << "An error has occurred\n";
        errorCode = EXECUTION_ERROR::ERRGETL;
        exit(1);
    }
    char **argv = decoder.decode(buff);
    if(argv == NULL) {
        delete[] argv;
        delete[] buff;
        return;
    }

    if(builtinModule.isBuiltin(argv[0])) {
        builtinModule.dispatch(argv);
    } else if(strcmp(argv[0], "path") == 0) {
        path.changePath(argv);    
    } else {
        argv[0] = path.resolvePath(argv[0]);
        if(argv[0] != NULL) {
            dispatch(argv);
        } else {
            std::cerr << "wish: no such command\n"; 
            errorCode = EXECUTION_ERROR::NOCMD;
        }
    }
    delete[] argv;
    delete[] buff;
}

void Wish::dispatch(char **argv) {
    if(argv == NULL)
        return;
    int wstatus;
    if(fork() == 0) {
        execv(argv[0], argv);
        std::cerr << "wish: An error has occured (ERRNO " << errno << ")\n";
    } else {
        wait(&wstatus);
        if(!WIFEXITED(wstatus)) {
            std::cerr << "wish: Error while executing process\n";
            errorCode = EXECUTION_ERROR::BADEXEC;
        }
    }
}

// ------ Helper methods for testing ------

int Wish::getMode() { return mode; }
int Wish::getError() { return errorCode; }
char* Wish::getBatchFile() { return batchFile; }
int Wish::getProcessedCount() { return processedCount; }
