//
// Created by KALIK on 11.10.2021.
/**
 * THis Library can converte file into assembly byte file.
 * This Library work with bit_string.
 * If the assembler meets an unknown command it moves on,
 * and don't read this command in file.
 * My syntax's:
 *
 * COMMAND:
 * My program have unobvious byte structure commands:
 * |____________|__________|
 * |            |          |
 * |   PUSH     |  DATA    |
 * | (com spec) | (data)   |
 * |____________|__________|
 *
 * 1 byte - it's command specifier
 * 2 byte and more - it's data
 *
 *
 *
 * Data consist of:
 *          1. Data specifier (PLUS_FLAG, CONST_FLAG, REG_FLAG)
 *          2. And the data that the specifier describes
 * But most important that data may consist another nested data with own data specifier
 *
 * Example:
 * |________________|____________|       |___________________|_________________|   |__________________|______________|
 * |                |            |       |                   |                 |   |                  |              |
 * |    PLUS_FLAG   |   DATA     |  ->   |     REG_FLAG      |      DATA       | + |   CONST_FLAG     |    DATA      |
 * |    (data spec  |  (data)    |       |  (data specifier) | (register data) |   | (data specifier) | (const data) |
 * |________________|____________|       |___________________|_________________|   |__________________|______________|
 *
 *
 * PLUS:
 * 1. spaces exist after and before "+"
 *          10 + 10 - right
 *          10+10   - wrong
 *          10+ 10  - wrong
 *          10 +10  - wrong
 *
 * COMMA:
 * 1. spaces exist after and before ","
 *          10 , 10 - right
 *          10,10   - wrong
 *          10, 10  - wrong
 *          10 ,10  - wrong
 * 2. comma may be only one
 *          10 , 10 - right
 *          10 , 11, 12 - wrong
 *
 * SQRT BRACKETS:
 * I suppose that space exists before left sqrt bracket
 * if space doesn't exist before left sqrt bracket - it's error
 *          POP [ - right
 *          POP[ - lexical error
**/

#ifndef ASSEMBLER_ASSEMBLER_H
#define ASSEMBLER_ASSEMBLER_H

#include <MyLibString.h>
#include <libHelpKalik.h>
#include <LibStack.h>

/// Debug defines
//#define ASM_MARK_DEBUG
#define ASM_DEBUG

#define CLEAN_MEM \
    SkekDtor(&undef_mark_names);              \
    free(arr_bit_string.arr); \
    free_memory_for_string_array(&arr_string);\
    fclose(prog_file);\
    fclose(bin_file);

#define ALLOC_COM(com) \
    pos_com ++;\
    bit_string->size = sizeof(char);\
    ALLOCATE_BITS(bit_string->data, bit_string->size, error)\
    *(char*)((char*)bit_string->data) = com;

// todo think about change these 3 defines on 1 own define

#define ASM_CMD_WITH_ARG(name) \
    if (command_arr[1] == nullptr) { \
        FUNC_ERROR(error, ASM_WRONG_FORMAT) \
    } \
     \
    ALLOC_COM(name) \
    \
    if (SeriesFlag(bit_string, command_arr, size_com, &pos_com, error)) { \
        CHECK_FOR_ERR(error, false)  \
        \
        if (pos_com != size_com) {   \
            FUNC_ERROR(error, ASM_NOT_ALL_SYMB_RECOGNIZE)                       \
        }                      \
        else return true;\
    }\
    \
    free(bit_string->data);                                               \
    CHECK_FOR_ERR(error, false)                  \
    FUNC_ERROR(error, ASM_WRONG_FORMAT)

#define ASM_CMD(name) \
                      \
    ALLOC_COM(name)\
                      \
    if (NoFlag    (bit_string, command_arr, size_com, &pos_com, error)) { \
        CHECK_FOR_ERR(error, false)                                       \
        return true;                  \
    }                 \
                      \
    if (SeriesFlag(bit_string, command_arr, size_com, &pos_com, error)) { \
        CHECK_FOR_ERR(error, false)                        \
                      \
        if (pos_com != size_com) {                                        \
            FUNC_ERROR(error, ASM_NOT_ALL_SYMB_RECOGNIZE)                       \
        }                      \
        else return true;\
    }\
    \
    free(bit_string->data);                                               \
    CHECK_FOR_ERR(error, false)                  \
    FUNC_ERROR(error, ASM_WRONG_FORMAT)

#define ASM_KALIK_COMPARE(name) \
    if (command_arr[1] == nullptr) { \
        FUNC_ERROR(error, ASM_WRONG_COMARE_FORMAT) \
    } \
     \
    ALLOC_COM(name) \
    \
    if (EnumFlag(bit_string, command_arr, size_com, &pos_com, error)) { \
        CHECK_FOR_ERR(error, false)  \
                                \
        if (pos_com != size_com) {   \
            FUNC_ERROR(error, ASM_NOT_ALL_SYMB_RECOGNIZE)                       \
        }                      \
        else return true;\
    }\
    \
    free(bit_string->data);                                               \
    CHECK_FOR_ERR(error, false)                  \
    FUNC_ERROR(error, ASM_WRONG_FORMAT)



/// one mark
struct mrk {
    char* name          = nullptr;
    long long byte_pos  = -1;
};

/// table mark
struct tbmrk {
    mrk* table          = nullptr;
    long long size      = 0;
    long long capacity  = 0;
};

/// pointer on table mark
/// pos_name        - position index name in mark_table
/// arr_index       - index name in array of string
/// byte_pos_in_str - byte position in certain string
struct ptr_mrk {
    long long pos_name         = -1;
    long long arr_index        = -1;
    long long byte_pos_in_str  = -1;
};

/// Size table with kek_mark in assembler
extern const int ASM_KEK_MARK_BUFF_SIZE;

/// Convert input file in bin file in form char\n
/// 4 first byte file it's my information about file.\n
/// First 4 byte - my signature\n
/// Func write in ASM_LOG_FILE_NAME debug file, if you wanna change output logfile\n
/// Change const ASM_LOG_FILE_NAME.\n
/// \param program_file_name - input file with program assembler code
/// \param binfile_name      - output bin file
/// \return true if operation succesfull or false if not
bool assembler (const char* program_file_name = PROGRAM_FILE_NAME,
                const char* binfile_name = BIN_FILE_NAME,
                CPU_ERRORS *error = &ASM_ERR);

/// DUMP

/// Write in logfile info about convert txt file with command -> bin file
/// \param arr_string      - array with string which consist of commands
/// \param arr_bit_string  - array wit bit form strings
/// \param logfile_name    - In whis file write info
/// \return True if operation Successfully or False else
bool ASMDump       (myarr* arr_string, arr_bit_str* arr_bit_string,
                    const char* logfile_name = ASM_LOG_FILE_NAME,
                    CPU_ERRORS* error = &ASM_ERR);

/// Write string and bit form this string (in Hex format) in logfile
/// \param logfile      - pointer on file descriptor
/// \param string       - string
/// \param bit_string   - bit form input string
/// \return True if operation Successfully or False else
bool ASMStrDump    (FILE* logfile, mystr* string, bit_str* bit_string);

/// Dump for Mark table
/// \param logfile File whose will write information
/// \return True if operation Successfully or False else
bool MarkDump      (FILE* logfile);

/// HELP FUNCTION

/// Convert arr strings(consist of command) into bit_string (bit form input string)
/// \param command_arr - Input arr string(consist of command)
/// \param bit_string  - Pointer on exist bit_string.\n
/// In this variable recording bit form input string
/// \param size_com    - Size command line
/// \param error       - ASM ERROR
/// \return True if operation Successfully or False else
bool ConvInBin (char** command_arr, bit_str* bit_string,
                size_t size_com, CPU_ERRORS* error = &ASM_ERR);

/// Compare input string with processor command
/// \param string - pointer on input string
/// \return  identifier on command
ASM_COMMANDS ConvCom (const char* string);


/// ConvReg - convert input string in bit name register
/// \param string - input string
/// \return enum number register
CPU_REGISTERS ConvReg(const char* string);

/// Reload mark names with -1 position\n
/// These positions were wrote in skek (undef_mark_names)\n
/// After these operation skek data must be lack\n
/// \param arrBitStr Array with bit strings
/// \param error     Error pointer
/// \return True if operation success else false
bool ReloadMarkName(arr_bit_str* arrBitStr, CPU_ERRORS* error = &CPU_ERR);


/// FLAGS OPERATIONS

/// This Function recognized all commands\n
/// Func consist of flag functions(PlusFlag, SqrtFlag...)\n
/// \param bit_string - Pointer on byte form this command
/// \param command_arr - Array with command in text form
/// \param size_com - Size command array
/// \param pos_com - Pointer on number being currently position in command array\n
///                  Command hasn't processed in currently position yet.
/// \param errors - Errors pointer.
/// \return True if find flag or false if func can't recognize flag.
bool SeriesFlag (bit_str* bit_string, char** command_arr,
                 size_t size_com, size_t* pos_com,
                 CPU_ERRORS* errors = &ASM_ERR);

/// Func processes command with null data.\n
/// If command_arr[pos_com] == nullptr that\n
/// Func write in bit_string 1 byte - NO_FLAG
/// \param bit_string - Pointer on byte form this command
/// \param command_arr - Array with command in text form
/// \param size_com - Size command array
/// \param pos_com - Pointer on number being currently position in command array\n
///                  Command hasn't processed in currently position yet.
/// \param errors - Errors pointer.
/// \return True if currently command is NO_FLAG.\n
///         False if it's not NO_FLAG or error interrupt.
bool NoFlag     (bit_str* bit_string, char** command_arr,
                 size_t size_com, size_t* pos_com,
                 CPU_ERRORS* errors = &ASM_ERR);

/// Func processes command with mark names\n
/// If command_arr[pos_com] started with ":" that\n\n\n
///
/// 1. If new name don't exists in mark_table that, Func write in mark_table.name new name.\n\n
///           a. If this name is first command that write in mark_table.byte_pos this pos.\n
///              Don't expand bit_string\n\n
///           b. If this name isn't first command that write in mark_table.byte_pos -1\n
///              Push in skek(with undefined mark names) position this name\n
///              Expand bit_string on sizeof(char) + sizeof(ASM_MARK_TYPE)\n
///              First byte - MARK_FLAG\n
///              Seconds sizeof(ASM_MARK_TYPE) bytes - ASM_MAGIC_NUMBER for debug.\n\n\n
///
/// 2. If new name exist in mark_table that\n\n
///           a. If this name is first command and have mark_table.byte_pos == -1 that, \n
///              We find real byte_pos this name and write in mark_table.byte_pos current position bit_string\n
///              Don't expajd bit_sting\n\n
///           b. If this name is only first command(without mark_table.byte_pos == -1) that error: ASM_SECONDLY_MARK_DEFINITION.\n\n
///           c. If this name isn't first command and mark_table.byte_pos == -1 that,\n
///              We found another one non-definition name:\n
///              Push in skek(with undefined mark names) position this name\n
///              Expand bit_string on sizeof(char) + sizeof(ASM_MARK_TYPE)\n
///              First byte - MARK_FLAG\n
///              Seconds sizeof(ASM_MARK_TYPE) bytes - ASM_MAGIC_NUMBER for debug.\n\n
///           d. If this name isn't first command and mark_table.byte_pos != -1 that,\n
///              We found another one already definition name:\n
///              Expand bit_string on sizeof(char) + sizeof(ASM_MARK_TYPE)\n
///              First byte - MARK_FLAG\n
///              Seconds sizeof(ASM_MARK_TYPE) bytes - position these def name (mark_table.byte_pos).\n\n\n
/// \param bit_string   Pointer on byte form this command
/// \param command_arr  Array with command in text form
/// \param size_com     Size command array
/// \param pos_com      Pointer on number being currently position in command array\n
///                     Command hasn't processed in currently position yet.
/// \param errors       Errors pointer
/// \return True if currently command have MARK_FLAG (and if these operation success)\n
///         Else False if it's not command with MARK_FLAG or error interrupt\n
bool MarkFlag  (bit_str* bit_string, char** command_arr,
                size_t size_com, size_t* pos_com,
                CPU_ERRORS* errors = &ASM_ERR);

/// Func processes command with consts.\n
/// If command_arr[pos_com] is number that\n
/// Func write in bit_string 1 + sizeof(COMMON_ASM_TYPE) byte - first is COSNT_FLAG, second is number in byte form.
/// \param bit_string - Pointer on byte form this command
/// \param command_arr - Array with command in text form
/// \param size_com - Size command array
/// \param pos_com - Pointer on number being currently position in command array\n
///                  Command hasn't processed in currently position yet.
/// \param errors - Errors pointer.
/// \return True if currently command is CONST_FLAG.\n
///         False if it's not CONST_FLAG or error interrupt.
bool ConstFlag  (bit_str* bit_string, char** command_arr,
                 size_t size_com, size_t* pos_com,
                 CPU_ERRORS* errors = &ASM_ERR);

/// Func processes command with register names.\n
/// If command_arr[pos_com] is register name that\n
/// Func write in bit_string 2 byte - first is REG_FLAG, second is byte name reg.
/// \param bit_string - Pointer on byte form this command
/// \param command_arr - Array with command in text form
/// \param size_com - Size command array
/// \param pos_com - Pointer on number being currently position in command array\n
///                  Command hasn't processed in currently position yet.
/// \param errors - Errors pointer.
/// \return True if currently command is REG_FLAG.\n
///         False if it's not REG_FLAG or error interrupt.
bool RegFlag    (bit_str* bit_string, char** command_arr,
                 size_t size_com, size_t* pos_com,
                 CPU_ERRORS* errors = &ASM_ERR);

/// Func processes command with "+" symbol.\n
/// Func look at first 3 command, starting with pos_com. And if 2 command is "+".\n
/// That func add in bit_string byte with PLUS_FLAG.\n
/// And Func moves in deep to first command and third command.\n
/// \param bit_string - Pointer on byte form this command
/// \param command_arr - Array with command in text form
/// \param size_com - Size command array
/// \param pos_com - Pointer on number being currently position in command array\n
///                  Command hasn't processed in currently position yet.
/// \param errors - Errors pointer.
/// \return True if currently command is PLUS_FLAG.\n
///         False if it's noе PLUS_FLAG or error interrupt.
bool PlusFlag   (bit_str* bit_string, char** command_arr,
                 size_t size_com, size_t* pos_com,
                 CPU_ERRORS* errors = &ASM_ERR);


/// Func processes command with "," symbol.\n
/// Func look at first 3 command, starting with pos_com. And if second command is ",".\n
/// That func add in bit_string byte with ENUM_FLAG.\n
/// And Func moves in deep to first command and third command.\n
/// \param bit_string - Pointer on byte form this command
/// \param command_arr - Array with command in text form
/// \param size_com - Size command array
/// \param pos_com - Pointer on number being currently position in command array\n
///                  Command hasn't processed in currently position yet.
/// \param errors - Errors pointer.
/// \return True if currently command is ENUM_FLAG.\n
///         False if it's noе ENUM_FLAG or error interrupt.
bool EnumFlag   (bit_str* bit_string, char** command_arr,
                 size_t size_com, size_t* pos_com,
                 CPU_ERRORS* errors) ;


/// Func processes command with sqrt brackets.\n
/// Try find "[". If find bracket go to second right bracket "]".\n
/// Write this in bit_string in byte form.\n
/// Write only byte MEM_FLAG, and go in deep bracket.
/// \param bit_string - Pointer on byte form this command
/// \param command_arr - Array with command in text form
/// \param size_com - Size command array
/// \param pos_com - Pointer on number being currently position in command array\n
///                  Command hasn't processed in currently position yet.
/// \param errors - Errors pointer.
/// \return True if currently command is MEM_FLAG.\n
///         False if it's not MEM_FLAG or error interrupt.
bool SqrtFlag   (bit_str* bit_string, char** command_arr,
                 size_t size_com, size_t* pos_com,
                 CPU_ERRORS* errors = &ASM_ERR);

#endif //ASSEMBLER_ASSEMBLER_H
