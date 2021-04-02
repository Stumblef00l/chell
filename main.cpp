#include <iostream>
#include <wish.hpp>
#include <config.h>

int main(int argc, char *argv[]) {
    if(argc > 2) {
        std::cerr << "wish: Usage - ./wish [CMD_FILE]";
        exit(1);
    }
    if(argc == 1)
        Wish(EXECUTION_MODES::INTERACTIVE).run();
    else
        Wish(EXECUTION_MODES::BATCH, argv[1]).run();
    return 0;
}

