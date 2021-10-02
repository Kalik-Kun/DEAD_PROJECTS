//
// Created by arlik_null on 20.09.2021.
//

#include "LibStack.h"


const std::map<int, char*> NAME_ERRORS = {
        {0  , "UNDEFINED"},
        {1  , "NULLPTR_ON_SKEK"},
        {2  , "SIZE_LARGE_CAPACITY"},
        {3  , "STACK_ALREADY_CREATED"},
        {4  , "ERROR_ALLOCATE_MEMORY"},
        {5  , "GET_WITHOUT_ELEM"},
        {6  , "POP_WITHOUT_ELEM"},
        {7  , "TWICE_ALLOCATE"},
        {8  , "NEGATIVE_SIZE"},
        {9  , "NULLPTR_IN_DATA"},
        {10 , "NULLPTR_ARRAY"},
        {11 , "NULLPTR_ELEM"},
        {11 , "FILE_OPEN"},

};

const char  FREE_ERROR_POINTER      = 13;
const char  ZOMBIE_NUMBER           = 17;
const long  BAD_SIZE                = LONG_MAX - 3243;
const long  CANARY_NUMBER           = 0xD0D0B00B5;
int         ERR_UNDEFINED           = UNDEFINED;
const int   FACTOR_INCR_CAPACITY    = 2;
const int   FACTOR_DECR_CAPACITY    = 2;
char*       LOGFILE_NAME            = "SkekLogFile.txt";
const int   PRINT_TYPE              = 1;


char SkekCtor   (struct Skek *my_skek, long amount_byte_type,
                long capacity, int* error) {

    if (!SkekVerif(my_skek, error)) {
        return false;
    }
    if (my_skek->data != nullptr) {
        *error = STACK_ALREADY_CREATED;
        return false;
    }
    if ((my_skek->data = (void *) calloc(capacity, amount_byte_type)) == nullptr) {
        *error = ERROR_ALLOCATE_MEMORY;
        return false;
    }

    my_skek->size_type = amount_byte_type;
    my_skek->size      = 0;
    my_skek->capacity  = capacity;

    if (!SkekVerif(my_skek, error)) {
        return false;
    }
    return true;
}

char SkekDtor(struct Skek *my_skek, int *error) { // todo distrc for void
    if (!SkekVerif(my_skek, error)) {
        return false;
    }

    kekset(my_skek->data, (void *) ZOMBIE_NUMBER, my_skek->capacity, my_skek->size_type, error);

    free(my_skek->data);
    my_skek->size       = BAD_SIZE;
    my_skek->size_type  = BAD_SIZE;
    my_skek->capacity   = BAD_SIZE;
    my_skek->data       = (void *) FREE_ERROR_POINTER;

    if (!SkekVerif(my_skek, error)) {
        return false;
    }

    return true;
}

char SkekExtension(struct Skek *my_skek, int* error) {
    if (!SkekVerif(my_skek, error)) {
        return false;
    }

    if (my_skek->size == my_skek->capacity) { // increase size

        printf("\n"
               "_____________________________\n"
               "_____________________________\n"
               "I'm SkekExtension\n"
               "I increase size memory:\n"
               "ptr on data:    %c"
               "size:           %ld\n"
               "capacity:       %ld\n"
               "size_type:      %ld\n"
               "_____________________________\n"
               "_____________________________\n",
               *((char *) my_skek->data),my_skek->size, my_skek->capacity, my_skek->size_type);
        // todo 2 global const
        my_skek->capacity *= FACTOR_INCR_CAPACITY;
        my_skek->data = (void *)realloc(my_skek->data,
                                        my_skek->capacity * my_skek->size_type);

        if (!SkekVerif(my_skek, error)) {
            return false;
        }
        return true;
    }

    if (my_skek->size * FACTOR_DECR_CAPACITY == my_skek->capacity) {  // decrease size
        printf("\n"
               "_____________________________\n"
               "_____________________________\n"
               "I'm SkekExtension\n"
               "I decrease resize memory:\n"
               "ptr on data:    %c"
               "size:           %ld\n"
               "capacity:       %ld\n"
               "size_type:      %ld\n"
               "_____________________________\n"
               "_____________________________\n",
               *((char *) my_skek->data), my_skek->size, my_skek->capacity, my_skek->size_type);


        my_skek->capacity = (long) my_skek->capacity / FACTOR_DECR_CAPACITY;
        my_skek->data = (void *) realloc(my_skek->data,
                                         my_skek->capacity * my_skek->size_type);

        if (!SkekVerif(my_skek, error)) {
            return false;
        }
        return true;
    }

    return true;
}

void* SkekGet (struct Skek* my_skek, int* error) {
    if (!SkekVerif(my_skek, error)) {
        return nullptr;
    }
    if (my_skek->size == 0) {
        *error = GET_WITHOUT_ELEM;
        return nullptr;
    }

    void* top_elem = (char *) my_skek->data + (my_skek->size - 1) * my_skek->size_type;

    if (top_elem == nullptr) {
        *error = NULLPTR_IN_DATA;
        return nullptr;
    }

    if (!SkekVerif(my_skek, error)) {
        return nullptr;
    }
    return top_elem;
}


char SkekPush(struct Skek *my_skek, void* value, int* error) {
    if (!SkekVerif(my_skek, error)) {
        return false;
    }
    if (!SkekExtension(my_skek, error)) return false;

    kekset((char *) my_skek->data + my_skek->size * my_skek->size_type,
           value, 1, my_skek->size_type, error);
    my_skek->size++;

    if (!SkekVerif(my_skek, error)) {
        return false;
    }
    return true;
}

void* SkekPop (struct Skek* my_skek, int *error) {
    if (!SkekVerif(my_skek, error)) {
        return nullptr;
    }
    if (my_skek->size == 0) {
        *error = POP_WITHOUT_ELEM;
        return nullptr;
    }

    void* elem = (void *)calloc(my_skek->size_type, sizeof (char));
    void* top_elem = (char *) my_skek->data + (my_skek->size - 1) * my_skek->size_type;

    kekset(elem, top_elem, 1,  my_skek->size_type);
    my_skek->size--;

    if (!SkekExtension(my_skek, error)) {
        return nullptr;
    }
    if (!SkekVerif(my_skek, error)) {
        return nullptr;
    }
    return elem;
}

char SkekVerif (struct Skek* my_skek, int* error) {

    if (my_skek->data == nullptr) {
        *error = NULLPTR_ON_SKEK;
        return false;
    }

    if (my_skek->size       == BAD_SIZE ||
        my_skek->size_type  == BAD_SIZE ||
        my_skek->capacity   == BAD_SIZE ||
        my_skek->data       == (void *) FREE_ERROR_POINTER) {

        *error = TWICE_ALLOCATE;
        return false;
    }

    if (my_skek->size       < 0 ||
        my_skek->size_type  < 0 ||
        my_skek->capacity   < 0) {
        // todo 3 if and enumb errors for this
        *error = NEGATIVE_SIZE;
        return false;
    }

    if (my_skek->size > my_skek->capacity) {
        *error = SIZE_LARGE_CAPACITY;
        return false;
    }

    return true;
}

char SkekDump (struct Skek * my_skek, const char* name_logfile,
               struct debug_elements debElem, int *error) {

    FILE* file = fopen(name_logfile, "a");
    if (file == nullptr) {
        // todo for colored output god idea is ncurses but i vary lazy for this
        printf("\x1b[31;5m"
               "ERROR: file can't input\n"
               "Please reload program\n"
               "\x1b[0m");
        *error = FILE_OPEN;
        return false;
    }
    // todo define for color text
    printf("\n\x1b[32;1m"
           "START DUMP\n"
           "LAUNCHED FROM:\n\x1b[0m"
           "\x1b[33mFILE:\x1b[0m %s\n"
           "\x1b[33mFUNC:\x1b[0m %s\n"
           "\x1b[33mLINE:\x1b[0m %d\n\n",
           debElem.FILE, debElem.PRETTY_FUNCTION, debElem.LINE);


    if (*error != UNDEFINED) {
        printf("\x1b[31m"
               "!!!!ERROR SKEK!!!!\n"
               "SKEK ERROR NUMBER: %d\n That's mean: %s\n\n",
               *error, NAME_ERRORS.at(*error));

        printf("Skek->size: %ld\n"
               "Skek->size_type: %ld\n"
               "Skek->capacity: %ld\n"
               "Skek->data:\n\n",
               my_skek->size, my_skek->size_type, my_skek->capacity);

        if (my_skek->data == nullptr ||
            my_skek->data == &FREE_ERROR_POINTER) {
            printf("skek hasn't data\n");
        }
        else {
            char* type_elem = print_void_arr(my_skek->data, PRINT_TYPE,
                                             my_skek->size, my_skek->size_type);
            printf("type of elements: %s\n", type_elem);
        }

        printf("END ERROR SKEK\n\x1b[0m");
    }
    
    if (*error != UNDEFINED) {
        fprintf(file,"!!!!ERROR SKEK!!!!\n"
                     "SKEK ERROR NUMBER: %d\n That's mean: %s\n\n",
               *error, NAME_ERRORS.at(*error));
    }

    else fprintf(file, "NORMAL SKEK\n\n");

    fprintf(file, "Skek->size: %ld\n"
           "Skek->size_type: %ld\n"
           "Skek->capacity: %ld\n"
           "Skek->data:\n\n",
           my_skek->size, my_skek->size_type, my_skek->capacity);

    if (my_skek->data == nullptr ||
        my_skek->data == &FREE_ERROR_POINTER) {
        fprintf(file, "Skek hasn't data\n");
    }
    else {
        char* type_elem = file_print_void_arr(file, my_skek->data, PRINT_TYPE,
                                              my_skek->size, my_skek->size_type);

        fprintf(file, "type of elements: %s\n", type_elem);
    }

    if (*error != UNDEFINED) fprintf(file, "END ERROR SKEK\n");
    else                     fprintf(file, "END SKEK\n");

    fprintf (file, "END DUMB\n\n");

    fclose (file);
    return true;
}

char CleanLogFile (const char* name_logfile, int* error) {
    // todo this is legal?
    FILE* file = fopen(name_logfile, "w");

    if (file == nullptr) {
        printf("\x1b[31;5m"
               "ERROR: file can't input\n"
               "Please reload program\n"
               "\x1b[0m");
        *error = FILE_OPEN;
        return false;
    }
    fclose(file);
    return true;
}


char kekset (void* ptr, void* elem, long count_elem, long size_type, int* error) {
    if (ptr == nullptr) {
        *error = NULLPTR_ARRAY;
        return false;
    }
    if (elem == nullptr) {
        *error = NULLPTR_ELEM;
        return false;
    }

    char* elem_char = (char*) elem;
    char* ptr_char  = (char*) ptr;

    for (long i = 0; i < count_elem; i ++) {
        for (int type_byte = 0; type_byte < size_type; type_byte++) {
            // todo check can elem do *
            *(ptr_char + i * size_type + type_byte) =
                    *(elem_char + type_byte);
        }
    }

    return true;
}


char* print_void_arr(void* ptr, int type, long count_elem, long size_type) {
    if (type == 0 && size_type == sizeof(bool)) {
        for (long numb_elem = 0; numb_elem < count_elem; numb_elem ++) {
            printf("data[%ld] = %d\n",
                   numb_elem, *((bool *) ptr + numb_elem));
        }
        return "bool";
    }

    if (type == 1) {
        switch (size_type) {
            case sizeof(char):
                for (long numb_elem = 0; numb_elem < count_elem; numb_elem ++) {
                    printf("data[%ld] = %c\n",
                           numb_elem, *((char*) ptr + numb_elem));
                }
                return "char";

            case sizeof(int):
                for (long numb_elem = 0; numb_elem < count_elem; numb_elem ++) {
                    printf("data[%ld] = %d\n",
                           numb_elem, *((int*) ptr + numb_elem));
                }

            case sizeof(long):
                for (long numb_elem = 0; numb_elem < count_elem; numb_elem ++) {
                    printf("data[%ld] = %ld\n",
                           numb_elem, *((long *) ptr + numb_elem));
                }
                return "long";

//            case sizeof(long long):
//                for (long numb_elem = 0; numb_elem < count_elem; numb_elem ++) {
//                    printf("data[%ld] = %lld\n",
//                           numb_elem, *((long long*) ptr));
//                }
//                return "long long";

            default:
                return "Don't know";
        }
    }

    if (type == 2) {
        switch (size_type) {
            case sizeof(float):
                for (long numb_elem = 0; numb_elem < count_elem; numb_elem ++) {
                    printf("data[%ld] = %f\n",
                           numb_elem, *((float *) ptr + numb_elem));
                }
                return "float";

            case sizeof(double):
                for (long numb_elem = 0; numb_elem < count_elem; numb_elem ++) {
                    printf("data[%ld] = %lf\n",
                           numb_elem, *((double *) ptr + numb_elem));
                }
                return "double";

            default:
                return "Don't know";
        }
    }

    return "Don't know";
}

char* file_print_void_arr(FILE* file, void* ptr, int type, long count_elem, long size_type) {
    if (type == 0 && size_type == sizeof(bool)) {
        for (long numb_elem = 0; numb_elem < count_elem; numb_elem ++) {
            fprintf(file, "data[%ld] = %d\n",
                   numb_elem, *((bool *) ptr + numb_elem));
        }
        return "bool";
    }

    if (type == 1) {
        switch (size_type) {
            case sizeof(char):
                for (long numb_elem = 0; numb_elem < count_elem; numb_elem ++) {
                    fprintf(file, "data[%ld] = %c\n",
                           numb_elem, *((char*) ptr + numb_elem));
                }
                return "char";

            case sizeof(int):
                for (long numb_elem = 0; numb_elem < count_elem; numb_elem ++) {
                    fprintf(file, "data[%ld] = %d\n",
                           numb_elem, *((int*) ptr + numb_elem));
                }

            case sizeof(long):
                for (long numb_elem = 0; numb_elem < count_elem; numb_elem ++) {
                    fprintf(file,"data[%ld] = %ld\n",
                           numb_elem, *((long *) ptr + numb_elem));
                }
                return "long";

//            case sizeof(long long):
//                for (long numb_elem = 0; numb_elem < count_elem; numb_elem ++) {
//                    printf("data[%ld] = %lld\n",
//                           numb_elem, *((long long*) ptr));
//                }
//                return "long long";

            default:
                return "Don't know";
        }
    }

    if (type == 2) {
        switch (size_type) {
            case sizeof(float):
                for (long numb_elem = 0; numb_elem < count_elem; numb_elem ++) {
                    fprintf(file, "data[%ld] = %f\n",
                           numb_elem, *((float *) ptr + numb_elem));
                }
                return "float";

            case sizeof(double):
                for (long numb_elem = 0; numb_elem < count_elem; numb_elem ++) {
                    fprintf(file, "data[%ld] = %lf\n",
                           numb_elem, *((double *) ptr + numb_elem));
                }
                return "double";

            default:
                return "Don't know";
        }
    }

    return "Don't know";
}