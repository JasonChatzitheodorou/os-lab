#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    int child;

    while (1) {
        child = fork();

        if(child > 32767) {
            exit(0);
        }

        if(child > 0 && child <= 32767) {
            printf("%d\n", child);
            wait(NULL);
        }

        if(child == 0 && getpid() == 32767) {
            char *new_argv[] = {NULL, NULL, NULL};
            char *new_env[] = {NULL, NULL, NULL};
            execve("./riddle", new_argv, new_env);
        }    
    } 
}
