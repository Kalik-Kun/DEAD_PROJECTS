//
// Created by KALIK on 11.10.2021.
//

#include "Assembler.h"

const char* BIN_FILE_NAME     = "bin_file.txt";
const char* PROGRAM_FILE_NAME = "prog.txt";
const char* LOG_FILE_NAME     = "ASMLogFile.txt";

bool to_bin_file(const char* prog_file_name,  const char* bin_file_name) {
    FILE* prog_file = fopen(prog_file_name, "r");
    if (prog_file == nullptr) {
        printf("\x1b[31b\n"
               "ERROR IN OPEN FILE: %s", prog_file_name);
        return false;
    }
    FILE* bin_file  = fopen(bin_file_name,  "w");
    if (bin_file == nullptr) {
        printf("\x1b[31b\n"
               "ERROR IN OPEN FILE: %s", bin_file_name);
        return false;
    }





    return true;
}