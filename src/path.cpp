#include <string>
#include <string.h>
#include <unistd.h>
#include <path.hpp>

Path::Path() {
    path = new char*[sizeof(char*) * 3];
    path[0] = new char[5 * sizeof(char)];
    strcpy(path[0], "/bin");
    path[1] = new char[9 * sizeof(char)];
    strcpy(path[1], "/usr/bin");
    path[3] = NULL;
}

char* Path::resolvePath(char *cmd) {
    int ind = 0;
    std::string cmdStr = std::string(cmd);
    while(path[ind] != NULL) {
        std::string binpth = std::string(path[ind]) + "/" + cmdStr;
        if(access(binpth.c_str(), X_OK) == 0) {
            int len = binpth.length();
            char *buff = new char[sizeof(char) * (len + 1)];
            binpth.copy(buff, len + 1);
            return buff;
        }
        ind++;
    }
    return NULL;
}

void Path::changePath(char **args) {
    int argc = 0;
    while(path[argc] != NULL) {
        delete[] path[argc];
        argc++;
    }
    delete[] path;
    argc = 0;
    while(args[argc] != NULL) 
        argc++;
    argc--;
    path = new char*[argc + 1];
    argc = 1;
    while(args[argc] != NULL) {
        path[argc - 1] = new char[strlen(args[argc]) + 1];
        strcpy(path[argc - 1], args[argc]);
        argc++;
    }
    path[argc - 1] = NULL;
}
