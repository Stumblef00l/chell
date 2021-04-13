#include <string>
#include <string.h>
#include <unistd.h>
#include <path.hpp>

Path::Path() {
    path = (char**)malloc(sizeof(char*) * 3);
    path[0] = (char*)malloc(5 * sizeof(char));
    strcpy(path[0], "/bin");
    path[1] = (char*)malloc(9 * sizeof(char));
    strcpy(path[1], "/usr/bin");
    path[2] = NULL;
}

char* Path::resolvePath(char *cmd) {
    int ind = 0;
    char *binpth = NULL;
    while(path[ind] != NULL) {
        binpth = (char*)realloc(binpth, sizeof(char) * (strlen(path[ind]) + strlen(cmd) + 2));   
        strcpy(binpth, path[ind]);
        strcat(binpth, "/");
        strcat(binpth, cmd);
        if(access(binpth, X_OK) == 0)
            return binpth;
        ind++;
    }
    free(binpth);
    return NULL;
}

void Path::changePath(char **args) {
    
    // Memory cleanup for path
    int argc = 0;
    while(path[argc] != NULL) {
        free(path[argc]);
        argc++;
    }
    free(path);

    argc = 0;
    while(args[argc] != NULL) 
        argc++;
    path = (char**)malloc(sizeof(char*) * argc);
    argc = 1;
    while(args[argc] != NULL) {
        path[argc - 1] = (char*)malloc(sizeof(char) * (strlen(args[argc]) + 1));
        strcpy(path[argc - 1], args[argc]);
        argc++;
    }
    path[argc - 1] = NULL;
}
