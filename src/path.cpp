#include <string>
#include <string.h>
#include <unistd.h>
#include <path.hpp>

Path::Path() {
    path = new char*[3];
    path[0] = new char[strlen("/bin") + 1];
    strcpy(path[0], "/bin");
    path[1] = new char[strlen("/usr/bin") + 1];
    strcpy(path[1], "/usr/bin");
    path[2] = NULL;
}

char* Path::resolvePath(char *cmd) {
    int ind = 0;
    char *binpth = NULL;
    while(path[ind] != NULL) {
        if(binpth != NULL)
            delete binpth;
        binpth = new char[strlen(path[ind]) + strlen(cmd) + 2];   
        strcpy(binpth, path[ind]);
        strcat(binpth, "/");
        strcat(binpth, cmd);
        if(access(binpth, X_OK) == 0)
            return binpth;
        ind++;
    }
    if(binpth != NULL)
        delete binpth;
    return NULL;
}

void Path::changePath(char **args) {
    
    // Memory cleanup for path
    int argc = 0;
    while(path[argc] != NULL) {
        delete path[argc];
        argc++;
    }
    delete path;

    argc = 0;
    while(args[argc] != NULL) 
        argc++;
    path = new char*[argc];
    argc = 1;
    while(args[argc] != NULL) {
        path[argc - 1] = new char[strlen(args[argc]) + 1];
        strcpy(path[argc - 1], args[argc]);
        argc++;
    }
    path[argc - 1] = NULL;
}
