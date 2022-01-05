//
// Created by arlik_null on 18.10.2021.
//

#ifndef CPU_LIBPROC_H
#define CPU_LIBPROC_H

#include <LibStack.h>
#include <MyLibString.h>
#include <libHelpKalik.h>
#include <ctime>


#define CPU_DUMP


enum CPU_Modes
{
    NUMBERS     = 1,
    DEFAULT     = 10,
    SHOW        = 100,
    DELETE_PNG  = 1000,
    DELETE_TXT  = 10000,
    DETAILED    = 100000,

    // modes types
    INTEGERS    = 1,
    FLOATS      = 2,
    BOOL        = 3,
    CHAR        = 4,
    UNSIGNED_INTEGERS = 5,
    ANIME       = 9, // undef
};

/// COMPARE_MODULE - allow define rule of compare numbers
/// number - it's number (0..6) 3 bits
/// 2, 1, 0 - bit (210)
/// 0 - bit responsible for equality
/// 1 - bit responsible for less symbol
/// 2 - bit responsible for more symbol
#define COMPARE_MODULE(number) \
    if (pair_elem.first - pair_elem.second < CPU_ACCURACY) { \
        proc->reg.kalik_logic = (number)%2;\
        return true;\
    }                          \
    if (pair_elem.first < pair_elem.second) {                \
        proc->reg.kalik_logic = ((number)>>1)%2;                    \
        return true;\
    }                          \
    if (pair_elem.first > pair_elem.second) {\
        proc->reg.kalik_logic = ((number)>>2)%2;\
        return true;\
    }                   \
    FUNC_ERROR(error, UNDEFINED)\
    return false;


/**
 * When you add new register plese change:
 * 1. Kalik pls think: are you needing this shit register???
 * 2. Write in struct Register these flag with comment(WITH COMMENT why that need)
 * 3. Add register in these place in code:
     * ASM: ConvReg
     * DisASM:
     * CPU: ConvInReg,
 * 4 PLESE don't forgot comment
 **/
struct Register {
    // special program registers (not for users)
    // in logick module i suppose that 0 - false and another number - true
    COMMON_ASM_TYPE kalik_logic = 0;
    COMMON_ASM_TYPE kek0 = 0;


    // registers for users
    COMMON_ASM_TYPE kek1 = 0;
    COMMON_ASM_TYPE kek2 = 0;
    COMMON_ASM_TYPE kek3 = 0;
    COMMON_ASM_TYPE kek4 = 0;
    COMMON_ASM_TYPE kek5 = 0;
    COMMON_ASM_TYPE kek6 = 0;
    COMMON_ASM_TYPE kek7 = 0;
};

struct CPU {
    Skek skek = {};
    Skek kunc_skek = {};

    void* code = nullptr;
    size_t size_code = 0;
    size_t pos_code  = 0;

    void* ram  = nullptr;
    size_t size_ram  = 0;
    size_t pos_ram   = 0;

    Register reg     = {};
};


/// convert bin file into array with code.\n
/// Function ALLOCATE MEMORY and assign allocate buff to a proc.code
/// \param proc - Pointer on your processor. Change only proc.code
/// \param bin_file_name - file name with bin file
/// \param error - errors
/// \return True if operation successfully else False
bool CPUStart(CPU* proc, const char* bin_file_name, CPU_ERRORS* error = &CPU_ERR);

bool CPUPerform(CPU* proc, CPU_ERRORS* error = &CPU_ERR);

bool CPUImplement(CPU* proc, CPU_ERRORS* error = &CPU_ERR);

COMMON_ASM_TYPE FlagImpOut    (CPU* proc, CPU_ERRORS* error = &CPU_ERR);

COMMON_ASM_TYPE PlusImpOut    (CPU* proc, CPU_ERRORS* error = &CPU_ERR);

COMMON_ASM_TYPE SqrtImpOut    (CPU* proc, CPU_ERRORS* error = &CPU_ERR);

COMMON_ASM_TYPE MarkImpOut    (CPU* proc, CPU_ERRORS* error = &CPU_ERR);

COMMON_ASM_TYPE ConstImpOut   (CPU* proc, CPU_ERRORS* error = &CPU_ERR);

COMMON_ASM_TYPE RegImpOut     (CPU* proc, CPU_ERRORS* error = &CPU_ERR);

COMMON_ASM_TYPE NoImpOut      (CPU* proc, CPU_ERRORS* error = &CPU_ERR);


COMMON_ASM_TYPE* FlagImpIn    (CPU* proc, CPU_ERRORS* error = &CPU_ERR);

COMMON_ASM_TYPE* PlusImpIn    (CPU* proc, CPU_ERRORS* error = &CPU_ERR);

COMMON_ASM_TYPE* SqrtImpIn    (CPU* proc, CPU_ERRORS* error = &CPU_ERR);

COMMON_ASM_TYPE* MarkImpIn    (CPU* proc, CPU_ERRORS* error = &CPU_ERR);

COMMON_ASM_TYPE* ConstImpIn   (CPU* proc, CPU_ERRORS* error = &CPU_ERR);

COMMON_ASM_TYPE* RegImpIn     (CPU* proc, CPU_ERRORS* error = &CPU_ERR);

COMMON_ASM_TYPE* NoImpIn      (CPU* proc, CPU_ERRORS* error = &CPU_ERR);

COMMON_ASM_PAIR  EnumImp      (CPU* proc, CPU_ERRORS* error = &CPU_ERR);

// in teory that out class
COMMON_ASM_TYPE* ConvInReg (Register* reg, const char bit_reg, CPU_ERRORS* error = &CPU_ERR);

bool CPUDump(CPU* proc, const char* cpu_log_file = CPU_LOG_FILE_NAME,CPU_ERRORS* error = &CPU_ERR);

/// Graph dump

bool GDump(CPU* proc,
           const char* tittle, const char* filename, const char* pngfilename, size_t mode);

bool ArrGDumper (FILE* file,
                 void* array, size_t size_type, size_t arr_size,
                 size_t mode, const char* tittle = "Arr", size_t number_arr = 0);

void viz_void_elem (void* elem, size_t byte_size, int mode = ANIME);

void viz_void_elem_file (FILE* file ,void* elem, size_t byte_size, size_t mode);


#endif //CPU_LIBPROC_H
