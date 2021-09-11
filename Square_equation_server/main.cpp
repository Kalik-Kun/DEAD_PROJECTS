#include <iostream>
#include <unistd.h>
#include <string.h>
#define ERROR_CODE 2
#define TEXT "It's messdge for me bro not for you mother faker\n"

int main() {
    pid_t pid;
    char *buf = (char*)calloc(strlen(TEXT), sizeof(char));
    int pipe_input[2], pipe_output[2];

    if (pipe(pipe_input)) {
        printf("ERROR\n");
        return 0;
    }

    pid = fork();

    if (pid < 0) {
        printf("ERROR\n");
        return 0;
    }

    if (pid == 0) {
        close(pipe_input[1]);
        read(pipe_input[0], buf, strlen(TEXT));
        printf("%s", buf);
        close (pipe_input[0]);
    }
    else {
        close(pipe_input[0]);
        write(pipe_input[1], TEXT, strlen(TEXT));
        close(pipe_input[1]);
    }

    return 0;
}
