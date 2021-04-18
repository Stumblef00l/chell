#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
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
    
    int idx = 0;
    while(cmds[idx] != NULL) {
        if(builtinModule.isBuiltin(cmds[idx])) {
            builtinModule.dispatch(cmds[idx]);
        } else if(strcmp(cmds[idx]->argv[0], "path") == 0) {
            if(cmds[idx]->outFile != NULL) {
                std::cerr << "wish: incorrect use of path\n";
                errorCode = EXECUTION_ERROR::NOCMD;
            }
            path.changePath(cmds[idx]->argv);    
        } else {
            char* resolvedPath = path.resolvePath(cmds[idx]->argv[0]);
            if(resolvedPath != NULL) {
                delete cmds[idx]->argv[0];
                cmds[idx]->argv[0] = resolvedPath;
                dispatch(cmds[idx]);
            } else {
                std::cerr << "wish: no such command\n"; 
                errorCode = EXECUTION_ERROR::NOCMD;
            }
        }
        idx++;
    }
    
    delete cmds;
}

void Wish::dispatch(Command* cmd) {
    if(cmd == NULL)
        return;
    int wstatus;
    if(fork() == 0) {
        int fdout = -1;
        if(cmd->outFile != NULL) {
            fdout = open(cmd->outFile, O_CREAT | O_WRONLY, S_IRWXG | S_IRWXU);
            if(fdout == -1) {
                std::cerr << "wish: Error while executing " << (std::string_view(cmd->argv[0])) << "(ERRNO " << errno << ")\n";
                exit(1);
            }
            dup2(fdout, STDOUT_FILENO);
        }
        execv(cmd->argv[0], cmd->argv);
        std::cerr << "wish: Error while executing " << (std::string_view(cmd->argv[0])) << "(ERRNO " << errno << ")\n";
        exit(1);
    } else {
        wait(&wstatus);
        if(!WIFEXITED(wstatus)) {
            std::cerr << "wish: Error while executing process\n";
            errorCode = EXECUTION_ERROR::BADEXEC;
        }
    }
    delete cmd;
}

// ------ Helper methods for testing ------

int Wish::getMode() { return mode; }
int Wish::getError() { return errorCode; }
const char* Wish::getBatchFile() { return batchFile; }
int Wish::getProcessedCount() { return processedCount; }
