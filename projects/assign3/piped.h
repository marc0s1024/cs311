#ifndef PIPED_H
#define PIPED_H

#include <unistd.h>     // read write functions
#include <string.h>
#include <stdio.h>
#include <sys/types.h>  // pid_t
#include <stdlib.h>     // exit
#include <sys/wait.h>   // wait


#define BUFFER_SIZE 1024

// Function prototypes
int piped(char msg[], int mode, int fd);

#endif
