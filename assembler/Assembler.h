//
// Created by arlik_null on 11.10.2021.
//

#ifndef ASSEMBLER_ASSEMBLER_H
#define ASSEMBLER_ASSEMBLER_H

#include "../Stack/LibStack.h"

enum commands {
    CMD_PUSH,
    CMD_ADD,
    CMD_MULT,
    CMD_DIVIDE,
    CMD_END,
};

#define OPEN_FILE(file_name, w) { \
     FILE* file  = fopen(file_name,  "w");\
    if (bin_file == nullptr) {\
        printf("\x1b[31b\n"\
        "ERROR IN OPEN FILE: %s", bin_file_name);\
        return false;\
    }\
    return openfile;\
}

extern const char* BIN_FILE_NAME;
extern const char* PROGRAM_FILE_NAME;
extern const char* LOG_FILE_NAME;

/// Convert input file in bin file
/// \param program_file_name - input file with program assembler code
/// \param binfile_name      - output bin file
/// \return true if operation succesfull or false if not
bool to_bin_file (const char* program_file_name = PROGRAM_FILE_NAME,
                  const char* binfile_name = BIN_FILE_NAME);



#endif //ASSEMBLER_ASSEMBLER_H
