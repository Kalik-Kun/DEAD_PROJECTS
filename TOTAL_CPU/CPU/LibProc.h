//
// Created by arlik_null on 18.10.2021.
//

#ifndef CPU_LIBPROC_H
#define CPU_LIBPROC_H

#include <LibStack.h>
#include <MyLibString.h>
#include <libHelpKalik.h>

#define CPU_DUMP


// todo hz why it's don't work
#define CPU_IN_SCANF \
    #ifdef ASM_INT_TYPE    \
        if (scanf("%d", ptr_number) == EOF)  { \
            FUNC_ERROR(error, ERR_IN_SCANF)       \
        }                  \
    #endif                 \
    #ifdef ASM_DOUBLE_TYPE \
        if (scanf("%lf", ptr_number) == EOF)  {\
            FUNC_ERROR(error, ERR_IN_SCANF)\
        }          \
    #endif                 \
    #ifdef ASM_LONGLONG_TYPE                       \
        if (scanf("%lld", ptr_number) == EOF)  {\
            FUNC_ERROR(error, ERR_IN_SCANF)\
        }        \
    #endif               \
    #ifdef ASM_CHAR_TYPE \
        if (scanf("%c", ptr_number) == EOF)  {\
            FUNC_ERROR(error, ERR_IN_SCANF)\
        }\
    #endif


// kekX - it's names registers.
struct Register {
    COMMON_ASM_TYPE kek0 = 0;
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


COMMON_ASM_TYPE* ConvInReg (Register* reg, const char bit_reg, CPU_ERRORS* error = &CPU_ERR);

bool CPUDump(CPU* proc, const char* cpu_log_file = CPU_LOG_FILE_NAME,CPU_ERRORS* error = &CPU_ERR);

#endif //CPU_LIBPROC_H
