#include <iostream>
#include "Disassembler.h"

int main(int argc,  char* argv[], char* envp[]) {

    const char *NAME_BIN_FILE = nullptr;
    const char *NAME_DISSASM_FILE = nullptr;

    if (argc == 1) {
        NAME_BIN_FILE       = BIN_FILE_NAME;
        NAME_DISSASM_FILE   = DISASM_FILE_NAME;
    }
    else if (argc == 2) {
        NAME_BIN_FILE       = argv[1];
        NAME_DISSASM_FILE   = DISASM_FILE_NAME;
    }
    else if (argc == 3) {
        NAME_BIN_FILE       = argv[1];
        NAME_DISSASM_FILE   = argv[2];
    }
    else {
        printf("\x1b[31mPLEASE INPUT 2 or 1 or 0 argument with name\n"
               "Count input elements: %d\n"
               "\x1b[0m", argc);
        return 0;
    }

    printf("\x1b[32mSTART DISSASM:\n"
           "first input bin file name: %s\n"
           "second output disassembler file name: %s\n"
           "\x1b[0m", NAME_BIN_FILE, NAME_DISSASM_FILE);

    disassembler(DISASM_FILE_NAME, NAME_BIN_FILE);
    return 0;
}
