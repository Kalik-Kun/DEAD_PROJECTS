#include <iostream>
#include "LibProc.h"
int main(int argc,  char* argv[], char* envp[]) {

    const char *NAME_BIN_FILE = nullptr;

    // todo 1 open
    // todo destructor and constructor
    fclose(fopen(CPU_LOG_FILE_NAME, "w"));

    CPU proc = {};

    if (argc == 1) {
        NAME_BIN_FILE = BIN_FILE_NAME;
    }
    else if (argc == 2) {
        NAME_BIN_FILE = argv[1];
    }
    else {
        printf("\x1b[31mInput error amount console parameters.\n"
               "Amount parameters: %d\n"
               "\x1b[0m", argc);
        return 0;
    }

    printf("\x1b[32mSTART CPU:\n"
           "input bin file: %s\n"
           "\n"
           "\x1b[0m", NAME_BIN_FILE);

    CPUStart(&proc, NAME_BIN_FILE);

    CPUPerform(&proc);

    return 0;
}
