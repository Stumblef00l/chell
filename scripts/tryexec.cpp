#include <iostream>
#include <cassert>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

using namespace std;

int main(int argc, char *argv[]) {
    assert(argv[argc] == NULL);
    if(fork() == 0) {
        int ret = execvp(argv[1], argv + 1);
        if(ret == -1) {
            cerr << "Error";
            exit(1);
        }
    } else {
        int status;
        wait(&status);
    }
    return 0;
}
