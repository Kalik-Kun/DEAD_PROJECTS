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
    if(*(error) != UNDEFINED) return return_value;

/// Processor commands
/**
 * When you add command plese change:
 * 1. Kalik pls think: are you needing this shit comand???
 * 2. Write in ASM_COMMANDS these comand with comment
 * 3. Add comand in these palce in code
     * ASM: ConvCom (onlu cmp) and ConInBin (add name with define)
     * DisASM: nahui u mena dump asemblere.... (CmdShow)
     * CPU: CPUImplement (add comand and write recognize with implement) and
 * 3. PLESE don't forgot comment
 *
 **/

enum ASM_COMMANDS {

    /// OWN ASM COMMANDS

    CMD_END = 1,    // END PROC (HAVE sizeof(char) bytes in memory)
    CMD_RESET,      // RESET SKEK (HAVE sizeof(char) bytes in memory)

    /// INTERACTION WITH SKEK

    /* PUSH element in top skek
    * (HAVE sizeof(char) + sizeof(char) + sizeof(data) bytes in memory)
    * 1 byte - it's spec operation
    * 2 byte - it desribe data
    * 3 byte - it's data
    * EXAMPLE:
    * PUSH 10      - push 10 in top skek
    * PUSH KEK1    - push register value in top skek
    * PUSH KEK1 + 10 - push register value + 10 in skek
    */
    CMD_PUSH,

    /* POP element in top skek and assigns element(reg or ram)
     * HAVE sizeof(char) + sizeof(char) + sizeof(data)
     * 1 byte - it's spec operation
     * 2 byte - it describe data
     * 3 byte - it's data
     * EXAMPLE:
     * POP       - only delete  top elem in skek
     * POP KEK0  - delete elem in skek and assign register name
     * POP [10]  - delete elem in skek and assign memory
    */
    CMD_POP,

    /// INTERACTION WITH USER

    /* input number (scanf) and put in top skek
    * May be with register and ram (IN or IN KEK0 or IN [10])
    * (HAVE sizeof(char) + sizeof(char) + sizeof(data))
    * 1 byte - it's spec operation
    * 2 byte - it desribe data
    * 3 byte - data (may be not exist)
    * EXAMPLE:
    * IN
    * IN KEK0
    */
    CMD_IN,

    /* Output top elem or registers ot ram
     * EXAMPLE:
     * OUT      - print top elem in skek
     * OUT KEK0 - print value register KEK)
     * OUT [10] - print ram with 10 indentificator
    */
    CMD_OUT,

    /// MATH OPERATIONS

    // ADD top and top-1 elements (HAVE sizeof(char) bytes in memory)
    CMD_ADD,

    // subtract top and top-1 elements (HAVE sizeof(char) bytes in memory)
    CMD_SUB,

    // MULTIPLY top and top-1 elements
    CMD_MULT,

    // DIVIDE top and top-1 elements
    CMD_DIV,

    /// KALIK COMPARES

    /* EKOMP - EQUAL KALIK COMPARE.
     * EKOMP - comapre 2 variable,
     * if FIRST EQUAL SECOND that
     * write in KALIK_LOGIC register 1 else write 0(default value).
     *
     * HAVE sizeof(char) + sizeof(char) + sizeof(data)
     * 1 byte - it's spec operation
     * 2 byte - it discribe data ( MUST BE  ENUM_FLAG, else ERROR)
     * 3 bite - data
     *
     * EXAMPLE:
     * EKOMP 1, 2       - compare 1 and 2 (write in KALIK_LOGIC 0)
     * EKOMP 2, 1       - compare 2 and 1 (write in KALIK_LOGIC 0)
     * EKOMP 0, 0       - compare 0 and 0 (write in KALIK_LOGIC 1)
     * EKOPM KEK0, KEK1 - compare KEK0 and KEK1
     */
    CMD_EKOMP,

    /* NEKOMP - NOT EQUAL KALIK COMPARE.
     * NEKOMP - comapre 2 variable,
     * if FIRST NOT EQUAL SECOND that
     * write in KALIK_LOGIC register 1 else write 0(default value).
     *
     * HAVE sizeof(char) + sizeof(char) + sizeof(data)
     * 1 byte - it's spec operation
     * 2 byte - it discribe data ( MUST BE  ENUM_FLAG, else ERROR)
     * 3 bite - data
     *
     * EXAMPLE:
     * NEKOMP 1, 2       - compare 1 and 2 (write in KALIK_LOGIC 1)
     * NEKOMP 2, 1       - compare 2 and 1 (write in KALIK_LOGIC 1)
     * NEKOMP 0, 0       - compare 0 and 0 (write in KALIK_LOGIC 0)
     * NEKOPM KEK0, KEK1 - compare KEK0 and KEK1
     */
    CMD_NEKOMP,

    /* LKOMP - LESS KALIK COMPARE.
     * LKOMP - comapre 2 value,
     * if FIRST LESS than SECOND veriable that
     * write in KALIK_LOGIC register 1 else write 0(default value).
     *
     * HAVE sizeof(char) + sizeof(char) + sizeof(data)
     * 1 byte - it's spec operation
     * 2 byte - it discribe data ( MUST BE  ENUM_FLAG, else ERROR)
     * 3 bite - data
     *
     * EXAMPLE:
     * LKOMP 1, 2       - compare 1 and 2 (write in KALIK_LOGIC 1)
     * LKOMP 2, 1       - compare 2 and 1 (write in KALIK_LOGIC 0)
     * LKOMP 0, 0       - compare 0 and 0 (write in KALIK_LOGIC 0)
     * LKOPM KEK0, KEK1 - compare KEK0 and KEK1
     */
    CMD_LKOMP,

    /* NLKOMP - NOT LESS KALIK COMPARE.
     * NLKOMP - comapre 2 value,
     * if FIRST NOT LESS than SECOND veriable that
     * write in KALIK_LOGIC register 1 else write 0(default value).
     *
     * HAVE sizeof(char) + sizeof(char) + sizeof(data)
     * 1 byte - it's spec operation
     * 2 byte - it discribe data ( MUST BE  ENUM_FLAG, else ERROR)
     * 3 bite - data
enum Parametors
{

};
     *
     * EXAMPLE:
     * NLKOMP 1, 2       - compare 1 and 2 (write in KALIK_LOGIC 0)
     * NLKOMP 2, 1       - compare 2 and 1 (write in KALIK_LOGIC 1)
     * NLKOMP 0, 0       - compare 0 and 0 (write in KALIK_LOGIC 1)
     * NLKOPM KEK0, KEK1 - compare KEK0 and KEK1
     */
    CMD_NLKOMP,

    /* ELKOMP - EQUAL or LESS KALIK COMPARE.
     * ELKOMP - comapre 2 value,
     * if FIRST EQUAL or LESS than SECOND veriable that
     * write in KALIK_LOGIC register 1 else write 0(default value).
     *
     * HAVE sizeof(char) + sizeof(char) + sizeof(data)
     * 1 byte - it's spec operation
     * 2 byte - it discribe data ( MUST BE  ENUM_FLAG, else ERROR)
     * 3 bite - data
     *
     * EXAMPLE:
     * ELKOMP 1, 2       - compare 1 and 2 (write in KALIK_LOGIC 1)
     * ELKOMP 2, 1       - compare 2 and 1 (write in KALIK_LOGIC 0)
     * ELKOMP 0, 0       - compare 0 and 0 (write in KALIK_LOGIC 1)
     * ELKOPM KEK0, KEK1 - compare KEK0 and KEK1
     */
    CMD_ELKOMP,

    /* MKOMP - MORE KALIK COMPARE.
     * MKOMP - comapre 2 value,
     * if first MORE than second veriable that
     * write in KALIK_LOGIC register 1 else write 0(default value).
     *
     * HAVE sizeof(char) + sizeof(char) + sizeof(data)
     * 1 byte - it's spec operation
     * 2 byte - it discribe data ( MUST BE  ENUM_FLAG, else ERROR)
     * 3 bite - data
     *
     * EXAMPLE:
     * MKOMP 1, 2       - compare 1 and 2 (write in KALIK_LOGIC 0)
     * MKOMP 2, 1       - compare 2 and 1 (write in KALIK_LOGIC 1)
     * MKOMP 0, 0       - compare 0 and 0 (write in KALIK_LOGIC 0)
     * MKOPM KEK0, KEK1 - compare KEK0 and KEK1
     */
    CMD_MKOMP,

    /* NMKOMP - NOT MORE KALIK COMPARE.
     * NMKOMP - comapre 2 value,
     * if first NOT MORE than second veriable that
     * write in KALIK_LOGIC register 1 else write 0(default value).
     *
     * HAVE sizeof(char) + sizeof(char) + sizeof(data)
     * 1 byte - it's spec operation
     * 2 byte - it discribe data ( MUST BE  ENUM_FLAG, else ERROR)
     * 3 bite - data
     *
     * EXAMPLE:
     * NMKOMP 1, 2       - compare 1 and 2 (write in KALIK_LOGIC 1)
     * NMKOMP 2, 1       - compare 2 and 1 (write in KALIK_LOGIC 0)
     * NMKOMP 0, 0       - compare 0 and 0 (write in KALIK_LOGIC 1)
     * NMKOPM KEK0, KEK1 - compare KEK0 and KEK1
     */
    CMD_NMKOMP,

    /* EMKOMP - EQUAL or MORE KALIK COMPARE.
     * EMKOMP - comapre 2 value,
     * if first EQUAL or MORE than second veriable that
     * write in KALIK_LOGIC register 1 else write 0(default value).
     *
     * HAVE sizeof(char) + sizeof(char) + sizeof(data)
     * 1 byte - it's spec operation
     * 2 byte - it discribe data ( MUST BE  ENUM_FLAG, else ERROR)
     * 3 bite - data
     *
     * EXAMPLE:
     * EMKOMP 1, 2       - compare 1 and 2 (write in KALIK_LOGIC 0)
     * EMKOMP 2, 1       - compare 2 and 1 (write in KALIK_LOGIC 1)
     * EMKOMP 0, 0       - compare 0 and 0 (write in KALIK_LOGIC 1)
     * EMKOPM KEK0, KEK1 - compare KEK0 and KEK1
     */
    CMD_EMKOMP,

    /// JUMPS

    /* LEAP - jump on certain bit
     *
     * HAVE sizeof(char) + sizeof(char) + sizeof(data)
     * 1 byte - it's spec operation
     * 2 byte - it desribe data (usually ENUM_FLAG)
     *
     * EXAMPLE:
     * LEAP 5        - jump on 5 bit in code
     * LEAP :KALIK   - jump on bit with value in this mark
     * LEAP [:KLAIK] - jump on bit with value in this ram
    */
    CMD_LEAP,

    /* LLEAP(Logical leap) - jump on certain bit if KALIK_LOGIC == 1
     *
     * HAVE sizeof(char) + sizeof(char) + sizeof(data)
     * 1 byte - it's spec operation
     * 2 byte - it desribe data (usually MARK_FLAG)
     * 3 byte - data
     *
     * EXAMPLE:
     * LLEAP 5        - jump on 5 bit in code
     * LLEAP :KALIK   - jump on bit with value in this mark
     * LLEAP [:KLAIK] - jump on bit with value in this ram
    */
    CMD_LLEAP,


    /// FUN
    /* FRIDAY_LEAP - jump on certain bit if today friday
     *
     * HAVE sizeof(char) + sizeof(char) + sizeof(data)
     * 1 byte - it's spec operation
     * 2 byte - it desribe data (usually MARK_FLAG)
     * 3 byte - data
     *
     * EXAMPLE:
     * FRIDAY_LEAP 5        - jump on 5 bit in code
     * FRIDAY_LEAP :KALIK   - jump on bit with value in this mark
     * FRIDAY_LEAP [:KLAIK] - jump on bit with value in this ram
    */
    CMD_FRIDAY_LEAP,

    /* CALL - it's function, work as LEAP but when function ending that return to call
     * When CALL jump on function mark, program create in kfunc_stack position of CALL
     * CALL (Mark)
     *
     * HAVE sizeof(char) + sizeof(char) + sizeof(data)
     * 1 byte - it's spec operation
     * 2 byte - it desribe data (usually MARK_FLAG)
     * 3 byte - data
     *
     * EXAMPLE:
     * CALL :ANIME          - jump on Mark anime()
    */
    CMD_CALL,

    /* KUNC - KALIK FUNCTION
     * KUNC in ASEMBLER define new mark name (mark name is behind KNUC)
     *      and write KUNC indeficator in bit_string
     * KUNC in CPU return error if processor stopped at this command
     *
     * HAVE sizeof(char) + sizeof(char) + sizeof(data)
     * 1 byte - it's spec operation
     * 2 byte - it desribe data (usually MARK_FLAG)
     * 3 byte - data
     *
     * EXAMPLE:
     * :anime KUNC
     * ...
     * EKUNC
    */
    CMD_KUNC,


    /* EKUNC - END KALIK FUNCTION
     * EKUNC in ASSEMBLER do nothing only write command on bit code
     * EKUNC - in CPU go to last mark in KUNC stack
     *
     * HAVE sizeof(char)
     * 1 byte - it's spec operation
     *
     * EXAMPLE:
     * KUNC :anime
     * ...
     * EKUNC
    */
    CMD_EKUNC,

    // UNDEFINED_SKEK
    CMD_UND = CHAR_MAX,
};

/// ASM FLAGS

/**
 * When you add flag plese change:
 * 1. Kalik pls think: are you needing this shit flag???
 * 1.5. KLAIK FLAG ISN'T A JOKE, THAT REAL SHIT, PLS THINK
 * 2. Write in ASM_FLAGS these flag with comment(WITH COMMENT)
 * 3. Write function like: NoFlag and you want thath these flag are using in all command,
 * you need add these func in SeriesFlag
 * 4. Add flag in these palce in code
     * ASM: SeriesFlag and add these function
     * DisASM: FlagShow
     * CPU: FlagImpOut, FlagImpIn
 * 5. PLESE don't forgot comment
 *
 **/
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

    // if use , (enumerate data) EXAMPLE: EKOMP 1, 2
    ENUM_FLAG   = 64,
};


enum CPU_REGISTERS {
    REG_KALIK_LOGIC,
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
    CPU_ERROR_IN_SKEK,
    CPU_REG_DOESNT_EXIST,
    CPU_CALL_NO_FUNCTION,
    CPU_FORBIDDEN_USAGE_ENUM,

    //ASM ERRORS

    ASM_WRONG_FORMAT,       // Wrong format
    ASM_LACK_SQRT_BRACKET,  // Lack sqrt bracket in input file
    ASM_NOT_MATCH_TYPE,     // define unknown type
    ASM_SECONDLY_MARK_DEFENITION,
    ASM_ERROR_IN_DUMP,      // Dump return false
    ASM_MARK_NAMES_SKEK_ERROR,
    ASM_ERROR_IN_SKEK,
    ASM_MARK_DONT_DEF,
    ASM_WRONG_COMARE_FORMAT,
    ASM_PLUS_WITHOUT_ARGUMENT,
    ASM_EMUN_WITHOUT_ARGUMENT,
    ASM_NOT_ALL_SYMB_RECOGNIZE,

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
/// \param index_str - number this string in array (arr_bit_str)
/// \param data    - pointer on data
/// \param start_byte - bit(i know) where string brgin in (array) arr_bit_str
/// \param size    - size this bit_string
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

/// COMMON_ASM_PAIR - only pair for work
/// \param first  - first number (COMMON_ASM_TYPE)
/// \param second - second number  (COMMON_ASM_TYPE)
struct COMMON_ASM_PAIR {
    COMMON_ASM_TYPE first  = 0;
    COMMON_ASM_TYPE second = 0;
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
extern const char* CLEAN_PROGRAM_FILE_NAME;
extern const char* DISASM_FILE_NAME;

extern const char* ASM_LOG_FILE_NAME;
extern const char* ASM_SKEK_LOG_FILE_NAME;

extern const char* CPU_LOG_FILE_NAME;
extern const char* CPU_SKEK_LOG_FILE_NAME;

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
