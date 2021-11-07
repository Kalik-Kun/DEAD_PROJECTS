#include <iostream>
#include "Disassembler.h"

int main(int argc,  char* argv[], char* envp[]) {
    if (argc != 2) {
        printf("\x1b[31mPLEASE input name file\x1b[0m\n");
        disassembler("Disassm.txt", BIN_FILE_NAME);
        return 0;
    }
    const char *NAME_BIN_FILE = argv[1];


    disassembler("Disassm.txt", NAME_BIN_FILE);
    return 0;
}
