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
    NOCMD = 3,
    BADEXEC = 4,
    EOEXEC = 5,
    OTHER = 2000
};

class Wish {
    
    int mode;
    const char *batchFile;
    size_t buffLen;
    int errorCode;
    int processedCount;

    BuiltinModule builtinModule;
    Path path;

    void runInteractive();
    void runBatch();
    void processInputStream(FILE* inputStream);
    void dispatch(char** command);

public:
    
    Wish(int mode = EXECUTION_MODES::INTERACTIVE, const char *batchFile = NULL);
    void run();
    
    // ----- Helper methods, useful for testing -----
    int getMode();
    int getError();
    const char* getBatchFile();
    int getProcessedCount();
};
