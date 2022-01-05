//
// Created by arlik_null on 24.10.2021.
//

#include "Disassembler.h"



bool disassembler(const char* program_file_name, const char* binfile_name, CPU_ERRORS* error) {
    FILE* prog_file = openfile(program_file_name, "w", error);
    if (prog_file == nullptr) return false;
    FILE* bin_file  = openfile(binfile_name, "r", error);
    if (bin_file == nullptr) {
        fclose(bin_file);
        return false;
    }

    void* info_buffer = calloc(INFO_SIZE, sizeof(char));
    if (info_buffer == nullptr) {
        fclose (bin_file);
        fclose (prog_file);
        FUNC_ERROR(error, NULLPTR_IN_CALLOC)
    }

    fread(info_buffer, INFO_SIZE, 1, bin_file);
    if (!bit_comp((void*)&KALIK_SIG, info_buffer, sizeof(int))) {
        free(info_buffer);
        fclose(bin_file);
        fclose(prog_file);
        FUNC_ERROR(error, NOT_KALIK_FORMAT)
    }

    // todo there may be a wrong in \0 in info buffer(info_buffer have \0 in end?)
    size_t buff_size = out_file_size(binfile_name) - INFO_SIZE;
    void* buffer = calloc(buff_size, sizeof(char));
    if (buffer == nullptr) {
        free(info_buffer);
        fclose(bin_file);
        fclose(prog_file);
        FUNC_ERROR(error, NULLPTR_IN_CALLOC)
    }
    fread(buffer, sizeof(char), buff_size, bin_file);

    size_t numb_byte = 0;

    const char* COMMAND   = "COMMANDS";
    const char* HEX_FORM  = "HEX_FORM";
    fprintf(prog_file, "START FILE\n"
                       "%-*s %s\n",
            MAX_INDENT, COMMAND,
            HEX_FORM);

    for (size_t numb_line = 0;
         *(char*)((char*)buffer + numb_byte) != '\0' && numb_byte <= buff_size;
         numb_line ++) {
        if (!CmdShow(buffer, &numb_byte, prog_file, error)) break;
    }

    free(buffer);
    free(info_buffer);
    fclose(prog_file);
    fclose(bin_file);
    return true;
}

bool CmdShow(void* buffer, size_t* numb_byte, FILE* prog_file, CPU_ERRORS* error) {
    if (prog_file == nullptr) {
        FUNC_ERROR(error, NULLPTR)
    }

    size_t start_byte = *numb_byte;

    printf("buffer: %02X\n", *(char*)((char*)buffer + *numb_byte));

    switch (*(char*)((char*)buffer + *numb_byte)) {
        case CMD_PUSH:
            PRINT_COM_WITH_FLAGS(PUSH)
            return true;

        case CMD_POP:
            PRINT_COM_WITH_FLAGS(POP)
            return true;

        case CMD_IN:
            PRINT_COM_WITH_FLAGS(IN)
            return true;

        case CMD_OUT:
            PRINT_COM_WITH_FLAGS(OUT)
            return true;

        case CMD_ADD:
            PRINT_COM(ADD)
            return true;

        case CMD_SUB:
            PRINT_COM(SUB)
            return true;

        case CMD_MULT:
            PRINT_COM(MULT)
            return true;

        case CMD_DIV:
            PRINT_COM(DIV)
            return true;

        case CMD_EKOMP:
            PRINT_COM_WITH_FLAGS(EKOMP)
            return true;
        case CMD_NEKOMP:
            PRINT_COM_WITH_FLAGS(NEKOMP)
            return true;

        case CMD_LKOMP:
            PRINT_COM_WITH_FLAGS(LKOMP)
            return true;
        case CMD_NLKOMP:
            PRINT_COM_WITH_FLAGS(NLKOMP)
            return true;
        case CMD_ELKOMP:
            PRINT_COM_WITH_FLAGS(ELKOMP)
            return true;

        case CMD_MKOMP:
            PRINT_COM_WITH_FLAGS(MKOMP)
            return true;
        case CMD_NMKOMP:
            PRINT_COM_WITH_FLAGS(NMKOMP)
            return true;
        case CMD_EMKOMP:
            PRINT_COM_WITH_FLAGS(EMKOMP)
            return true;

        case CMD_LEAP:
            PRINT_COM_WITH_FLAGS(LEAP)
            return true;

        case CMD_LLEAP:
            PRINT_COM_WITH_FLAGS(LLEAP)
            return true;

        case CMD_FRIDAY_LEAP:
            PRINT_COM_WITH_FLAGS(FRIDAY_LEAP)
            return true;

        case CMD_CALL:
            PRINT_COM_WITH_FLAGS(CALL)
            return true;
        case CMD_KUNC:
            PRINT_COM(KUNC)
            return true;
        case CMD_EKUNC:
            PRINT_COM(EKUNC)
            return true;

        case CMD_RESET:
            PRINT_COM(RESET)
            return true;

        case CMD_END:
            PRINT_COM(END)
            return true;

        case CMD_UND:
        FUNC_ERROR(error, UNDEFINED)

        default:
        FUNC_ERROR(error, UNDEFINED)
    }

    FUNC_ERROR(error, UNDEFINED)
}


bool FlagShow(void* buffer,
                size_t* numb_byte, FILE* prog_file,
                CPU_ERRORS* error) {
    if (buffer == nullptr) {
        FUNC_ERROR(error, NULLPTR)
    }

    switch (*(char*)((char*)buffer + *numb_byte))  {
        case NO_FLAG:
            return NoShow(buffer, numb_byte, prog_file, error);

        case MARK_FLAG:
            return MarkShow(buffer, numb_byte, prog_file, error);

        case CONST_FLAG:
            return ConstShow(buffer, numb_byte, prog_file, error);

        case REG_FLAG:
            return RegShow(buffer, numb_byte, prog_file, error);

        case MEM_FLAG:
            return SqrtShow(buffer, numb_byte, prog_file, error);

        case PLUS_FLAG:
            return PlusShow(buffer, numb_byte, prog_file, error);

        case ENUM_FLAG:
            return EnumShow(buffer, numb_byte, prog_file, error);

    }

    return false;
}


bool NoShow(void* buffer,
            size_t* numb_byte, FILE* prog_file,
            CPU_ERRORS* error) {
    if (*(char*)((char*)buffer + *numb_byte) != NO_FLAG) return false;
    *numb_byte += sizeof(char);
    return true;
}

bool MarkShow (void* buffer,
               size_t* numb_byte, FILE* prog_file,
               CPU_ERRORS* error) {
    if (*(char*)((char*)buffer + *numb_byte) != MARK_FLAG) return false;
    (*numb_byte) += sizeof(char);

    // that i think ASM_MARK_TYPE is long long
    fprintf(prog_file, "%lld", *(ASM_MARK_TYPE*)((char*)buffer + *numb_byte));

    *numb_byte += sizeof(ASM_MARK_TYPE);
    return true;
}

bool ConstShow(void* buffer,
               size_t* numb_byte, FILE* prog_file,
               CPU_ERRORS* error) {
    if (*(char*)((char*)buffer + *numb_byte) != CONST_FLAG) return false;
    *numb_byte += sizeof(char);
#ifdef ASM_INT_TYPE
    fprintf(prog_file, "%d", *(COMMON_ASM_TYPE *)((char*)buffer + *numb_byte));
#endif
#ifdef ASM_DOUBLE_TYPE
    fprintf(prog_file, "%lf", *(COMMON_ASM_TYPE *)((char*)buffer + *numb_byte));
#endif

    *numb_byte += sizeof(COMMON_ASM_TYPE);
    return true;
}

bool RegShow(void* buffer,
             size_t* numb_byte, FILE* prog_file,
             CPU_ERRORS* error) {
    if (*(char*)((char*)buffer + *numb_byte) != REG_FLAG) return false;
    *numb_byte += sizeof(char);

    fprintf(prog_file, "%s", ConvReginStr(*(char*)((char*)buffer + *numb_byte)));

    *numb_byte += sizeof(char);
    return true;
}

bool PlusShow(void* buffer,
              size_t* numb_byte, FILE* prog_file,
              CPU_ERRORS* error) {
    if (*(char*)((char*)buffer + *numb_byte) != PLUS_FLAG) return false;

    *numb_byte += sizeof(char);
    if (!FlagShow(buffer, numb_byte, prog_file, error)) return false;
    fprintf(prog_file, " + ");
    if (!FlagShow(buffer, numb_byte, prog_file, error)) return false;

    return true;
}

bool SqrtShow(void* buffer,
              size_t* numb_byte, FILE* prog_file,
              CPU_ERRORS* error) {
    if (*(char*)((char*)buffer + *numb_byte) != MEM_FLAG) return false;

    *numb_byte += sizeof(char);

    fprintf(prog_file, "[");
    if (!FlagShow(buffer, numb_byte, prog_file, error)) return false;
    fprintf(prog_file, "]");


    return true;
}

bool EnumShow (void* buffer,
             size_t* numb_byte, FILE* prog_file,
             CPU_ERRORS* error) {


    if (*(char*)((char*)buffer + *numb_byte) != ENUM_FLAG) return false;

    *numb_byte += sizeof(char);
    if (!FlagShow(buffer, numb_byte, prog_file, error)) return false;
    fprintf(prog_file, " , ");
    if (!FlagShow(buffer, numb_byte, prog_file, error)) return false;

    return true;
}
