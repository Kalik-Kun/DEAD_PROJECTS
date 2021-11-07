#include <iostream>
#include "LibProc.h"
int main(int argc,  char* argv[], char* envp[]) {

    char *NAME_BIN_FILE = nullptr;
    fclose(fopen(CPU_LOG_FILE_NAME, "w"));

    CPU proc = {};

    if (argc != 2) {
//        printf("\x1b[31mPLEASE input name file\x1b[0m\n");
        CPUStart(&proc, BIN_FILE_NAME);
    }
    else {
        NAME_BIN_FILE = argv[1];
        CPUStart(&proc, NAME_BIN_FILE);
    }
    CPUPerform(&proc);

    return 0;
}
