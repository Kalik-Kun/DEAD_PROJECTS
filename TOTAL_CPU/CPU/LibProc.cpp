//
// Created by arlik_null on 18.10.2021.
//

#include "LibProc.h"



bool CPUStart(CPU* proc, const char* bin_file_name, CPU_ERRORS* error) {
    FILE* bin_file = fopen(bin_file_name, "r");
    if (bin_file == nullptr) {
        FUNC_ERROR(error, NULLPTR_WHEN_FILE_OPEN)
    }

    void* info_buffer = calloc(INFO_SIZE, sizeof(char));
    if (info_buffer == nullptr) {
        fclose (bin_file);
        FUNC_ERROR(error, NULLPTR_IN_CALLOC);
    }
    fread(info_buffer, INFO_SIZE, 1, bin_file);

    // if info change it must be change
    if (!bit_comp((void*)&KALIK_SIG, info_buffer, sizeof(int))) {
        free(info_buffer);
        fclose(bin_file);
        FUNC_ERROR(error, NOT_KALIK_FORMAT)
    }
    free(info_buffer);

    size_t buff_size = out_file_size(bin_file_name) - INFO_SIZE;
    void* buffer = calloc(buff_size, sizeof(char));
    if (buffer == nullptr) {
        free(buffer);
        fclose(bin_file);
        FUNC_ERROR(error, NULLPTR_IN_CALLOC)
    }
    fread(buffer, sizeof(char), buff_size, bin_file);
    fclose(bin_file);

    proc->size_code = buff_size;
    proc->code = buffer;

    proc->size_ram = SIZE_RAM_BUFFER;
    proc->ram = calloc(SIZE_RAM_BUFFER, sizeof(COMMON_ASM_TYPE));

    if (proc->ram == nullptr) {
        free(buffer);
        FUNC_ERROR(error, NULLPTR_IN_CALLOC)
    }

    SkekCtor(&proc->skek, sizeof(COMMON_ASM_TYPE));

    #ifdef CPU_DUMP
        CPUDump(proc);
    #endif

    return true;
}

bool CPUPerform(CPU* proc, CPU_ERRORS* error) {
    if (proc == nullptr) {
        FUNC_ERROR(error, NULLPTR);
    }
    if (proc->code == nullptr) {
        FUNC_ERROR(error, NULLPTR)
    }


    while (proc->pos_code < proc->size_code) {
        #ifdef CPU_DUMP
            CPUDump(proc, CPU_LOG_FILE_NAME, error);
        #endif
        if (!CPUImplement(proc, error)) break;
    }

    if (proc->code != nullptr) {
        printf("\x1b[31m ERROR IN PROC: NO COMMAND END\x1b[0m\n");
        #ifdef CPU_DUMP
            CPUDump(proc, CPU_LOG_FILE_NAME,error);
        #endif
        return false;
    }
//    if (CheckRemSkek(&proc->skek)) {
//        printf("\x1b[31m ERROR IN PROC: NO COMMAND RESET FOR REMOVAL SKEK\x1b[0m\n");
//        #ifdef CPU_DUMP
//          CPUDump(proc, error);
//        #endif
//        return false;
//    }


    printf("\x1b[32;1mSUCCESSFULLY END\x1b[0m\n");
    #ifdef CPU_DUMP
        CPUDump(proc, CPU_LOG_FILE_NAME, error);
    #endif
    return true;
}

bool CPUImplement(CPU* proc, CPU_ERRORS* error) {
    if (proc == nullptr) {
        FUNC_ERROR(error, NULLPTR)
    }
    if (proc->code == nullptr) {
        CPUDump(proc, CPU_LOG_FILE_NAME, error);
        FUNC_ERROR(error, CPU_NULLPTR_ON_CODE)
    }

    COMMON_ASM_TYPE first_elem  = 0;
    COMMON_ASM_TYPE second_elem = 0;
    COMMON_ASM_TYPE third_elem  = 0;
    COMMON_ASM_TYPE* ptr_number = nullptr;

    switch (*(char*)((char*)proc->code + proc->pos_code)) {
        case CMD_PUSH:
            // because if don't work with compare type and use sizeof it not so wide
            proc->pos_code += sizeof(char);

            first_elem = FlagImpOut(proc, error);
            CHECK_FOR_ERR(error, false)

            SkekPush(&proc->skek, &first_elem);

            return true;

        case CMD_POP:
            proc->pos_code += sizeof(char);

            ptr_number = FlagImpIn(proc, error);
            CHECK_FOR_ERR(error, false)

            if (ptr_number == nullptr) {
                // only delete
                SkekPop(&proc->skek, &first_elem);
            }

            SkekPop(&proc->skek, ptr_number);

            return true;

        case CMD_IN:
            proc->pos_code += sizeof(char);
            ptr_number = FlagImpIn(proc, error);
            CHECK_FOR_ERR(error, false)

            // i don't what i must do if in haven't argument
            if (ptr_number == nullptr) {
                FUNC_ERROR(error, NULLPTR)
            }

#ifdef ASM_INT_TYPE
            if (scanf("%d", ptr_number) == EOF)  {
                FUNC_ERROR(error, ERR_IN_SCANF)
            }
#endif
#ifdef ASM_DOUBLE_TYPE
            if (scanf("%lf", ptr_number) == EOF)  {
                FUNC_ERROR(error, ERR_IN_SCANF)
            }
#endif
#ifdef ASM_LONGLONG_TYPE
            if (scanf("%lld", ptr_number) == EOF)  {
                FUNC_ERROR(error, ERR_IN_SCANF)
            }
#endif
#ifdef ASM_CHAR_TYPE
            if (scanf("%c", ptr_number) == EOF)  {
                FUNC_ERROR(error, ERR_IN_SCANF)
            }
#endif

        case CMD_OUT:
            proc->pos_code += sizeof(char);
            ptr_number = FlagImpIn(proc, error);
            CHECK_FOR_ERR(error, false)

            if (ptr_number == nullptr) {
                SkekGet(&proc->skek, &first_elem);
#ifdef ASM_INT_TYPE
                printf("\x1b[32;1mTop Skek: %d\x1b[0m\n", first_elem);
#endif
#ifdef ASM_LONGLONG_TYPE
                printf("\x1b[32;1mTop Skek: %lld\x1b[0m\n", first_elem);
#endif
#ifdef ASM_DOUBLE_TYPE
                printf("\x1b[32;1mTop Skek: %lf\x1b[0m\n", first_elem);
#endif
#ifdef ASM_CHAR_TYPE
                printf("\x1b[32;1mTop Skek: %c\x1b[0m\n", first_elem);
#endif
                return true;
            }

#ifdef ASM_INT_TYPE
            printf("\x1b[32;1mTop Skek: %d\x1b[0m\n", *ptr_number);
#endif
#ifdef ASM_LONGLONG_TYPE
            printf("\x1b[32;1mTop Skek: %lld\x1b[0m\n", *ptr_number);
#endif
#ifdef ASM_DOUBLE_TYPE
            printf("\x1b[32;1mTop Skek: %lf\x1b[0m\n", *ptr_number);
#endif
#ifdef ASM_CHAR_TYPE
            printf("\x1b[32;1mTop Skek: %c\x1b[0m\n", *ptr_number);
#endif

            return true;

        case CMD_ADD:
            proc->pos_code += sizeof(char);
            SkekPop(&proc->skek, &first_elem);
            SkekPop(&proc->skek, &second_elem);
            third_elem = (first_elem + second_elem);
            SkekPush(&proc->skek, &third_elem);

            return true;

        case CMD_SUB:
            // todo why i cann't assign var with COMMON_ASM_TYPE third_elem
            proc->pos_code += sizeof(char);

            SkekPop(&proc->skek, &first_elem);
            SkekPop(&proc->skek, &second_elem);
            third_elem = first_elem - second_elem;
            SkekPush(&proc->skek, &third_elem);

            return true;

        case CMD_MULT:
            proc->pos_code += sizeof(char);

            SkekPop(&proc->skek, &first_elem);
            SkekPop(&proc->skek, &second_elem);
            third_elem = first_elem * second_elem;
            SkekPush(&proc->skek, &third_elem);

            return true;

        case CMD_DIV:
            proc->pos_code += sizeof(char);

            SkekPop(&proc->skek, &first_elem);
            SkekPop(&proc->skek, &second_elem);
            if (second_elem < CPU_ACCURACY) {
                FUNC_ERROR(error, CPU_DIVIDE_ON_ZERO);
            }
            third_elem = first_elem / second_elem;
            SkekPush(&proc->skek, &third_elem);
            return true;

        case CMD_LEAP:
            proc->pos_code += sizeof(char);
            proc->pos_code = FlagImpOut(proc, error);

            CHECK_FOR_ERR(error, false)
            return true;

        case CMD_RESET:
            proc->pos_code += sizeof(char);
            printf("todo reset pls\n");
            return true;

        case CMD_END:
            proc->pos_code += sizeof(char);

            SkekDtor(&proc->skek);
            free(proc->code);
            proc->code = nullptr;
            free(proc->ram);
            proc->ram  =  nullptr;
            printf("\nEND PROC\n"
                   "proc->pos_code: %ld\n"
                   "proc->size_code: %ld\n", proc->pos_code, proc->size_code);

            proc->pos_code = proc->size_code;
            //todo i don't know must i use skekdtor there
            return true;

        case CMD_UND:
        FUNC_ERROR(error, UNDEFINED)

        default:
        FUNC_ERROR(error, UNDEFINED)
    }

    FUNC_ERROR(error, UNDEFINED)
}

COMMON_ASM_TYPE* ConvInReg (Register* reg, const char bit_reg, CPU_ERRORS* error) {
    switch (bit_reg) {
        case REG_KEK0:
            return &reg->kek0;
        case REG_KEK1:
            return &reg->kek1;
        case REG_KEK2:
            return &reg->kek2;
        case REG_KEK3:
            return &reg->kek3;
        case REG_KEK4:
            return &reg->kek4;
        case REG_KEK5:
            return &reg->kek5;
        case REG_KEK6:
            return &reg->kek6;
        case REG_KEK7:
            return &reg->kek7;
    }

    FUNC_ERROR_RTRN(error, CPU_REG_DOESNT_EXIST, nullptr)
}

COMMON_ASM_TYPE FlagImpOut   (CPU* proc, CPU_ERRORS* error) {
    if (proc == nullptr) {
        FUNC_ERROR(error, NULLPTR)
    }

    if (proc->code == nullptr) {
        CPUDump(proc, CPU_LOG_FILE_NAME, error);
        FUNC_ERROR(error, CPU_NULLPTR_ON_CODE)
    }

    COMMON_ASM_TYPE number = -1;

    switch (*(char*)((char*)proc->code + proc->pos_code)) {

        case PLUS_FLAG:
            number = PlusImpOut(proc, error);
            CHECK_FOR_ERR(error, false)
            return number;

        case MEM_FLAG:
            number = SqrtImpOut(proc, error);
            CHECK_FOR_ERR(error, false)
            return number;

        case MARK_FLAG:
            number = MarkImpOut(proc, error);
            CHECK_FOR_ERR(error, false)
            return number;

        case CONST_FLAG:
            number = ConstImpOut(proc, error);
            CHECK_FOR_ERR(error, false)
            return number;

        case REG_FLAG:
            number = RegImpOut(proc, error);
            CHECK_FOR_ERR(error, false)
            return number;

        case NO_FLAG:
            // it's error anything
            NoImpOut(proc, error);
            return false;

    }

    FUNC_ERROR(error, CPU_UNDEF_FLAG)
}

COMMON_ASM_TYPE PlusImpOut    (CPU* proc, CPU_ERRORS* error) {
    if (*(char *)((char *)proc->code + proc->pos_code) != PLUS_FLAG) {
        FUNC_ERROR(error, CPU_UNDEF_FLAG)
    }

    proc->pos_code += sizeof(char);

    COMMON_ASM_TYPE number1 = FlagImpOut(proc, error);
    CHECK_FOR_ERR(error, false)

    COMMON_ASM_TYPE number2 = FlagImpOut(proc, error);
    CHECK_FOR_ERR(error, false)

    return number1 + number2;
}

COMMON_ASM_TYPE SqrtImpOut    (CPU* proc, CPU_ERRORS* error) {
    if (*(char*)((char*)proc->code + proc->pos_code) != MEM_FLAG) {
        FUNC_ERROR(error, CPU_UNDEF_FLAG)
    }
    proc->pos_code += sizeof(char);

    COMMON_ASM_TYPE number = FlagImpOut(proc, error);
    CHECK_FOR_ERR(error, false)

    if (number > SIZE_RAM_BUFFER) {
        FUNC_ERROR(error, CPU_OUT_MEM_BROADS);
    }

    return *(COMMON_ASM_TYPE*)((COMMON_ASM_TYPE *)proc->ram + number);
}

COMMON_ASM_TYPE MarkImpOut   (CPU* proc, CPU_ERRORS* error) {
    if (*(char*)((char*)proc->code + proc->pos_code) != MARK_FLAG) {
        FUNC_ERROR(error, CPU_UNDEF_FLAG)
    }

    proc->pos_code += sizeof(char);

    ASM_MARK_TYPE number = *(ASM_MARK_TYPE *)((char*)proc->code + proc->pos_code);

    proc->pos_code += sizeof(ASM_MARK_TYPE);

    return number;
}

COMMON_ASM_TYPE ConstImpOut   (CPU* proc, CPU_ERRORS* error) {
    if (*(char*)((char*)proc->code + proc->pos_code) != CONST_FLAG) {
        FUNC_ERROR(error, CPU_UNDEF_FLAG)
    }

    proc->pos_code += sizeof(char);

    COMMON_ASM_TYPE number = *(COMMON_ASM_TYPE *)((char*)proc->code + proc->pos_code);

    proc->pos_code += sizeof(COMMON_ASM_TYPE);

    return number;
}

COMMON_ASM_TYPE RegImpOut   (CPU* proc, CPU_ERRORS* error) {
    if(*(char*)((char*)proc->code + proc->pos_code) != REG_FLAG) {
        FUNC_ERROR(error, CPU_UNDEF_FLAG)
    }

    proc->pos_code += sizeof(char);

    COMMON_ASM_TYPE number = *ConvInReg(&proc->reg, *(char*)((char*)proc->code + proc->pos_code));
    CHECK_FOR_ERR(error, false)

    proc->pos_code += sizeof(COMMON_ASM_TYPE);

    return number;
}

COMMON_ASM_TYPE NoImpOut      (CPU* proc, CPU_ERRORS* error) {
    if (*(char*)((char*)proc->code + proc->pos_code) == NO_FLAG) {
        FUNC_ERROR(error, CPU_NO_IN_OUTPUT)
    }

    FUNC_ERROR(error, CPU_UNDEF_FLAG)
}

COMMON_ASM_TYPE* FlagImpIn   (CPU* proc, CPU_ERRORS* error) {
    if (proc == nullptr) {
        FUNC_ERROR_RTRN(error, NULLPTR, nullptr)
    }
    if (proc->code == nullptr) {
        FUNC_ERROR_RTRN(error, NULLPTR, nullptr)
    }

    COMMON_ASM_TYPE* number = nullptr;

    switch (*(char*)((char*)proc->code + proc->pos_code)) {

        case PLUS_FLAG:
            // error anything
            PlusImpIn(proc, error);
            return nullptr;

        case MEM_FLAG:
            number = SqrtImpIn(proc, error);
            CHECK_FOR_ERR(error, nullptr)
            return number;

        case MARK_FLAG:
            // error anything
            MarkImpIn(proc, error);
            return nullptr;

        case CONST_FLAG:
            // error anything
            ConstImpIn(proc, error);
            return nullptr;

        case REG_FLAG:
            number = RegImpIn(proc, error);
            CHECK_FOR_ERR(error, nullptr)
            return number;

        case NO_FLAG:
            // it's not error
            NoImpIn(proc, error);
            return nullptr;

    }

    FUNC_ERROR_RTRN(error, CPU_UNDEF_FLAG, nullptr)
}

COMMON_ASM_TYPE* PlusImpIn    (CPU* proc, CPU_ERRORS* error) {
    if (*(char *)((char *)proc->code + proc->pos_code) == PLUS_FLAG) {
        FUNC_ERROR_RTRN(error, CPU_PLUS_IN_INPUT, nullptr)
    }

    FUNC_ERROR_RTRN(error, CPU_UNDEF_FLAG, nullptr)
}

COMMON_ASM_TYPE* SqrtImpIn    (CPU* proc, CPU_ERRORS* error) {
    if (*(char *)((char *)proc->code + proc->pos_code) != MEM_FLAG) {
        FUNC_ERROR_RTRN(error, CPU_UNDEF_FLAG, nullptr)
    }

    proc->pos_code += sizeof(char);

    COMMON_ASM_TYPE number = FlagImpOut(proc, error);
    CHECK_FOR_ERR(error, nullptr)

    if (number > SIZE_RAM_BUFFER) {
        FUNC_ERROR_RTRN(error, CPU_OUT_MEM_BROADS, nullptr)
    }

    return (COMMON_ASM_TYPE*)((COMMON_ASM_TYPE *)proc->ram + number);
}

COMMON_ASM_TYPE* MarkImpIn    (CPU* proc, CPU_ERRORS* error) {
    if (*(char *)((char *)proc->code + proc->pos_code) == MARK_FLAG) {
        FUNC_ERROR_RTRN(error, CPU_MARK_IN_INPUT, nullptr)
    }

    FUNC_ERROR_RTRN(error, CPU_UNDEF_FLAG, nullptr)
}

COMMON_ASM_TYPE* ConstImpIn   (CPU* proc, CPU_ERRORS* error) {
    if (*(char *)((char *)proc->code + proc->pos_code) == CONST_FLAG) {
        FUNC_ERROR_RTRN(error, CPU_CONST_IN_INPUT, nullptr)
    }
    FUNC_ERROR_RTRN(error, CPU_UNDEF_FLAG, nullptr)
}

COMMON_ASM_TYPE* RegImpIn     (CPU* proc, CPU_ERRORS* error) {
    if (*(char *)((char *)proc->code + proc->pos_code) != REG_FLAG) {
        FUNC_ERROR_RTRN(error, CPU_UNDEF_FLAG, nullptr)
    }

    proc->pos_code += sizeof(char);

    COMMON_ASM_TYPE* number = ConvInReg(&proc->reg, *(char*)((char*)proc->code + proc->pos_code), error);
    CHECK_FOR_ERR(error, nullptr)

    proc->pos_code += sizeof(char);
    return number;
}

COMMON_ASM_TYPE* NoImpIn      (CPU* proc, CPU_ERRORS* error) {
    if (*(char *)((char *)proc->code + proc->pos_code) != NO_FLAG) {
        FUNC_ERROR_RTRN(error, CPU_UNDEF_FLAG, nullptr)
    }
    proc->pos_code += sizeof(char);
    // it's not error
    return nullptr;
}


bool CPUDump(CPU* proc, const char* cpu_log_file, CPU_ERRORS* error) {
    if (proc == nullptr) {
        FUNC_ERROR(error, NULLPTR)
    }

    FILE* logfile = fopen(cpu_log_file, "a");
    fprintf(logfile, "DUMP PROC\n\n");

    fprintf(logfile, "SIZE_CODE: %ld\n", proc->size_code);
    fprintf(logfile, "POS:       %ld\n", proc->pos_code);
    fprintf(logfile, "SIZE_RAM:  %ld\n", proc->size_ram);
    fprintf(logfile, "IP:        %ld\n", proc->pos_ram);

    if (CheckRemSkek(&proc->skek)) {
        fprintf(logfile, "SKEK WAS REMOVAL\n");
    }
    else {
        fprintf(logfile, "SKEK:\n");
        //todo i don't know use another log file for skek or not
        SkekDump(&proc->skek, DEB_ELEM("SKEK_DUMP_IN_CPU"));
    }

    if (proc->code == nullptr) {
        fprintf(logfile, "NULLPTR_ON_CODE\n");
    }
    else {
        fprintf(logfile, "CODE:\n");
        for(size_t byte = 0; byte < proc->size_code; byte ++) {
            fprintf(logfile, "data[%ld] = %02X\n", byte, *((char*)proc->code + byte));
        }
        fprintf(logfile, "\n");
    }

    if (proc->ram == nullptr) {
        fprintf(logfile, "NULLPTR_ON_RAM\n");
    }
    else {
        fprintf(logfile, "RAM:\n");
        for(size_t byte = 0; byte < proc->size_ram; byte ++) {
            fprintf(logfile, "data[%ld] = %X\n", byte, *(COMMON_ASM_TYPE*)((COMMON_ASM_TYPE *)proc->ram + byte));
        }
        fprintf(logfile, "\n");
    }

    fprintf(logfile, "REGISTERS:\n");
    fprintf(logfile, "kek0: %d\n"
           "kek1: %d\n"
           "kek2: %d\n"
           "kek3: %d\n"
           "kek4: %d\n"
           "kek5: %d\n"
           "kek6: %d\n"
           "kek7: %d\n",
           proc->reg.kek0, proc->reg.kek1, proc->reg.kek2, proc->reg.kek3,
           proc->reg.kek4, proc->reg.kek5, proc->reg.kek6, proc->reg.kek7);
    fprintf(logfile, "\n");

    return true;
}


