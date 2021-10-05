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

long        START_CAPACITY          = 16;
long        START_SIZE_TYPE         = 1;
int         ERR_UNDEFINED           = UNDEFINED;

const int   FACTOR_INCR_CAPACITY    = 2;
const int   FACTOR_DECR_CAPACITY    = 2;
const char* LOGFILE_NAME            = "SkekLogFile.txt";
const int   PRINT_TYPE              = 1;


char SkekCtor   (struct Skek *my_skek, long amount_byte_type,
                long capacity, int* error) {
    // for deleted old logfile and create it also
    CleanLogFile(LOGFILE_NAME);

    if (!SkekVerif(my_skek, error, DEB_ELEM)) {
        return false;
    }

    if (my_skek->data != nullptr ||
        my_skek->capacity  != 0  ||
        my_skek->size      != 0  ||
        my_skek->type_size != 0) {

        *error = STACK_ALREADY_CREATED;
        SkekDump(my_skek, error, DEB_ELEM);
        return false;
    }

    if ((my_skek->data = (void *) calloc(capacity, amount_byte_type)) == nullptr) {
        *error = ERROR_ALLOCATE_MEMORY;
        SkekDump(my_skek, error, DEB_ELEM);
        return false;
    }

    my_skek->type_size = amount_byte_type;
    my_skek->size      = 0;
    my_skek->capacity  = capacity;
    START_CAPACITY     = capacity;
    if (!SkekVerif(my_skek, error, DEB_ELEM)) {
        return false;
    }
    return true;
}

char SkekDtor(struct Skek *my_skek, int *error) { // todo distrc for void
    if (!SkekVerif(my_skek, error, DEB_ELEM)) {
        return false;
    }

    kekset(my_skek->data, (void *) &ZOMBIE_NUMBER, my_skek->capacity, my_skek->type_size, error);

    free(my_skek->data);
    my_skek->size       = BAD_SIZE;
    my_skek->type_size  = BAD_SIZE;
    my_skek->capacity   = BAD_SIZE;
    my_skek->data       = (void *) FREE_ERROR_POINTER;

//    if (!SkekVerif(my_skek, error, DEB_ELEM)) {
//        return false;
//    }

    ERR_UNDEFINED = UNDEFINED;
    return true;
}

char SkekExtension(struct Skek *my_skek, int* error) {
    if (!SkekVerif(my_skek, error, DEB_ELEM)) {
        return false;
    }

    if (my_skek->size == my_skek->capacity) { // increase size

        printf("\n"
               "_____________________________\n"
               "_____________________________\n"
               "I'm SkekExtension\n"
               "I increase size memory:\n"
               "ptr on data:    %p\n"
               "size:           %ld\n"
               "type_size:      %ld\n"
               "capacity:       %ld\n"
               "will capacity:  %ld\n"
               "_____________________________\n"
               "_____________________________\n",
               my_skek->data, my_skek->size, my_skek->type_size,
               my_skek->capacity, my_skek->capacity * FACTOR_INCR_CAPACITY);

        my_skek->capacity *= FACTOR_INCR_CAPACITY;
        my_skek->data = (void *)realloc(my_skek->data,
                                        my_skek->capacity * my_skek->type_size);

        if (!SkekVerif(my_skek, error, DEB_ELEM)) {
            return false;
        }
        return true;
    }

    if (my_skek->size * FACTOR_DECR_CAPACITY <= my_skek->capacity &&
        my_skek->size > (long) START_CAPACITY / FACTOR_DECR_CAPACITY) {  // decrease size
        printf("\n"
               "_____________________________\n"
               "_____________________________\n"
               "I'm SkekExtension\n"
               "I decrease resize memory:\n"
               "ptr on data:    %p\n"
               "size:           %ld\n"
               "type_size:      %ld\n"
               "capacity:       %ld\n"
               "will capacity:  %ld\n"
               "_____________________________\n"
               "_____________________________\n",
               my_skek->data, my_skek->size, my_skek->type_size,
               my_skek->capacity, (long) my_skek->capacity / FACTOR_DECR_CAPACITY + 1);


        my_skek->capacity = (long) my_skek->capacity / FACTOR_DECR_CAPACITY + 1;
        my_skek->data = (void *) realloc(my_skek->data,
                                         my_skek->capacity * my_skek->type_size);

        if (!SkekVerif(my_skek, error, DEB_ELEM)) {
            return false;
        }
        return true;
    }

    return true;
}

void* SkekGet (struct Skek* my_skek, int* error) {
    if (!SkekVerif(my_skek, error, DEB_ELEM)) {
        return nullptr;
    }
    if (my_skek->size == 0) {
        *error = GET_WITHOUT_ELEM;
        SkekDump(my_skek, error, DEB_ELEM);
        return nullptr;
    }

    void* top_elem = (char *) my_skek->data + (my_skek->size - 1) * my_skek->type_size;

    if (top_elem == nullptr) {
        *error = NULLPTR_IN_DATA;
        SkekDump(my_skek, error, DEB_ELEM);
        return nullptr;
    }

    if (!SkekVerif(my_skek, error, DEB_ELEM)) {
        return nullptr;
    }
    return top_elem;
}


char SkekPush(struct Skek *my_skek, void* value, int* error) {
    if (!SkekVerif(my_skek, error, DEB_ELEM)) {
        return false;
    }
    if (!SkekExtension(my_skek, error)) return false;

    kekset((char *) my_skek->data + my_skek->size * my_skek->type_size,
           value, 1, my_skek->type_size, error);
    my_skek->size++;

    if (!SkekVerif(my_skek, error, DEB_ELEM)) {
        return false;
    }
    return true;
}

void* SkekPop (struct Skek* my_skek, int *error) {
    if (!SkekVerif(my_skek, error, DEB_ELEM)) {
        return nullptr;
    }
    if (my_skek->size == 0) {
        *error = POP_WITHOUT_ELEM;
        SkekDump(my_skek, error, DEB_ELEM);
        return nullptr;
    }

    void* elem = (void *) calloc(my_skek->type_size, sizeof (char));
    void* top_elem = (char *) my_skek->data + (my_skek->size - 1) * my_skek->type_size;

    kekset(elem, top_elem, 1,  my_skek->type_size);
    my_skek->size--;

    if (!SkekExtension(my_skek, error)) {
        return nullptr;
    }
    if (!SkekVerif(my_skek, error, DEB_ELEM)) {
        return nullptr;
    }
    return elem;
}

char SkekVerif (struct Skek* my_skek, int* error, struct debug_elements debElem, const char* name_logfile) {

    if (my_skek == nullptr) {
        *error = NULLPTR_ON_SKEK;
        SkekDump(my_skek, error, debElem, name_logfile);
        return false;
    }

    if (my_skek->size       == BAD_SIZE ||
        my_skek->type_size  == BAD_SIZE ||
        my_skek->capacity   == BAD_SIZE ||
        my_skek->data       == (void *) FREE_ERROR_POINTER) {

        *error = TWICE_ALLOCATE;
        SkekDump(my_skek, error, debElem, name_logfile);
        return false;
    }

    if (my_skek->size       < 0 ||
        my_skek->type_size  < 0 ||
        my_skek->capacity   < 0) {
        // todo 3 if and enumb errors for this
        *error = NEGATIVE_SIZE;
        SkekDump(my_skek, error, debElem, name_logfile);
        return false;
    }

    if (my_skek->size > my_skek->capacity) {
        *error = SIZE_LARGE_CAPACITY;
        SkekDump(my_skek, error, debElem, name_logfile);
        return false;
    }

    return true;
}

char SkekDump (struct Skek * my_skek, int *error,
               struct debug_elements debElem, const char* name_logfile) {

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

    // time
    struct tm *ptr;
    time_t It;
    It = time(NULL);
    ptr = localtime(&It);

    // todo define for color text


    // block input in console (i input onlu errors skeks
    if (*error != UNDEFINED) {

        printf("\n\x1b[32;1m"
               "TIME : %s"
               "START DUMP\n"
               "LAUNCHED FROM:\n\x1b[0m"
               "\x1b[33mFILE:\x1b[0m %s\n"
               "\x1b[33mFUNC:\x1b[0m %s\n"
               "\x1b[33mLINE:\x1b[0m %d\n\n",
               asctime(ptr),
               debElem.FILE, debElem.PRETTY_FUNCTION, debElem.LINE);


        printf("\x1b[31m"
               "!!!!ERROR SKEK!!!!\n"
               "SKEK ERROR NUMBER: %d\n That's mean: %s\n\n",
               *error, NAME_ERRORS.at(*error));

        printf("Skek->size:        %ld\n"
               "Skek->type_size:   %ld\n"
               "Skek->capacity:    %ld\n"
               "Skek->data:\n",
               my_skek->size, my_skek->type_size, my_skek->capacity);

        if (my_skek->data == nullptr ||
            my_skek->data == &FREE_ERROR_POINTER) {
            printf("skek hasn't data\n");
        }
        else {
            const char* type_elem = print_void_arr(my_skek->data, PRINT_TYPE,
                                             my_skek->size, my_skek->type_size);
            printf("\ntype of elements: %s\n", type_elem);
        }

        printf("END ERROR SKEK\n\x1b[0m");
    }

    // block input in file
    fprintf(file,"\n"
            "TIME : %s"
            "START DUMP\n"
            "LAUNCHED FROM:\n"
            "FILE: %s\n"
            "FUNC: %s\n"
            "LINE: %d\n\n",
            asctime(ptr),
            debElem.FILE, debElem.PRETTY_FUNCTION, debElem.LINE);

    if (*error != UNDEFINED) {
        fprintf(file,"!!!!ERROR SKEK!!!!\n"
                     "SKEK ERROR NUMBER: %d\n That's mean: %s\n\n",
               *error, NAME_ERRORS.at(*error));
    }

    else fprintf(file, "NORMAL SKEK\n");

    fprintf(file, "Skek->size:      %ld\n"
           "Skek->type_size: %ld\n"
           "Skek->capacity:  %ld\n"
           "Skek->data:\n",
           my_skek->size, my_skek->type_size, my_skek->capacity);

    if (my_skek->data == nullptr ||
        my_skek->data == &FREE_ERROR_POINTER) {
        fprintf(file, "Skek hasn't data\n");
    }
    else {
        const char* type_elem = file_print_void_arr(file, my_skek->data, PRINT_TYPE,
                                              my_skek->size, my_skek->type_size);

        fprintf(file, "\ntype of elements: %s\n", type_elem);
    }

    if (*error != UNDEFINED) fprintf(file, "END ERROR SKEK\n");
    else                     fprintf(file, "END SKEK\n");

    fprintf (file, "END DUMB\n\n");

    fclose (file);
    return true;
}

char CleanLogFile (const char* name_logfile, int* error) {
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


char kekset (void* ptr, void* elem, long count_elem, long type_size, int* error) {
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
        for (int type_byte = 0; type_byte < type_size; type_byte++) {
            // todo check can elem do *
            *(ptr_char + i * type_size + type_byte) =
                    *(elem_char + type_byte);
        }
    }

    return true;
}


const char* print_void_arr(void* ptr, int type, long count_elem, long type_size) {
    if (type == 0 && type_size == sizeof(bool)) {
        for (long numb_elem = 0; numb_elem < count_elem; numb_elem ++) {
            printf("data[%ld] = %d\n",
                   numb_elem, *((bool *) ptr + numb_elem));
        }
        return "bool";
    }

    if (type == 1) {
        switch (type_size) {
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
                return "int";

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
        switch (type_size) {
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

    for (long numb_elem = 0; numb_elem < count_elem; numb_elem ++) {
        for (long numb_byte = 0; numb_byte < type_size; numb_byte ++) {
            printf("data[%ld] = %02X",
                   numb_elem, *((char *) ptr + numb_elem + numb_byte));
        }
        printf("\n");
    }
    return "Hex";
}

const char* file_print_void_arr(FILE* file, void* ptr, int type, long count_elem, long type_size) {
    if (type == 0 && type_size == sizeof(bool)) {
        for (long numb_elem = 0; numb_elem < count_elem; numb_elem ++) {
            fprintf(file, "data[%ld] = %d\n",
                   numb_elem, *((bool *) ptr + numb_elem));
        }
        return "bool";
    }

    if (type == 1) {
        switch (type_size) {
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
                return "int";

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
        switch (type_size) {
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


    for (long numb_elem = 0; numb_elem < count_elem; numb_elem ++) {
        for (long numb_byte = 0; numb_byte < type_size; numb_byte ++) {
            printf("data[%ld] = %02X",
                   numb_elem, *((char *) ptr + numb_elem + numb_byte));
        }
        printf("\n");
    }
    return "Hex";
}