//
// Created by KALIK on 11.10.2021.
//

#include "Assembler.h"

const int ASM_KEK_MARK_BUFF_SIZE = CHAR_MAX;

mrk mark_table[ASM_KEK_MARK_BUFF_SIZE];
Skek undef_mark_names = {};

bool assembler(const char* program_file_name, const char* binfile_name,
               CPU_ERRORS* error) {
    FILE* prog_file = openfile(program_file_name, "r", error);
    if (prog_file == nullptr) return false;
    FILE* bin_file  = openfile(binfile_name, "w", error);
    if (bin_file == nullptr) {
        fclose(bin_file);
        return false;
    }

    fwrite(&KALIK_SIG, INFO_SIZE, 1, bin_file);

    // arr strings consist of processor commands mb
    myarr arr_string = file_reading(prog_file, program_file_name);

//    print_array(&arr_string);


    // arr bit strings
    arr_bit_str arr_bit_string = {};
    arr_bit_string.size = arr_string.size;
    arr_bit_string.arr = (bit_str*)calloc(arr_bit_string.size, sizeof(bit_str));
    if (arr_bit_string.arr == nullptr) {
        free_memory_for_string_array(&arr_string);
        fclose(prog_file);
        fclose(bin_file);
        FUNC_ERROR(error, NULLPTR_IN_CALLOC)
    }

    //print_array(&arr_string);

    #ifdef ASM_DEBUG
        myarr* deb_arr_str = nullptr;
        copy_arr_string(&deb_arr_str, &arr_string);
    #endif


    size_t real_len_bit_string = 0;

    if (!SkekCtor(&undef_mark_names, sizeof(ptr_mrk))) {
        FUNC_ERROR(error, ASM_ERROR_IN_SKEK)
    }

    for (int i = 0; i < arr_string.size; i ++) {
        if (arr_string.arr[i].len == 0) continue;
        long len_com = 0;

        size_t num_space = find_count_elems(arr_string.arr[i].str, ' ') ;

        size_t count_left_sqrt = find_count_elems(arr_string.arr[i].str, '[');
        size_t count_right_sqrt = find_count_elems(arr_string.arr[i].str, ']');
        if (count_left_sqrt != count_right_sqrt) {
            SkekDtor(&undef_mark_names);
            free(arr_bit_string.arr);
            free_memory_for_string_array(&arr_string);
            fclose(prog_file);
            fclose(bin_file);
            FUNC_ERROR(error, ASM_LACK_SQRT_BRACKET)
        }

        char** command_arr = (char**)calloc(num_space + 1 +
                                            count_left_sqrt  + 1 +
                                            count_right_sqrt + 1, sizeof(char*));
        if (command_arr == nullptr) {
            SkekDtor(&undef_mark_names);
            free(arr_bit_string.arr);
            free_memory_for_string_array(&arr_string);
            fclose(prog_file);
            fclose(bin_file);
            FUNC_ERROR(error, NULLPTR_IN_CALLOC)
        }

        arr_bit_string.arr[i].index_str = i;
        if (i > 0)
            arr_bit_string.arr[i].start_byte =
                arr_bit_string.arr[i - 1].start_byte + arr_bit_string.arr[i - 1].size;

        char* ptr_on_str = arr_string.arr[i].str;
//        printf("%zu %s\n", arr_string.arr[i].len, arr_string.arr[i].str);
        while (*ptr_on_str == ' ') {
            *ptr_on_str = '\0';
            ptr_on_str += sizeof(char);
        }

        char* ptr_space = nullptr;
        char* ptr_lsqrt = nullptr;
        char* ptr_rsqrt = nullptr;

        for(;;) {
            ptr_space = strchr(ptr_on_str, ' ');
            ptr_lsqrt = strchr(ptr_on_str, '[');
            ptr_rsqrt = strchr(ptr_on_str, ']');

            if (ptr_space == nullptr &&
                ptr_lsqrt == nullptr &&
                ptr_rsqrt == nullptr) {
                break;
            }

            if (ptr_space == nullptr) {
                ptr_space = arr_string.arr[i].str + arr_string.arr[i].len + 1;
            }

            if (ptr_lsqrt != nullptr && ptr_lsqrt < ptr_space) {
                *ptr_lsqrt = '\0';

                if (*ptr_on_str != '\0') {
                    command_arr[len_com++] = ptr_on_str;
//                    printf("lsqrt: %s\n", command_arr[len_com - 1]);
                }

                command_arr[len_com++] = "[";
//                printf("lsqrt: %s\n", command_arr[len_com - 1]);

                ptr_on_str = ptr_lsqrt + sizeof(char);
                while (*ptr_on_str == ' ') {
                    *ptr_on_str = '\0';
                    ptr_on_str += sizeof(char);
                }
                continue;
            }

            if (ptr_rsqrt != nullptr && ptr_rsqrt < ptr_space) {
                *ptr_rsqrt = '\0';
                if (*ptr_on_str != '\0') {
                    command_arr[len_com++] = ptr_on_str;
//                    printf("rsqrt: %s\n", command_arr[len_com - 1]);
                }
                command_arr[len_com++] = "]";
//                printf("rsqrt: %s\n", command_arr[len_com - 1]);

                ptr_on_str = ptr_rsqrt + sizeof(char);
                while (*ptr_on_str == ' ') {
                    *ptr_on_str = '\0';
                    ptr_on_str += sizeof(char);
                }
                continue;
            }

            *ptr_space = '\0';
            if (*ptr_on_str != '\0') {
                command_arr[len_com++] = ptr_on_str;
//                printf("space: %s\n", command_arr[len_com - 1]);
            }

            ptr_on_str = ptr_space + sizeof(char);
            while (*ptr_on_str == ' ') {
                *ptr_on_str = '\0';
                ptr_on_str += sizeof(char);
            }
        }

        if (*ptr_on_str != '\0') command_arr[len_com++] = ptr_on_str;

#ifdef ASM_DEBUG
        for (int j = 0; j < len_com; j ++) {
            printf("%s\n", command_arr[j]);
        }
#endif

//        if (!ConvInBin(command_arr, &arr_bit_string.arr[i], error)) {
//            SkekDtor(&undef_mark_names);
//            free(command_arr);
//            free(arr_bit_string.arr);
//            free_memory_for_string_array(&arr_string);
//            fclose(prog_file);
//            fclose(bin_file);
//            return false;
//
//        }
        // todo in end my files exist ascii code 11 i don't know what it is
       if (ConvInBin(command_arr, &arr_bit_string.arr[i], len_com, error)) {
           real_len_bit_string++;
//           write_byte_string(bin_file, &arr_bit_string.arr[i]);
        }
        free(command_arr);
    }

    if (!ReloadMarkName(&arr_bit_string, error)) {

        SkekDtor(&undef_mark_names);
        free(arr_bit_string.arr);
        free_memory_for_string_array(&arr_string);
        fclose(prog_file);
        fclose(bin_file);
        return false;
    }

    for (int i = 0; i < real_len_bit_string; i ++) {
        if (arr_bit_string.arr[i].data == nullptr) continue;
        write_byte_string(bin_file, &arr_bit_string.arr[i]);
    }

    #ifdef ASM_DEBUG
        if (!ASMDump(deb_arr_str, &arr_bit_string, LOG_FILE_NAME, error)) {
            *error = ASM_ERROR_IN_DUMP;
            SMALL_DUMP(ASM_ERROR_IN_DUMP);

            SkekDtor(&undef_mark_names);
            free_memory_for_string_array(deb_arr_str);
            free(deb_arr_str);
            free(arr_bit_string.arr);
            free_memory_for_string_array(&arr_string);
            fclose(prog_file);
            fclose(bin_file);
            return false;
        }
        free_memory_for_string_array(deb_arr_str);
        free(deb_arr_str);
    #endif

    SkekDtor(&undef_mark_names);
    free(arr_bit_string.arr);
    free_memory_for_string_array(&arr_string);
    fclose(prog_file);
    fclose(bin_file);
    return true;
}

bool ConvInBin(char** command_arr, bit_str* bit_string,
               size_t size_com, CPU_ERRORS* error) {
    if (command_arr[0] == nullptr) {
        FUNC_ERROR(error, ASM_WRONG_FORMAT)
    }

    ASM_COMMANDS command = ConvCom(command_arr[0]);

    COMMON_ASM_TYPE  number = -1;
    size_t pos_com          = 0;
    CPU_REGISTERS REG_NAME  = REG_UND;

    if (MarkFlag(bit_string, command_arr, size_com, &pos_com, error)){
        return true;
    }
    else if (*error != UNDEFINED) {
        return false;
    }


    switch (command) {

        case CMD_PUSH:
            // PUSH must have 2 arguments
            if (command_arr[1] == nullptr) {
                FUNC_ERROR(error, ASM_WRONG_FORMAT)
            }

            ALLOC_COM(CMD_PUSH)

            // todo improve SeriesFlag
            if (!SeriesFlag(bit_string, command_arr, size_com, &pos_com, error)) {
                free(bit_string->data);
                FUNC_ERROR(error, ASM_WRONG_FORMAT)
            }

            return true;

        case CMD_POP:
            ALLOC_COM(CMD_POP)
            if (NoFlag(bit_string, command_arr, size_com, &pos_com, error))     goto cmd_pop;
            if (SeriesFlag(bit_string, command_arr, size_com, &pos_com, error)) goto cmd_pop;

            free(bit_string->data);
            FUNC_ERROR(error, ASM_WRONG_FORMAT)

            cmd_pop: return true;

        case CMD_IN:

            ALLOC_COM(CMD_IN)
\
            if (NoFlag(bit_string, command_arr, size_com, &pos_com, error))     goto cmd_in;
            if (SeriesFlag(bit_string, command_arr, size_com, &pos_com, error)) goto cmd_in;

            free(bit_string->data);
            FUNC_ERROR(error, ASM_WRONG_FORMAT)

            cmd_in: return true;

        case CMD_OUT:
            // todo check 1 arg
            ALLOC_COM(CMD_OUT)
            if (NoFlag(bit_string, command_arr, size_com, &pos_com, error))     goto cmd_out;
            if (SeriesFlag(bit_string, command_arr, size_com, &pos_com, error)) goto cmd_out;

            free(bit_string->data);
            FUNC_ERROR(error, ASM_WRONG_FORMAT)

            cmd_out: return true;

        case CMD_ADD:
            ALLOC_COM(CMD_ADD)
            return true;

        case CMD_SUB:
            ALLOC_COM(CMD_SUB)
            return true;

        case CMD_MULT:
            ALLOC_COM(CMD_MULT)
            return true;

        case CMD_DIV:
            ALLOC_COM(CMD_DIV)
            return true;

        case CMD_LEAP:
            if (command_arr[1] == nullptr) {
                FUNC_ERROR(error, ASM_WRONG_FORMAT)
            }

            ALLOC_COM(CMD_LEAP)

            if (SeriesFlag(bit_string, command_arr, size_com, &pos_com, error)) goto cmd_leap;


            free(bit_string->data);
            FUNC_ERROR(error, ASM_WRONG_FORMAT);

            cmd_leap: return true;

        case CMD_RESET:
            ALLOC_COM(CMD_RESET)
            return true;

        case CMD_END:
            ALLOC_COM(CMD_END)
            return true;

        case CMD_UND:
            FUNC_ERROR(error, UNDEFINED)
    }

    FUNC_ERROR(error, UNDEFINED)
}

ASM_COMMANDS ConvCom (const char* string) {
    //todo strncmp
    if (strcmp(string, "PUSH")  == 0)   return CMD_PUSH;
    if (strcmp(string, "POP")   == 0)   return CMD_POP;
    if (strcmp(string, "IN")    == 0)   return CMD_IN;
    if (strcmp(string, "OUT")   == 0)   return CMD_OUT;
    if (strcmp(string, "ADD")   == 0)   return CMD_ADD;
    if (strcmp(string, "SUB")   == 0)   return CMD_SUB;
    if (strcmp(string, "MULT")  == 0)   return CMD_MULT;
    if (strcmp(string, "DIV")   == 0)   return CMD_DIV;
    if (strcmp(string, "LEAP")  == 0)   return CMD_LEAP;
    if (strcmp(string, "RESET") == 0)   return CMD_RESET;
    if (strcmp(string, "END")   == 0)   return CMD_END;
    return CMD_UND;
}

CPU_REGISTERS ConvReg(const char* string) {
    if (strcmp(string, "KEK0") == 0) return REG_KEK0;
    if (strcmp(string, "KEK1") == 0) return REG_KEK1;
    if (strcmp(string, "KEK2") == 0) return REG_KEK2;
    if (strcmp(string, "KEK3") == 0) return REG_KEK3;
    if (strcmp(string, "KEK4") == 0) return REG_KEK4;
    if (strcmp(string, "KEK5") == 0) return REG_KEK5;
    if (strcmp(string, "KEK6") == 0) return REG_KEK6;
    if (strcmp(string, "KEK7") == 0) return REG_KEK7;
    return REG_UND;
}

bool ReloadMarkName(arr_bit_str* arrBitStr, CPU_ERRORS* error) {
    while (undef_mark_names.size != 0) {
        ptr_mrk loc = {};
        if (!SkekPop(&undef_mark_names, &loc)) {
            FUNC_ERROR(error, ASM_ERROR_IN_SKEK)
        }
        if (loc.arr_index == -1 ||
            loc.byte_pos_in_str == -1 ||
            loc.pos_name == -1) {
            FUNC_ERROR(error, ASM_MARK_NAMES_SKEK_ERROR)
        }

        if (mark_table[loc.pos_name].byte_pos == -1) {
            printf("%s\n", mark_table[loc.pos_name].name);
            FUNC_ERROR(error, ASM_MARK_DONT_DEF)
        }

        *(ASM_MARK_TYPE*)((char*)arrBitStr->arr[loc.arr_index].data + loc.byte_pos_in_str) =
                mark_table[loc.pos_name].byte_pos;

    }

    return true;
}


bool SeriesFlag (bit_str* bit_string, char** command_arr,
                 size_t size_com, size_t* pos_com,
                 CPU_ERRORS* errors) {

    if (PlusFlag(bit_string, command_arr, size_com, pos_com, errors))   return true;
    if (*errors != UNDEFINED) return false;
    if (SqrtFlag(bit_string, command_arr, size_com, pos_com, errors))   return true;
    if (*errors != UNDEFINED) return false;
    if (MarkFlag(bit_string, command_arr, size_com, pos_com, errors))   return true;
    if (*errors != UNDEFINED) return false;
    if (ConstFlag(bit_string, command_arr, size_com, pos_com, errors))  return true;
    if (*errors != UNDEFINED) return false;
    if (RegFlag(bit_string, command_arr, size_com, pos_com, errors))    return true;
    if (*errors != UNDEFINED) return false;
    return false;
}


bool NoFlag     (bit_str* bit_string, char** command_arr,
                 size_t size_com, size_t* pos_com,
                 CPU_ERRORS* errors) {
    printf("here\n");
    if (command_arr[*pos_com] != nullptr) return false;

    long long old_size = bit_string->size;
    long long new_size = bit_string->size + sizeof(char);

    bit_string->data = realloc(bit_string->data,
                               new_size);
    if (bit_string->data == nullptr) {
        FUNC_ERROR(errors, NULLPTR_IN_REALLOC)
    }

#ifdef ASM_DEBUG
    printf("\nI am %s\n."
           "I Extension bit_string->data:\n"
           "Old size: %ld\n"
           "New size: %ld\n\n",
           __PRETTY_FUNCTION__, old_size, new_size);
#endif

    *(char *) ((char *) bit_string->data + old_size) = NO_FLAG;
    bit_string->size = new_size;
    *pos_com += 1;
    return true;
}

bool MarkFlag  (bit_str* bit_string, char** command_arr,
                size_t size_com, size_t* pos_com,
                CPU_ERRORS* errors) {
    if (command_arr[*pos_com] == nullptr ||
        command_arr[*pos_com][0] != ':') return false;

    long long start_byte_pos = bit_string->size;
    long long end_byte_pos   = bit_string->size;
    if (start_byte_pos != 0) {
        end_byte_pos = bit_string->size + sizeof(char) + sizeof(ASM_MARK_TYPE);
        bit_string->data = realloc(bit_string->data,
                                   end_byte_pos);
        if (bit_string->data == nullptr) {
            FUNC_ERROR(errors, NULLPTR_IN_REALLOC)
        }
    }


#ifdef ASM_DEBUG
    printf("\nI am %s\n."
           "I Extension bit_string->data:\n"
           "Old size: %lld\n"
           "New size: %lld\n\n",
           __PRETTY_FUNCTION__, start_byte_pos, end_byte_pos);
#endif

    long long i = 0;

    while (mark_table[i].name != nullptr) {
        if (strcmp(mark_table[i].name, command_arr[*pos_com]) == 0) {
            if (start_byte_pos == 0 && mark_table[i].byte_pos == -1) {

                mark_table[i].byte_pos = bit_string->start_byte;

#ifdef ASM_MARK_DEBUG
                printf("\x1b[31m"
                       "Found and pos == 0 and byte_pos == -1\n"
                       "I am here: %lld, name: %s, byte_pos: %lld\x1b[0m\n",
                       i, mark_table[i].name, mark_table[i].byte_pos);
#endif

                bit_string->size = end_byte_pos;
                (*pos_com) ++;
                return true;
            }

            if (start_byte_pos == 0) {
                FUNC_ERROR(errors, ASM_SECONDLY_MARK_DEFENITION)
            }

            if (mark_table[i].byte_pos == -1) {

                ptr_mrk a = {i, bit_string->index_str, start_byte_pos + (long long)sizeof(char)};
                if(!SkekPush(&undef_mark_names, &a)) {
                    FUNC_ERROR(errors, ASM_ERROR_IN_SKEK)
                }

#ifdef ASM_MARK_DEBUG
                printf("\x1b[31m"
                       "Found and pos != 0 and byte_pos == -1\n"
                       "I am here: %lld, name: %s, byte_pos: %lld\x1b[0m\n",
                       i, mark_table[i].name, mark_table[i].byte_pos);
                SkekDump(&undef_mark_names, DEB_ELEM("Found and pos != 0 and byte_pos == -1"));
#endif

                *(char*)((char*)bit_string->data + start_byte_pos) = MARK_FLAG;
                *(ASM_MARK_TYPE *)((char*)bit_string->data + start_byte_pos + sizeof(char)) = ASM_MAGIC_NUMBER;

                bit_string->size = end_byte_pos;
                (*pos_com) ++;
                return true;
            }

#ifdef ASM_MARK_DEBUG
            printf("\x1b[31m"
                   "Found and pos > 0 and byte_pos != -1\n"
                   "I am here: %lld, name: %s, byte_pos: %lld\x1b[0m\n",
                   i, mark_table[i].name, mark_table[i].byte_pos);
#endif

            *(char*)((char*)bit_string->data + start_byte_pos) = MARK_FLAG;
            *(ASM_MARK_TYPE *)((char*)bit_string->data + start_byte_pos + sizeof(char)) = mark_table[i].byte_pos;

            bit_string->size = end_byte_pos;
            (*pos_com) ++;
            return true;
        }
        i++;
    }


    if (start_byte_pos == 0) {
        mark_table[i].name = command_arr[*pos_com];
//        mark_table[i].name = strcpy(mark_table[i].name, command_arr[*pos_com]);
        mark_table[i].byte_pos = bit_string->start_byte;

#ifdef ASM_MARK_DEBUG
        printf("\x1b[31m"
               "Not found and pos == 0\n"
               "I am here: %lld, name: %s, byte_pos: %lld\x1b[0m\n",
               i, mark_table[i].name, mark_table[i].byte_pos);
#endif
        bit_string->size = end_byte_pos;
        (*pos_com) ++;
        return true;
    }
    else {
        mark_table[i].name = command_arr[*pos_com];
//        mark_table[i].name = strcpy(mark_table[i].name, command_arr[*pos_com]);
        mark_table[i].byte_pos = -1;

        ptr_mrk a = {i, bit_string->index_str, start_byte_pos + (ASM_MARK_TYPE)sizeof(char)};
        if (!SkekPush(&undef_mark_names, &a)) {
            FUNC_ERROR(errors, ASM_ERROR_IN_SKEK)
        }

#ifdef ASM_MARK_DEBUG
        printf("\x1b[31m"
               "Not found and pos > 0\n"
               "I am here: %lld, name: %s, byte_pos: %lld\x1b[0m\n",
               i, mark_table[i].name, mark_table[i].byte_pos);
        SkekDump(&undef_mark_names, DEB_ELEM("Not found and pos > 0"));
#endif
        *(char*)((char*)bit_string->data + start_byte_pos) = MARK_FLAG;
        *(ASM_MARK_TYPE *)((char*)bit_string->data + start_byte_pos + sizeof(char)) = ASM_MAGIC_NUMBER;

        bit_string->size = end_byte_pos;
        (*pos_com) ++;
        return true;
    }

}

bool ConstFlag  (bit_str* bit_string, char** command_arr,
                 size_t size_com, size_t *pos_com,
                 CPU_ERRORS* errors) {
    COMMON_ASM_TYPE number = 0;
    if (string_to_number(command_arr[*pos_com], &number)) {

        long long old_size = bit_string->size;
        long long new_size = bit_string->size + sizeof(char) + sizeof(COMMON_ASM_TYPE);

        bit_string->data = realloc(bit_string->data,
                                   new_size);
        if (bit_string->data == nullptr) {
            FUNC_ERROR(errors, NULLPTR_IN_REALLOC)
        }

#ifdef ASM_DEBUG
        printf("\nI am %s\n."
               "I Extension bit_string->data:\n"
               "Old size: %lld\n"
               "New size: %lld\n\n",
               __PRETTY_FUNCTION__, old_size, new_size);
#endif

        *(char*)((char*)bit_string->data + old_size) = CONST_FLAG;
        *(COMMON_ASM_TYPE*)((char*)bit_string->data + old_size + sizeof(char)) = number;
        bit_string->size = new_size;
        (*pos_com) = *pos_com + 1;
        return true;
    }
    return false;
}

bool RegFlag    (bit_str* bit_string, char** command_arr,
                 size_t size_com, size_t* pos_com,
                 CPU_ERRORS* errors) {

    CPU_REGISTERS REG_NAME  = REG_UND;

    if ((REG_NAME = ConvReg(command_arr[*pos_com])) == REG_UND) return false;


    long old_size = bit_string->size;
    long new_size = bit_string->size + sizeof(char) + sizeof(char);

    bit_string->data = realloc(bit_string->data,
                               new_size);
    if (bit_string->data == nullptr) {
        FUNC_ERROR(errors, NULLPTR_IN_REALLOC)
    }

#ifdef ASM_DEBUG
    printf("\nI am %s\n."
           "I Extension bit_string->data:\n"
           "Old size: %ld\n"
           "New size: %ld\n\n",
           __PRETTY_FUNCTION__, old_size, new_size);
#endif

    *(char*)((char*)bit_string->data + old_size) = REG_FLAG;
    *(char*)((char*)bit_string->data + old_size + sizeof(char)) = REG_NAME;

    bit_string->size = new_size;
    *pos_com += 1;

    return true;
}

bool PlusFlag   (bit_str* bit_string, char** command_arr,
                 size_t size_com, size_t* pos_com,
                 CPU_ERRORS* errors) {

//    printf("plus: %s %s %s\n", command_arr[*pos_com], command_arr[*pos_com + 1], command_arr[*pos_com + 2]);
    if (*pos_com + 2 > size_com) return false;

    if (command_arr[*pos_com] == nullptr     ||
        command_arr[*pos_com + 1] == nullptr ||
        command_arr[*pos_com + 2] == nullptr) return false;

    // if left number is sqrt
    if (strcmp(command_arr[*pos_com], "[") == 0) {
        bool flag = false;
        size_t i = *pos_com;
        long numb_sqrt = 0;
        while (i < size_com) {
//            printf("circle: %ld %ld %s\n", i, size_com, command_arr[i]);
            if (strcmp(command_arr[i], "[") == 0) numb_sqrt ++;
            if (strcmp(command_arr[i], "]") == 0) {
//                printf("    circle: %ld %ld %s\n", i, size_com, command_arr[i]);
                numb_sqrt--;
                if (numb_sqrt == 0) {
                    flag = true;
                    break;
                }
            }
            i++;
        }

        if (flag && command_arr[i + 1] == nullptr)        return false;
        if (flag && strcmp(command_arr[i + 1], "+") != 0) return false;
    }
    else if (strcmp(command_arr[*pos_com + 1], "+") != 0) return false;

    long long old_size = bit_string->size;
    long long new_size = bit_string->size + sizeof(char);

//    for (int i = 0; i < bit_string->size; i++) {
//        printf("%02X", *((char*)bit_string->data + i));
//    }
//    printf("\n");

    bit_string->data = realloc(bit_string->data,
                               new_size);
    if (bit_string->data == nullptr) {
        FUNC_ERROR(errors, NULLPTR_IN_REALLOC)
    }

#ifdef ASM_DEBUG
    printf("\nI am %s\n."
           "I Extension bit_string->data:\n"
           "Old size: %lld\n"
           "New size: %lld\n\n",
           __PRETTY_FUNCTION__, old_size, new_size);
#endif

    *(char*)((char*)bit_string->data + old_size) = PLUS_FLAG;
    bit_string->size = new_size;

    if (SqrtFlag(bit_string,  command_arr, size_com, pos_com, errors))   goto next;
    if (MarkFlag(bit_string,  command_arr, size_com, pos_com, errors))   goto next;
    if (ConstFlag(bit_string, command_arr, size_com, pos_com, errors))   goto next;
    if (RegFlag(bit_string,   command_arr, size_com, pos_com, errors))   goto next;
    FUNC_ERROR(errors, ASM_WRONG_FORMAT)

    next: *pos_com += 1;

    if (!SeriesFlag(bit_string, command_arr, size_com, pos_com, errors)) {
        FUNC_ERROR(errors, ASM_WRONG_FORMAT)
    }

    return true;
}


bool SqrtFlag   (bit_str* bit_string, char** command_arr,
                 size_t size_com, size_t* pos_com,
                 CPU_ERRORS* errors) {

    if (strcmp(command_arr[*pos_com], "[") != 0) return false;

    long long old_size = bit_string->size;
    long long new_size = bit_string->size + sizeof(char);

    bit_string->data = realloc(bit_string->data,
                               new_size);
    if (bit_string->data == nullptr) {
        FUNC_ERROR(errors, NULLPTR_IN_REALLOC)
    }

#ifdef ASM_DEBUG
    printf("\nI am %s\n."
           "I Extension bit_string->data:\n"
           "Old size: %lld\n"
           "New size: %lld\n\n",
           __PRETTY_FUNCTION__, old_size, new_size);
#endif

    *(char*)((char*)bit_string->data + old_size) = MEM_FLAG;
    bit_string->size = new_size;

    *pos_com += 1;
    while (*pos_com < size_com) {
        if (command_arr[*pos_com] == nullptr) {
            FUNC_ERROR(errors, ASM_LACK_SQRT_BRACKET)
        }
        if (strcmp(command_arr[*pos_com], "]") == 0) {
            *pos_com += 1;
            return true;
        }
        printf("hui: %c\n", command_arr[*pos_com][0]);
        if (!SeriesFlag(bit_string, command_arr, size_com, pos_com, errors)) {
            FUNC_ERROR(errors, ASM_WRONG_FORMAT)
        }
    }

    FUNC_ERROR(errors, ASM_LACK_SQRT_BRACKET);
}

bool ASMDump(myarr* arr_string, arr_bit_str* arr_bit_string,
             const char* logfile_name, CPU_ERRORS* error) {
    FILE* logfile = openfile(logfile_name, "w");
    if (logfile == nullptr) return false;

    if (arr_string->size != arr_bit_string->size) {
        fclose(logfile);
        return false;
    }

    const char* COMMAND = "COMMANDS";
    const char* BIT_STRING = "BIT_FORM";

    fprintf(logfile, "START DUMP\n");
    fprintf(logfile,"%-*s %s\n",
                     MAX_INDENT, COMMAND, BIT_STRING);

    for (int i = 0; i < arr_bit_string->size; i++) {
        if (!ASMStrDump(logfile, &arr_string->arr[i], &arr_bit_string->arr[i])) {
            fclose(logfile);
            return false;
        }
    }

    fprintf(logfile, "\n");
    MarkDump(logfile);
    if(!SkekDump(&undef_mark_names, DEB_ELEM("ASM_DUMP"))) {
        FUNC_ERROR(error, ASM_ERROR_IN_SKEK)
    }

    fprintf(logfile, "END DUMP\n");

    fclose(logfile);
    return true;
}

bool ASMStrDump (FILE* logfile, mystr* string, bit_str* bit_string) {
    if (string == nullptr) {
        SMALL_DUMP(NULLPTR)
        return false;
    }
    if (bit_string == nullptr) {
        SMALL_DUMP(NULLPTR)
        return false;
    }

    fprintf(logfile,
            "%-*s ", MAX_INDENT, string->str);

    fprintf(logfile, "data[%lld] = ", bit_string->index_str);
    fprintf_bit_string_HEX(logfile, bit_string);
    fprintf(logfile, "\n");

    return true;
}

bool MarkDump(FILE* logfile) {

    fprintf(logfile, "MARK BUFFER:\n");
    const char* NAME = "NAME";
    const char* BYTE_POS = "BYTE_POS";

    fprintf(logfile,"%-*s %s\n",
            MAX_INDENT, NAME, BYTE_POS);

    for(int i = 0; mark_table[i].name != nullptr; i++) {
        fprintf(logfile, "%-*s %lld\n",MAX_INDENT, mark_table[i].name, mark_table[i].byte_pos);
    }

    fprintf(logfile, "\n");

    return true;
}


