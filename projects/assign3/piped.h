// piped.h

#ifndef PIPED_H
#define PIPED_H

#include <unistd.h>     // read write functions
#include <string.h>
#include <stdio.h>

#define BUFFER_SIZE 1024

// Function prototypes
int piped(char msg[], int mode, int fd);

#endif
