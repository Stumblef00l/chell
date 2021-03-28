#pragma once
#include <cstddef>
#include <decoder.hpp>
#include <builtin/builtin.hpp>
#include <path.hpp>

enum EXECUTION_MODES {
    INTERACTIVE = 0,
    BATCH = 1
};

class Wish {
    
    int mode;
    char *batchFile;
    size_t buffLen;

    Decoder decoder;
    BuiltinModule builtinModule;
    Path path;

    void runInteractive();
    void runBatch();
    void dispatch(char** command);

public:
    
    Wish(int mode = EXECUTION_MODES::INTERACTIVE, char *batchFile = NULL);
    void run();
};
