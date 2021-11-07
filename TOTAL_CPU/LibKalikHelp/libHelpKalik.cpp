#include "libHelpKalik.h"

#include <iostream>

CPU_ERRORS CPU_ERR = UNDEFINED;
CPU_ERRORS ASM_ERR = UNDEFINED;

const int KALIK_SIG          = 0xAB0BA;
const int INFO_SIZE          = sizeof(int);

const double CPU_ACCURACY        = 1e-10;

const char* BIN_FILE_NAME     = "bin_file.txt";
const char* PROGRAM_FILE_NAME = "prog.txt";
const char* LOG_FILE_NAME     = "ASMLogFile.txt";
const char* CPU_LOG_FILE_NAME = "CPULogFile.txt";

const int MAX_INDENT          = 25;

const ASM_MARK_TYPE ASM_MAGIC_NUMBER = 0xD0D0;

const long SIZE_RAM_BUFFER = CHAR_MAX;

FILE* openfile(const char* file_name, const char* spec, CPU_ERRORS* error) {
    FILE* file = fopen(file_name, spec);
    if (file == nullptr) {
        printf("\x1b[31m\n"
               "ERROR IN OPEN FILE: %s\n"
               "\x1b[0m", file_name);
        *error = NULLPTR_WHEN_FILE_OPEN;
        SMALL_DUMP(NULLPTR_WHEN_FILE_OPEN);
        return nullptr;
    }
    return file;
}

void fprintf_bit_string_HEX (FILE* file, bit_str* bit_string) {
    for (long numb_byte = 0; numb_byte < bit_string->size; numb_byte ++) {
        fprintf(file, "%02X",
                *((char *)  bit_string->data + numb_byte));
    }
}

void fprintf_data_HEX  (FILE* file, void* data, size_t size, int indent) {

    fprintf(file, "%-*c", indent, ' ');

    for (long numb_byte = 0; numb_byte < size; numb_byte++) {
        fprintf(file, "%02X",
                *((char*)data + numb_byte));
    }
}

void fprintf_bit_string_CHAR (FILE* file, bit_str* bit_string) {
    for (long numb_byte = 0; numb_byte < bit_string->size; numb_byte ++) {
        fprintf(file, "%c",
                *((char *)  bit_string->data + numb_byte));
    }
}

void write_byte_string (FILE* file, bit_str* bit_string) {
    fwrite (bit_string->data, sizeof(char), bit_string->size, file);
}


bool bit_comp(void* a, void* b, size_t size) {

    for (int i = 0; i < size; i++) {
//        printf("%02X %02X\n", *((char*) a + i), *((char*) b + i));
        if (*((char*) a + i) != *((char*) b + i)) {
            return false;
        }
    }
    return true;
}

const char* ConvReginStr(const char reg) {
    switch (reg) {
        case REG_KEK0:
            return "KEK0";
        case REG_KEK1:
            return "KEK1";
        case REG_KEK2:
            return "KEK2";
        case REG_KEK3:
            return "KEK3";
        case REG_KEK4:
            return "KEK4";
        case REG_KEK5:
            return "KEK5";
        case REG_KEK6:
            return "KEK6";
        case REG_KEK7:
            return "KEK7";
        default:
            return "\x1b[31mERROR IN REGISTERS\x1b[0m";
    }
}

bool bitcat(bit_str* bs1, bit_str* bs2) {
    bs1->data = realloc(bs1->data, bs1->size + bs2->size);
    if (bs1->data == nullptr) return false;

    for (long i = bs1->size; i < bs1->size + bs2->size; i ++) {
        *((char*)bs1->data + i) = *((char*)bs2->data + i - bs1->size);
    }

    return true;
}