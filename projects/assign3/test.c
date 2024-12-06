#include "piped.h"

int main() {
    int parent_to_child[2]; // pipe parent to child
    int child_to_parent[2]; // pipe child to parent
    pid_t pid;
    char msg[BUFFER_SIZE];

    // create pipes
    if (pipe(parent_to_child) == -1) {
        perror("Parent to child pipe creation failed");
        exit(1);
    }
    if (pipe(child_to_parent) == -1) {
        perror("Child to parent pipe creation failed");
        exit(1);
    }

    // fork process
    pid = fork();

    if (pid > 0) {
        // parent Process
        close(parent_to_child[0]); // close unused read end of parent-to-child pipe
        close(child_to_parent[1]); // close unused write end of child-to-parent pipe

        // write message to child
        strcpy(msg, "Hi from parent");
        piped(msg, 1, parent_to_child[1]); // Mode 1: Write to child
        printf("Parent sent: %s\n", msg);

        // read message from child
        memset(msg, 0, BUFFER_SIZE); // clear buffer
        piped(msg, 0, child_to_parent[0]); // Mode 0: Read from child
        printf("Parent received: %s\n", msg);

        // close used pipe ends
        close(parent_to_child[1]); // close write end
        close(child_to_parent[0]); // close read end

        wait(NULL); // wait for child process to finish

    }
    else if (pid == 0) {
        // child Process
        // close unused pipe ends
        close(parent_to_child[1]); // close write end of parent-to-child pipe
        close(child_to_parent[0]); // close read end of child-to-parent pipe

        // read message from parent
        memset(msg, 0, BUFFER_SIZE); // clear the buffer
        piped(msg, 2, parent_to_child[0]); // Mode 2: Read from parent
        printf("Child received: %s\n", msg);

        // write message to parent
        strcpy(msg, "Hi from child");
        piped(msg, 3, child_to_parent[1]); // Mode 3: Write to parent
        printf("Child sent: %s\n", msg);

        // close used pipe ends
        close(parent_to_child[0]); // close read
        close(child_to_parent[1]); // close write

        exit(0); // terminate child proc

    }
    else {
        // fork fail
        perror("Fork failed");
        exit(1);
    }

    return 0;
}
