#pragma once
#include <cstddef>
#include <decoder.hpp>
#include <builtin/builtin.hpp>
#include <path.hpp>

enum EXECUTION_MODES {
    INTERACTIVE = 0,
    BATCH = 1
};

enum EXECUTION_ERROR {
    NOERR = 0,
    ERRGETL = 1,
    NOFILE = 2,
    OTHER = 2000
};

class Wish {
    
    int mode;
    char *batchFile;
    size_t buffLen;
    int errorCode;

    Decoder decoder;
    BuiltinModule builtinModule;
    Path path;

    void runInteractive();
    void runBatch();
    void processInputStream(FILE* inputStream);
    void dispatch(char** command);

public:
    
    Wish(int mode = EXECUTION_MODES::INTERACTIVE, char *batchFile = NULL);
    void run();
    
    // ----- Helper methods, useful for testing -----
    int getMode();
    int getError();
    char* getBatchFile();
};
