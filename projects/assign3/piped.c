#include "piped.h"

int piped(char msg[], int mode, int fd) {
    ssize_t result; // same return type as read/write

    switch (mode) {
        case 0: // read from child process
            result = read(fd, msg, BUFFER_SIZE - 1);
            
            if (result == -1) {
                perror("Read failed");
                return -1;
            }

            if (result >= 0 && result < BUFFER_SIZE) {
                msg[result] = '\0'; // null terminate string
            }
            break;

        case 1: // write to child process
            if (write(fd, msg, strlen(msg) + 1) == -1) {
                perror("Write failed");
                return -1;
            }
            break;

        case 2: // read from parent process
            result = read(fd, msg, BUFFER_SIZE - 1);

            if (result == -1) {
                perror("Read failed");
                return -1;
            }

            if(result >= 0 && result < BUFFER_SIZE) {
                msg[result] = '\0'; // null terminate string
            }
            break;

        case 3: // write to parent process
            if(write(fd, msg, strlen(msg) + 1) == -1) {
                perror("Write failed");
                return -1;
            }
            break;

        default:
            printf("Invalid mode input\n");
            return -1;
    }
    return 0;
}
