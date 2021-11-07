#ifndef LIBKALIKHELP_LIBHELPKALIK_H
#define LIBKALIKHELP_LIBHELPKALIK_H

#include <cstdio>
#include <climits>

/// Types defines
//#define ASM_LONGLONG_TYPE
#define ASM_INT_TYPE
/// WARNING double don't work
//#define ASM_DOUBLE_TYPE
//#define ASM_CHAR_TYPE


#ifdef ASM_LONGLONG_TYPE
typedef long long COMMON_ASM_TYPE;
#endif
#ifdef ASM_INT_TYPE
typedef int COMMON_ASM_TYPE;
#endif
#ifdef ASM_DOUBLE_TYPE
typedef double COMMON_ASM_TYPE;
#endif
#ifdef ASM_CHAR_TYPE
typedef char COMMON_ASM_TYPE;
#endif

#define SMALL_DUMP(error_text) \
printf("\x1b[31mERROR\n"\
        "FILE: %s\n"\
        "FUNC: %s\n"\
        "LINE: %d\n"\
        "CPU_ERRORS number: %d\n"\
        "THAT MEAN:" #error_text "\n"\
        "\x1b[0m",              \
        __FILE__, __PRETTY_FUNCTION__, __LINE__, error_text);

#define FUNC_ERROR(var_error, name_error) \
    *(var_error) = name_error;\
    SMALL_DUMP(name_error)\
    return false;

#define FUNC_ERROR_RTRN(var_error, name_error, return_value) \
    *(var_error) = name_error;\
    SMALL_DUMP(name_error)\
    return return_value;

#define ALLOCATE_BITS(data, n, error) \
    data = calloc(n, sizeof(char));\
    if ((data) == nullptr) {     \
        FUNC_ERROR(error, NULLPTR_IN_CALLOC)\
    }

#define CHECK_FOR_ERR(error, return_value) \
    if(*(error) != UNDEFINED) return (return_value);

/// Processor commands
/*
 * When you add command plese change:
 * ASM: ConvCom and ConInBin
 * DisASM:
 * CPU:
 */
enum ASM_COMMANDS {
    CMD_END = 1,    // END PROC (HAVE sizeof(char) bytes in memory)
    CMD_RESET,      // RESET SKEK (HAVE sizeof(char) bytes in memory)

    /* PUSH element in top skek
    // (HAVE sizeof(char) + sizeof(char) +maybe(sizeof(char))+sizeof(COMMON_ASM_TYPE) bytes in memory)
    // 1 byte - it's spec operation
    * 2 byte - it desribe argument. USE: CONST_FLAG, REG_FLAG, REG_FLAG | CONST_FLAG ,TODO(MEM_FLAG)
    // (3 byte mb) - if 2 byte -reg byte use these memory for decribe certain register
    // 3(4) byte - it's data
    // EXAMPLE:
    // PUSH 10      - push 10 in top skek
    // PUSH KEK1    - push register value in top skek
    // PUSH KEK1 + 10 - push register value + 10 in skek
    */
    CMD_PUSH,
    /* POP element in top skek and assigns element(reg or ram)
     * HAVE sizeof(char) + sizeof(char)
     * 1 byte - it's spec operation
     * 2 byte - it desribe argument. USE: NO_FLAG, REG_FLAG, TODO(MEM_FLAG)
     * EXAMPLE:
     * POP       - only delete  top elem in skek
     * POP KEK0  - delete elem in skek and assign register name
     * POP [10]  - delete elem in skek and assign memory
    */
    CMD_POP,
    /* input number (scanf) and put in top skek
    // May be with register (IN or IN KEK0)
    // (HAVE sizeof(char) + sizeof(char) + myabe(sizeof(char)))
    // 1 byte - it's spec operation
    * 2 byte - it desribe argument. USE: CONST_FLAG, REG_FLAG, TODO(MEM_FLAG)
    // (3) byte - for name register if 2 byte allows
    // EXAMPLE:
    // IN
    // IN KEK0
    */
    CMD_IN,
    // output top elem
    // EXAMPLE:
    // OUT
    CMD_OUT,

    // ADD top and top-1 elements (HAVE sizeof(char) bytes in memory)
    CMD_ADD,
    // subtract top and top-1 elements (HAVE sizeof(char) bytes in memory)
    CMD_SUB,
    // MULTIPLY top and top-1 elements
    CMD_MULT,
    // DIVIDE top and top-1 elements
    CMD_DIV,
    // JUMP
    CMD_LEAP,
    
    // UNDEFINED_SKEK
    CMD_UND = CHAR_MAX,
};

enum ASM_FLAGS {
    // no flag after command
    NO_FLAG     = 1,
    // if command have const
    CONST_FLAG  = 2,

    MARK_FLAG   = 4,
    // reg flag after command (that mean next arg is name register)
    REG_FLAG    = 8,
    // if use RAM
    MEM_FLAG    = 16,
    // if use +
    PLUS_FLAG   = 32,

};


enum CPU_REGISTERS {
    REG_KEK0,
    REG_KEK1,
    REG_KEK2,
    REG_KEK3,
    REG_KEK4,
    REG_KEK5,
    REG_KEK6,
    REG_KEK7,
    REG_UND =  CHAR_MAX,
};

/// Processor errors
enum CPU_ERRORS {

    //CPU ERRORS

    CPU_UNDEF_FLAG,
    CPU_NULLPTR_ON_CODE,
    CPU_NULLPTR_ON_RAM,
    CPU_DIVIDE_ON_ZERO,
    CPU_NO_IN_OUTPUT,
    CPU_OUT_MEM_BROADS,
    CPU_PLUS_IN_INPUT,
    CPU_MARK_IN_INPUT,
    CPU_CONST_IN_INPUT,
    CPU_REG_DOESNT_EXIST,

    //ASM ERRORS

    ASM_WRONG_FORMAT,       // Wrong format
    ASM_LACK_SQRT_BRACKET,  // Lack sqrt bracket in input file
    ASM_NOT_MATCH_TYPE,     // define unknown type
    ASM_SECONDLY_MARK_DEFENITION,
    ASM_ERROR_IN_DUMP,      // Dump return false
    ASM_MARK_NAMES_SKEK_ERROR,
    ASM_ERROR_IN_SKEK,
    ASM_MARK_DONT_DEF,

    // OWN error
    UNDEFINED,              // UNDEFINED_SKEK error in proc
    ERR_IN_SCANF,
    NOT_KALIK_FORMAT,       // Input file not KALIK format
    NULLPTR_WHEN_FILE_OPEN, // error in file open
    NULLPTR_IN_CALLOC,      // Calloc return NULLPTR
    NULLPTR_IN_REALLOC,     // Realloc return NULLPTR
    NULLPTR,                // If pointer is NULLPTR
};

/// bit_str - this bit string\n
/// \param index_str - (long) number this string in array
/// \param data    - (void*) pointer on data
/// \param size    - (long) size this bit_string
struct bit_str {
    void*     data          = nullptr;
    long long index_str     = 0;
    long long start_byte    = 0;
    long long size          = 0;
};

/// arr_bit_str - this array consisting of bit string\n
/// \param arr  - pointer on bit_str
/// \param size - size this array
struct arr_bit_str {
    struct bit_str* arr = nullptr;
    long   size         = 0;
};

/// errors var
extern CPU_ERRORS CPU_ERR;
extern CPU_ERRORS ASM_ERR;

/// my signature
extern const int KALIK_SIG;
/// info type how many byte in start bin file are occupied
extern const int INFO_SIZE;

/// Filenames
extern const char* BIN_FILE_NAME;
extern const char* PROGRAM_FILE_NAME;
extern const char* LOG_FILE_NAME;
extern const char* CPU_LOG_FILE_NAME;

/// Indent in dump for output
extern const int MAX_INDENT;

/// ACCURACY DOUBLE ZERO
extern const double CPU_ACCURACY;

/// ASM
typedef COMMON_ASM_TYPE ASM_MARK_TYPE;
extern const ASM_MARK_TYPE ASM_MAGIC_NUMBER;

/// CPU
extern const long SIZE_RAM_BUFFER;



/// OPEN file
/// \param file_name - name file
/// \param spec      - specificator ("w" or "r" or "a" and else)
/// \param error     - error
/// \return pointer on file descriptor
FILE* openfile(const char* file_name, const char* spec, CPU_ERRORS* error = &ASM_ERR);

/// Write bit_string in file in format HEX
/// \param file         - file where is wrote
/// \param bit_string   - input  pointer on bit string
void fprintf_bit_string_HEX    (FILE* file, bit_str* bit_string);

/// Write void in file (HEX form)
/// \param file - pointer on file descriptor
/// \param data - pointer on data
/// \param size - size fprintf data
void fprintf_data_HEX  (FILE* file, void* data, size_t size, int indent = 1);

/// Write bit_string in file in format CHAR
/// \param file         - file where is wrote
/// \param bit_string   - input  pointer on bit string
void fprintf_bit_string_CHAR    (FILE* file, bit_str* bit_string);

/// wrtie bi_string in file on byte format
/// \param file        - file where is wrote
/// \param bit_string  - input pointer on byte string
void write_byte_string           (FILE* file, bit_str* bit_string);

/// Compare a bit form of a two pointers\n
/// Compare size bit
/// \param a - first pointer
/// \param b - second pointer
/// \param size - size compare bits
/// \return true if equal and false else
bool bit_comp(void* a, void* b, size_t size);

/// Convert bit reg name in name string
/// \param reg - bit name register
/// \return string - name register
const char* ConvReginStr(const char reg);

bool bitcat(bit_str* bit_string1, bit_str* bit_string2);
#endif //LIBKALIKHELP_LIBHELPKALIK_H
