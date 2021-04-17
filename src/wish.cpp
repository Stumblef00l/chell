#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <wish.hpp>

extern bool SUPPRESS_EXIT_SYSCALL;

Wish::Wish(int mode, const char *batchFile)
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
        processedCount++;
    }
}

void Wish::runBatch() {
    FILE *inputStream = fopen(batchFile, "r");
    if(inputStream == NULL) {
        std::cerr << "wish: No such command file\n";
        errorCode = EXECUTION_ERROR::NOFILE;
        if(SUPPRESS_EXIT_SYSCALL)
            return;
        exit(1);
    }
    while(true) {
        processInputStream(inputStream);
        if(errorCode == EXECUTION_ERROR::NOERR)
            processedCount++;
        else
            break;
    }
    fclose(inputStream);
}

void Wish::processInputStream(FILE* inputStream) {
    char* buff = NULL;
    int lineLength;
    if((lineLength = getline(&buff, &buffLen, inputStream)) == -1) {
        free(buff);
        errorCode = EXECUTION_ERROR::EOEXEC;
        if(SUPPRESS_EXIT_SYSCALL)
            return;
        exit(1);
    }
    
    Command** cmds = Decoder::decode(buff);
    free(buff);
    if(cmds == NULL)
        return;
    
    if(builtinModule.isBuiltin(cmds[0])) {
        builtinModule.dispatch(argv);
    } else if(strcmp(argv[0], "path") == 0) {
        path.changePath(argv);    
    } else {
        char* resolvedPath = path.resolvePath(argv[0]);
        if(resolvedPath != NULL) {
            free(argv[0]);
            argv[0] = resolvedPath;
            dispatch(argv);
        } else {
            std::cerr << "wish: no such command\n"; 
            errorCode = EXECUTION_ERROR::NOCMD;
        }
    }
    
    // Memory cleanup
    int argIdx = 0;
    while(argv[argIdx] != NULL) {
        free(argv[argIdx]);
        argIdx++;
    }
    free(argv);
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
const char* Wish::getBatchFile() { return batchFile; }
int Wish::getProcessedCount() { return processedCount; }
