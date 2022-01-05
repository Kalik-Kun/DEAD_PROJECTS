#include "Assembler.h"



int main(int argc,  char* argv[], char* envp[]) {
    // for normal deb skke files
    //todo how check existsting folder and create folder
    const char *NAME_PROG_FILE  = nullptr;
    const char *NAME_CLEAN_PROG_FILE = CLEAN_PROGRAM_FILE_NAME;
    const char *NAME_BIN_FILE   = nullptr;

    if (argc == 1) {
        NAME_PROG_FILE = PROGRAM_FILE_NAME;
        NAME_BIN_FILE  = BIN_FILE_NAME;
    }
    else if (argc == 2) {
        NAME_PROG_FILE = argv[1];
        NAME_BIN_FILE  = BIN_FILE_NAME;
    }
    else if (argc == 3) {
        NAME_PROG_FILE  = argv[1];
        NAME_BIN_FILE   = argv[2];
    }
    else {
        printf("\x1b[31mPLEASE INPUT 2 or 1 or 0 argument with name\n"
               "Count input elements: %d\n"
               "\x1b[0m", argc);
        return 0;
    }

//    cleaning_file_and_record(NAME_PROG_FILE, NAME_CLEAN_PROG_FILE);

    printf ("\x1b[32mStart with\n"
            "Program name:  %s\n"
            "Clean program file: %s\n"
            "Bin file name: %s\n"
            "\x1b[0m", NAME_PROG_FILE, NAME_CLEAN_PROG_FILE, NAME_BIN_FILE);

//    assembler(NAME_PROG_FILE, NAME_BIN_FILE);
    assembler(NAME_PROG_FILE, NAME_BIN_FILE);

    return 0;
}
