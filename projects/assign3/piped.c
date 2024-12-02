// piped.c

#include "piped.h"

int piped(char msg[], int mode, int fd) {
    switch (mode) {
        case 0: // read from child process
            read(fd, msg, BUFFER_SIZE);
            break;
        case 1: // write to child process
            write(fd, msg, strlen(msg) + 1);
            break;
        case 2: // read from parent process
            read(fd, msg, BUFFER_SIZE);
            break;
        case 3: // write to parent process
            write(fd, msg, strlen(msg) + 1);
            break;
        default:
            printf("Invalid mode input\n");
            return -1;
    }
    return 0;
}
