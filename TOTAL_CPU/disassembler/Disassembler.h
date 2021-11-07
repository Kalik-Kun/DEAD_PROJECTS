//
// Created by arlik_null on 24.10.2021.
//
/* Disassembler - Convert input bin file in normal txt view
 * Disassembler see UNDEFINED bytes in file and if it can't recognize these bytes, return error and interrupts program
 *
*/
#ifndef DISASSEMBLER_DISASSEMBLER_H
#define DISASSEMBLER_DISASSEMBLER_H

#include <MyLibString.h>
#include <libHelpKalik.h>

#define PRINT_COM_WITH_FLAGS(cmd) \
    *numb_byte += sizeof(char);\
    fprintf(prog_file, #cmd " ");\
    if(!FlagShow(buffer, numb_byte, prog_file, error)) {\
        FUNC_ERROR(error, UNDEFINED)\
    }\
    fprintf_data_HEX(prog_file,\
                    ((char*)buffer + start_byte),\
                    *numb_byte - start_byte, MAX_INDENT);\
    fprintf(prog_file, "\n");


#define PRINT_COM(cmd) \
    fprintf(prog_file, #cmd); \
    fprintf_data_HEX(prog_file,\
                ((char*)buffer + *numb_byte),\
                1*sizeof(char), MAX_INDENT);\
    *numb_byte += sizeof(char);\
    fprintf(prog_file, "\n");


/// Convert input bin file in txt file\n
/// Func write in LOG_FILE_NAME debug file, if you wanna change output logfile\n
/// Change const LOG_FILE_NAME.\n
/// \param program_file_name - otput txt file
/// \param binfile_name     - input bin file with program assembler code
/// \return true if operation succesfull or false if not
bool disassembler (const char* program_file_name = PROGRAM_FILE_NAME,
                   const char* binfile_name = BIN_FILE_NAME,
                   CPU_ERRORS *error = &ASM_ERR);

/// Perform bin command are contained in buffer\n
/// If you don't want print set prog_file = nullptr\n
/// Else pointer on file descriptor
/// \param buffer      - input buffer consist of command
/// \param numb_byte   - Intend buffer
/// \param prog_file   - pointer on descriptor program file
/// \param error       - errors
/// \return True if command exist or False if CmdShow can't recognize command
bool CmdShow(void* buffer,
             size_t *numb_byte, FILE* prog_file = nullptr,
             CPU_ERRORS* error = &CPU_ERR);

/// Show data (go to all flags)
/// \param buffer       Input buffer consist of command
/// \param numb_byte    Intend buffer
/// \param prog_file    Pointer on descriptor program file
/// \param error        Error pointer
/// \return True if command exist or False if CmdShow can't recognize command
bool FlagShow(void* buffer,
                size_t* numb_byte, FILE* prog_file = nullptr,
                CPU_ERRORS* error = &CPU_ERR);

/// Show data with (NO_FLAG)
/// \param buffer       Input buffer consist of command
/// \param numb_byte    Intend buffer
/// \param prog_file    Pointer on descriptor program file
/// \param error        Error pointer
/// \return True if command exist or False if CmdShow can't recognize command
bool NoShow(void* buffer,
               size_t* numb_byte, FILE* prog_file = nullptr,
               CPU_ERRORS* error = &CPU_ERR);

/// Show data with (MARK_FLAG)
/// \param buffer       Input buffer consist of command
/// \param numb_byte    Intend buffer
/// \param prog_file    Pointer on descriptor program file
/// \param error        Error pointer
/// \return True if command exist or False if CmdShow can't recognize command
bool MarkShow (void* buffer,
               size_t* numb_byte, FILE* prog_file = nullptr,
               CPU_ERRORS* error = &CPU_ERR);

/// Show data with (CONST_FLAG)
/// \param buffer       Input buffer consist of command
/// \param numb_byte    Intend buffer
/// \param prog_file    Pointer on descriptor program file
/// \param error        Error pointer
/// \return True if command exist or False if CmdShow can't recognize command
bool ConstShow(void* buffer,
              size_t* numb_byte, FILE* prog_file = nullptr,
              CPU_ERRORS* error = &CPU_ERR);

/// Show data with (REG_FLAG)
/// \param buffer       Input buffer consist of command
/// \param numb_byte    Intend buffer
/// \param prog_file    Pointer on descriptor program file
/// \param error        Error pointer
/// \return True if command exist or False if CmdShow can't recognize command
bool RegShow(void* buffer,
               size_t* numb_byte, FILE* prog_file = nullptr,
               CPU_ERRORS* error = &CPU_ERR);

/// Show data with (PLUS_FLAG)
/// \param buffer       Input buffer consist of command
/// \param numb_byte    Intend buffer
/// \param prog_file    Pointer on descriptor program file
/// \param error        Error pointer
/// \return True if command exist or False if CmdShow can't recognize command
bool PlusShow(void* buffer,
               size_t* numb_byte, FILE* prog_file = nullptr,
               CPU_ERRORS* error = &CPU_ERR);

/// Show data with (SQRT_FLAG)
/// \param buffer       Input buffer consist of command
/// \param numb_byte    Intend buffer
/// \param prog_file    Pointer on descriptor program file
/// \param error        Error pointer
/// \return True if command exist or False if CmdShow can't recognize command
bool SqrtShow(void* buffer,
               size_t* numb_byte, FILE* prog_file = nullptr,
               CPU_ERRORS* error = &CPU_ERR);


#endif //DISASSEMBLER_DISASSEMBLER_H
