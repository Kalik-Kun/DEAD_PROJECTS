//
// Created by arlik_null on 20.09.2021.
//

#include "LibStack.h"

const char FREE_ERROR_POINTER       = 13;
const char ZOMBIE_NUMBER            = 17;
const long BAD_SIZE                 = LONG_MAX - 3453;

const long  CANARY_FRONT            = 0xD0D0B00B5;
const long  CANARY_BEHIND           = 0xD0D0B00B5;
const long  CANARY_DATA_FRONT       = 0xD0D0B00B5;
const long  CANARY_DATA_BEHIND      = 0xD0D0B00B5;

const char* LOGFILE_NAME            = "SkekLogFile.txt";
long        START_CAPACITY          = 16;
long        START_SIZE_TYPE         = 1;
int         ERR_UNDEFINED           = UNDEFINED_SKEK;
const int   FACTOR_INCR_CAPACITY    = 2;
const int   FACTOR_DECR_CAPACITY    = 2;
const int   PRINT_TYPE              = 1214;

char SkekCtor   (struct Skek *my_skek, long amount_byte_type,
                long capacity, int* error) {
    // for deleted old logfile and create it also
    CleanLogFile(LOGFILE_NAME);

    if (!SkekVerif(my_skek, error, DEB_ELEM("Don't know"))) {
        return false;
    }

    if (my_skek->data != nullptr ||
        my_skek->capacity  != 0  ||
        my_skek->size      != 0  ||
        my_skek->type_size != 0) {

        *error = STACK_ALREADY_CREATED;
        SkekDump(my_skek, DEB_ELEM("STACK_ALREADY_CREATED"), LOGFILE_NAME, error);
        return false;
    }

    #ifdef NO_DEFENSE
        if ((my_skek->data = (void *) calloc(capacity, amount_byte_type)) == nullptr) {
            *error = ERROR_ALLOCATE_MEMORY_SKEK;
            SkekDump(my_skek, error, DEB_ELEM("ERROR_ALLOCATE_MEMORY_SKEK"));
            return false;
        }
    #endif

    #ifndef NO_DEFENSE
        if ((my_skek->canary_data_front = (void *) calloc(capacity * amount_byte_type + 2 * sizeof(long) + 1, sizeof(char))) == nullptr) {
            *error = ERROR_ALLOCATE_MEMORY_SKEK;
            SkekDump(my_skek, DEB_ELEM("ERROR_ALLOCATE_MEMORY_SKEK"), LOGFILE_NAME, error);
            return false;
        }
        kekset(my_skek->canary_data_front, (void *) &CANARY_DATA_FRONT,
               1, sizeof(long), error);

        my_skek->data               = (void *) ((char *) my_skek->canary_data_front + sizeof(long));
        my_skek->canary_data_behind = (void *) ((char *) my_skek->data + capacity * amount_byte_type);

        kekset(my_skek->canary_data_behind, (void *) &CANARY_DATA_BEHIND,
               1, sizeof(long), error);
    #endif

    #ifdef SECOND_DEFENSE_LAYER
        my_skek->hash = MyHashCalc(my_skek->data, my_skek->size, error);
    #endif

    my_skek->type_size = amount_byte_type;
    my_skek->size      = 0;
    my_skek->capacity  = capacity;
    START_CAPACITY     = capacity;

    if (!SkekVerif(my_skek, error, DEB_ELEM("Don't know"))) {
        return false;
    }
    return true;
}

char SkekDtor(struct Skek *my_skek, int *error) {
    if (!SkekVerif(my_skek, error, DEB_ELEM("Don't know"))) {
        return false;
    }
    #ifdef NO_DEFENSE
        kekset(my_skek->data, (void *) &ZOMBIE_NUMBER, my_skek->capacity, my_skek->type_size, error);
        free(my_skek->data);
    #else
        kekset(my_skek->canary_data_front, (void *) &ZOMBIE_NUMBER,
               sizeof(long)/sizeof(char), sizeof(char), error);
        kekset(my_skek->data, (void *) &ZOMBIE_NUMBER, my_skek->capacity, my_skek->type_size, error);
        kekset(my_skek->canary_data_behind, (void *) &ZOMBIE_NUMBER,
               sizeof(long)/sizeof(char), sizeof(char), error);

        free(my_skek->canary_data_front);
        my_skek->canary_front       = ZOMBIE_NUMBER;
        my_skek->canary_behind      = ZOMBIE_NUMBER;
        my_skek->canary_data_front  = (void*) FREE_ERROR_POINTER;
        my_skek->canary_data_behind = (void*) FREE_ERROR_POINTER;
    #endif

    #ifdef SECOND_DEFENSE_LAYER
        my_skek->hash = 0;
    #endif

    my_skek->size       = BAD_SIZE;
    my_skek->type_size  = BAD_SIZE;
    my_skek->capacity   = BAD_SIZE;
    my_skek->data       = (void *) FREE_ERROR_POINTER;

//    if (!SkekVerif(my_skek, error, DEB_ELEM("Don't know")) {
//        return false;
//    }

    ERR_UNDEFINED = UNDEFINED_SKEK;
    return true;
}

char SkekExtension(struct Skek *my_skek, int* error) {
    if (!SkekVerif(my_skek, error, DEB_ELEM("Don't know"))) {
        return false;
    }

    if (my_skek->size == my_skek->capacity) { // increase size

        printf("\n\x1b[32;1m"
               "_____________________________\n"
               "_____________________________\n"
               "I'm SkekExtension\n"
               "I increase size memory:\n"
               "ptr on data:       %p\n"
               "size:              %ld\n"
               "type_size:         %ld\n"
               "capacity:          %ld\n"
               "capacity will be:  %ld\n"
               "_____________________________\n"
               "_____________________________\n"
               "\x1b[0m",
               my_skek->data, my_skek->size, my_skek->type_size,
               my_skek->capacity, my_skek->capacity * FACTOR_INCR_CAPACITY);

        my_skek->capacity *= FACTOR_INCR_CAPACITY;

        #ifdef NO_DEFENSE

        void* error_var = (void *)realloc(my_skek->data,
                                        my_skek->capacity * my_skek->type_size);
        if (error_var == nullptr) {
            *error = NULLPTR_IN_REALOC_SKEK;
            SkekDump(my_skek, error, DEB_ELEM("NULLPTR_IN_REALLOC_IN_INCREASE_EXTENSION"));
            return false;
        }
        my_skek->data = error_var;
        #else
        void* error_var = (void *) realloc(my_skek->canary_data_front,
                                            my_skek->capacity * my_skek->type_size + 2*sizeof(long));
        if (error_var == nullptr) {
            *error = NULLPTR_IN_REALOC_SKEK;
            SkekDump(my_skek, DEB_ELEM("NULLPTR_IN_REALLOC_IN_INCREASE_EXTENSION"), LOGFILE_NAME, error);
            return false;
        }
        my_skek->canary_data_front = error_var;

        my_skek->data = (char *) my_skek->canary_data_front + sizeof(CANARY_DATA_FRONT);
        my_skek->canary_data_behind = (char*) my_skek->data +
                                      my_skek->capacity * my_skek->type_size;
        kekset(my_skek->canary_data_behind, (void*) &CANARY_DATA_BEHIND,
               1, sizeof(CANARY_DATA_BEHIND), error);
        #endif

        if (!SkekVerif(my_skek, error, DEB_ELEM("Don't know"))) {
            return false;
        }
        return true;
    }

    if (my_skek->size * FACTOR_DECR_CAPACITY <= my_skek->capacity &&
        my_skek->size > (long) START_CAPACITY / FACTOR_DECR_CAPACITY) {  // decrease size
        printf("\n\x1b[32;1m"
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
               "_____________________________\n"
               "\x1b[0m",
               my_skek->data, my_skek->size, my_skek->type_size,
               my_skek->capacity, (long) my_skek->capacity / FACTOR_DECR_CAPACITY + 1);


        my_skek->capacity = (long) my_skek->capacity / FACTOR_DECR_CAPACITY + 1;

        #ifdef NO_DEFENSE
            void* error_var = (void *) realloc(my_skek->data,
                                         my_skek->capacity * my_skek->type_size);

            if (error_var == nullptr) {
                *error = NULLPTR_IN_REALOC_SKEK;
                SkekDump(my_skek, error, DEB_ELEM("NULLPTR_IN_REALLOC_IN_DECREASE_EXTENSION"));
                return false;
            }
            my_skek->data = error_var;

        #else
            void* error_var = (void *) realloc(my_skek->canary_data_front,
                                         my_skek->capacity * my_skek->type_size + 2*sizeof(long));
            if (error_var == nullptr) {
                *error = NULLPTR_IN_REALOC_SKEK;
                SkekDump(my_skek, DEB_ELEM("NULLPTR_IN_REALLOC_IN_DECREASE_EXTENSION"), LOGFILE_NAME, error);
                return false;
            }
            my_skek->canary_data_front = error_var;

            my_skek->data = (char *)my_skek->canary_data_front + sizeof(long);

            my_skek->canary_data_behind = (char*) my_skek->data +
                                          my_skek->capacity * my_skek->type_size;
            kekset(my_skek->canary_data_behind, (void*) &CANARY_DATA_BEHIND,
                                            1, sizeof(long), error);
        #endif

        if (!SkekVerif(my_skek, error, DEB_ELEM("Don't know"))) {
            return false;
        }
        return true;
    }

    return true;
}

char SkekGet (struct Skek* my_skek, void* buffer, int* error) {
    if (!SkekVerif(my_skek, error, DEB_ELEM("Don't know"))) {
        return false;
    }
    if (buffer == nullptr) {
        *error = NULLPTR_ON_BUFFER_SKEK;
        SkekDump(my_skek, DEB_ELEM("NULLPTR_ON_BUFFER_IN_SKEKGET"), LOGFILE_NAME, error);
        return false;
    }
    if (my_skek->size == 0) {
        *error = GET_WITHOUT_ELEM_SKEK;
        SkekDump(my_skek, DEB_ELEM("GET_WITHOUT_ELEM_SKEK"), LOGFILE_NAME, error);
        return false;
    }

    void* top_elem = ((char *) my_skek->data + (my_skek->size - 1) * my_skek->type_size);

    if (top_elem == nullptr) {
        *error = NULLPTR_IN_DATA_SKEK;
        SkekDump(my_skek, DEB_ELEM("NULLPTR_IN_DATA_SKEK"), LOGFILE_NAME, error);
        return false;
    }

    kekset(buffer, top_elem, 1,  my_skek->type_size);

    if (!SkekVerif(my_skek, error, DEB_ELEM("Don't know"))) {
        return false;
    }
    return true;
}


char SkekPush(struct Skek *my_skek, void* value, int* error) {
    if (!SkekVerif(my_skek, error, DEB_ELEM("Don't know"))) {
        return false;
    }
    if (!SkekExtension(my_skek, error)) return false;

    kekset((char *) my_skek->data + my_skek->size * my_skek->type_size,
           value, 1, my_skek->type_size, error);
    my_skek->size++;

    #ifdef SECOND_DEFENSE_LAYER
    my_skek->hash = MyHashCalc(my_skek->data, my_skek->size, error);
    #endif

    if (!SkekVerif(my_skek, error, DEB_ELEM("Don't know"))) {
        return false;
    }
    return true;
}

char SkekPop (struct Skek* my_skek, void* buff, int *error) {
    if (!SkekVerif(my_skek, error, DEB_ELEM("Don't know"))) {
        return false;
    }
    if (buff == nullptr) {
        *error = NULLPTR_ON_BUFFER_SKEK;
        SkekDump(my_skek, DEB_ELEM("NULLPTR_ON_SKEK_IN_SKEKPOP"), LOGFILE_NAME, error);
        return false;
    }
    if (my_skek->size == 0) {
        *error = POP_WITHOUT_ELEM_SKEK;
        SkekDump(my_skek, DEB_ELEM("POP_WITHOUT_ELEM_SKEK"), LOGFILE_NAME, error);
        return true;
    }

    void* top_elem = (char *) my_skek->data + (my_skek->size - 1) * my_skek->type_size;

    kekset(buff, top_elem, 1,  my_skek->type_size);
    my_skek->size--;

    #ifdef SECOND_DEFENSE_LAYER
        my_skek->hash = MyHashCalc(my_skek->data, my_skek->size, error);
    #endif

    if (!SkekExtension(my_skek, error)) {
        return false;
    }
    if (!SkekVerif(my_skek, error, DEB_ELEM("Don't know"))) {
        return false;
    }
    return true;
}

char SkekVerif (struct Skek* my_skek, int* error, struct debug_elements debElem, const char* name_logfile) {

    if (my_skek == nullptr) {
        *error = NULLPTR_ON_SKEK;
        debElem.ERROR_MESSAGE = "NULLPTR_ON_SKEK";
        SkekDump(my_skek, debElem, name_logfile, error);
        return false;
    }

    if (my_skek->size       == BAD_SIZE ||
        my_skek->type_size  == BAD_SIZE ||
        my_skek->capacity   == BAD_SIZE ||
        my_skek->data       == (void *) FREE_ERROR_POINTER) {

        *error = TWICE_ALLOCATE_IN_SKEK;
        debElem.ERROR_MESSAGE = "TWICE_ALLOCATE_IN_SKEK";
        SkekDump(my_skek, debElem, name_logfile, error);
        return false;
    }

    if (my_skek->size       < 0 ||
        my_skek->type_size  < 0 ||
        my_skek->capacity   < 0) {

        *error = NEGATIVE_SIZE_SKEK;
        debElem.ERROR_MESSAGE = "NEGATIVE_SIZE_SKEK";
        SkekDump(my_skek, debElem, name_logfile, error);
        return false;
    }


    if (my_skek->size > my_skek->capacity) {
        *error = SIZE_LARGE_CAPACITY;
        debElem.ERROR_MESSAGE = "SIZE_LARGE_CAPACITY";
        SkekDump(my_skek, debElem, name_logfile, error);
        return false;
    }

    #ifndef NO_DEFENSE

        if (my_skek->canary_front != CANARY_FRONT) {
            *error = CANARY_FRONT_DIE_SKEK;
            debElem.ERROR_MESSAGE = "CANARY_FRONT_DIE_SKEK";
            SkekDump(my_skek, debElem, name_logfile, error);
            printf("\n\x1b[31b"
                   "Canary Die\n"
                   "Name ding front canary: %lX\n\n"
                   "\x1b[0m", my_skek->canary_front);
            return false;
        }

        if (my_skek->canary_behind != CANARY_BEHIND) {
            *error = CANARY_BEHIND_DIE_SKEK;
            debElem.ERROR_MESSAGE = "CANARY_BEHIND_DIE_SKEK";
            SkekDump(my_skek, debElem, name_logfile, error);
            printf("\n\x1b[31b"
                   "Canary Die\n"
                   "Name ding behind canary: %lX\n\n"
                   "\x1b[0m", my_skek->canary_front);
            return false;
        }

        if (my_skek->canary_data_front != nullptr &&
            *(long*)my_skek->canary_data_front != CANARY_DATA_FRONT) {
            *error = CANARY_DATA_FRONT_DIE_SKEK;
            debElem.ERROR_MESSAGE = "CANARY_DATA_FRONT_DIE_SKEK";
            SkekDump(my_skek, debElem, name_logfile, error);
            printf("\n\x1b[31b"
                   "Canary Die\n"
                   "Name ding front data canary: %lX\n\n"
                   "\x1b[0m", *(long*)my_skek->canary_data_front);
            return false;
        }

        if (my_skek->canary_data_behind != nullptr &&
                *(long*)my_skek->canary_data_behind != CANARY_DATA_BEHIND) {
            *error = CANARY_DATA_BEHIND_DIE_SKEK;
            debElem.ERROR_MESSAGE = "CANARY_DATA_BEHIND_DIE_SKEK";
            SkekDump(my_skek, debElem, name_logfile, error);
            printf("\n\x1b[31b"
                   "Canary die\n"
                   "Name ding behind data canary: %lX\n\n"
                   "\x1b[0m", *(long*)my_skek->canary_data_behind);
            return false;
        }

    #endif
    #ifdef SECOND_DEFENSE_LAYER
        unsigned long long old_hash = my_skek->hash;
        my_skek->hash = 0;
        my_skek->hash = MyHashCalc(my_skek->data, my_skek->size, error);
        if (old_hash != my_skek->hash) {
            *error = INCONSISTENCY_HASHES_IN_SKEK;
            debElem.ERROR_MESSAGE = "INCONSISTENCY_HASHES_IN_SKEK";
            SkekDump(my_skek, debElem, name_logfile, error);
            printf ("\n\x1b[31m"
                    "BAD HASHES\n"
                    "OLD HASH: %lld\n"
                    "NEW HASH: %lld\n",
                    old_hash, my_skek->hash);
            return 0;
        }
    #endif


    return true;
}

char SkekDump (struct Skek * my_skek, struct debug_elements debElem,
                const char* name_logfile, int *error) {

    FILE* file = fopen(name_logfile, "a");
    if (file == nullptr) {
        printf("\x1b[31;5m"
               "ERROR: file can't input\n"
               "Please reload program\n"
               "\x1b[0m");
        *error = FILE_OPEN_SKEK;
        return false;
    }

    // time
    struct tm *ptr;
    time_t It;
    It = time(NULL);
    ptr = localtime(&It);

    // block input in console (i input onlu errors skeks)
    if (*error != UNDEFINED_SKEK) {

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
               "SKEK ERROR NUMBER: %d\n"
               "That's mean: %s\n\n",
               *error, debElem.ERROR_MESSAGE);

        print_status_skek(my_skek, error);

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

    if (*error != UNDEFINED_SKEK) {
        fprintf(file,"!!!!ERROR SKEK!!!!\n"
                     "SKEK ERROR NU MBER: %d\n"
                     "That's mean: %s\n\n",
               *error, debElem.ERROR_MESSAGE);
    }

    else fprintf(file, "NORMAL SKEK\n"
                       "MESSAGE: %s\n", debElem.ERROR_MESSAGE);

    fprint_status_skek(my_skek, file, error);

    if (my_skek->data == nullptr ||
        my_skek->data == &FREE_ERROR_POINTER) {
        fprintf(file, "Skek hasn't data\n");
    }
    else {
        const char* type_elem = file_print_void_arr(file, my_skek->data, PRINT_TYPE,
                                                  my_skek->size, my_skek->type_size);

        fprintf(file, "\ntype of elements: %s\n", type_elem);
    }

    if (*error != UNDEFINED_SKEK) fprintf(file, "END ERROR SKEK\n");
    else                          fprintf(file, "END SKEK\n");

    fprintf (file, "END DUMB\n\n");

    fclose (file);
    return true;
}

char CheckRemSkek (struct Skek* my_skek) {
//#ifdef NO_DEFENSE
//    kekset(my_skek->data, (void *) &ZOMBIE_NUMBER, my_skek->capacity, my_skek->type_size, error);
//        free(my_skek->data);
//#else
//    kekset(my_skek->canary_data_front, (void *) &ZOMBIE_NUMBER,
//           sizeof(long)/sizeof(char), sizeof(char), error);
//    kekset(my_skek->data, (void *) &ZOMBIE_NUMBER, my_skek->capacity, my_skek->type_size, error);
//    kekset(my_skek->canary_data_behind, (void *) &ZOMBIE_NUMBER,
//           sizeof(long)/sizeof(char), sizeof(char), error);
//
//    free(my_skek->canary_data_front);
//    my_skek->canary_front       = ZOMBIE_NUMBER;
//    my_skek->canary_behind      = ZOMBIE_NUMBER;
//    my_skek->canary_data_front  = (void*) FREE_ERROR_POINTER;
//    my_skek->canary_data_behind = (void*) FREE_ERROR_POINTER;
    if (my_skek == nullptr) {
        // because false it's normal worked skek
        return true;
    }

    #ifdef NO_DEFENSE
        if (my_skek->size == BAD_SIZE       &&
            my_skek->type_size == BAD_SIZE  &&
            my_skek->capacity  == BAD_SIZE  &&
            my_skek->data == (void*) FREE_ERROR_POINTER) {
            return true;
        }
    #endif

    #ifdef FIRST_DEFENSE_LAYER
        if (my_skek->size       == BAD_SIZE             &&
            my_skek->type_size  == BAD_SIZE             &&
            my_skek->capacity   == BAD_SIZE             &&
            my_skek->data == (void*) FREE_ERROR_POINTER &&
            my_skek->canary_front == ZOMBIE_NUMBER      &&
            my_skek->canary_behind == ZOMBIE_NUMBER     &&
            my_skek->canary_data_front == (void*) FREE_ERROR_POINTER &&
            my_skek->canary_data_behind == (void*) FREE_ERROR_POINTER){

            return true;
        }
    #endif

    #ifdef SECOND_DEFENSE_LAYER
    if (my_skek->size       == BAD_SIZE             &&
        my_skek->type_size  == BAD_SIZE             &&
        my_skek->capacity   == BAD_SIZE             &&
        my_skek->data == (void*) FREE_ERROR_POINTER &&
        my_skek->canary_front == ZOMBIE_NUMBER      &&
        my_skek->canary_behind == ZOMBIE_NUMBER     &&
        my_skek->canary_data_front == (void*) FREE_ERROR_POINTER  &&
        my_skek->canary_data_behind == (void*) FREE_ERROR_POINTER &&
        my_skek->hash == 0){

        return true;
    }
    #endif

    return false;
}


char kekset (void* ptr, void* elem, long count_elem, long type_size, int* error) {
    if (ptr == nullptr) {
        *error = NULLPTR_ARRAY_KEKSET;
        return false;
    }
    if (elem == nullptr) {
        *error = NULLPTR_ELEM_KEKSET;
        return false;
    }

    char* elem_char = (char*) elem;
    char* ptr_char  = (char*) ptr;

    for (long i = 0; i < count_elem; i ++) {
        for (int type_byte = 0; type_byte < type_size; type_byte++) {
            *(ptr_char + i * type_size + type_byte) =
                    *(elem_char + type_byte);
        }
    }

    return true;
}

char CleanLogFile (const char* name_logfile, int* error) {
    FILE* file = fopen(name_logfile, "w");

    if (file == nullptr) {
        printf("\x1b[31;5m"
               "ERROR: file can't input\n"
               "Please reload program\n"
               "\x1b[0m");
        *error = FILE_OPEN_SKEK;
        return false;
    }
    fclose(file);
    return true;
}


char fprint_status_skek(struct Skek* my_skek, FILE* file, int* error) {
#ifdef NO_DEFENSE
    fprintf(file, "Skek->size:        %ld\n"
          "Skek->type_size:   %ld\n"
          "Skek->capacity:    %ld\n"
          "Skek->data:\n",
    my_skek->size, my_skek->type_size, my_skek->capacity);
#elifdef FIRST_DEFENSE_LAYER
    fprintf(file, "Skek->size:        %ld\n"
         "Skek->type_size:   %ld\n"
         "Skek->capacity:    %ld\n"
         "Skek->canary_front:         %lX\n"
         "Skek->canary_behind:        %lX\n"
         "Skek->canary_data_front:    %lX\n"
         "Skek->canary_data_behind:   %lX\n"
         "Skek->data:\n",
    my_skek->size, my_skek->type_size, my_skek->capacity,
    my_skek->canary_front, my_skek->canary_behind,
    *(long*)my_skek->canary_data_front, *(long*)my_skek->canary_data_behind);
#else
    fprintf(file, "Skek->size:        %ld\n"
           "Skek->type_size:   %ld\n"
           "Skek->capacity:    %ld\n"
           "Skek->hash:                 %lld\n"
           "Skek->canary_front:         %lX\n"
           "Skek->canary_behind:        %lX\n"
           "Skek->canary_data_front:    %lX\n"
           "Skek->canary_data_behind:   %lX\n"
           "Skek->data:\n",
           my_skek->size, my_skek->type_size, my_skek->capacity,
           my_skek->hash, my_skek->canary_front, my_skek->canary_behind,
           *(long*)my_skek->canary_data_front, *(long*)my_skek->canary_data_behind);
#endif
        return true;
}

char print_status_skek (struct Skek* my_skek, int* error) {
#ifdef NO_DEFENSE
    printf("Skek->size:        %ld\n"
          "Skek->type_size:   %ld\n"
          "Skek->capacity:    %ld\n"
          "Skek->data:\n",
    my_skek->size, my_skek->type_size, my_skek->capacity);
#elifdef FIRST_DEFENSE_LAYER
    printf("Skek->size:        %ld\n"
         "Skek->type_size:   %ld\n"
         "Skek->capacity:    %ld\n"
         "Skek->canary_front:         %lX\n"
         "Skek->canary_behind:        %lX\n"
         "Skek->canary_data_front:    %lX\n"
         "Skek->canary_data_behind:   %lX\n"
         "Skek->data:\n",
    my_skek->size, my_skek->type_size, my_skek->capacity,
    my_skek->canary_front, my_skek->canary_behind,
    *(long*)my_skek->canary_data_front, *(long*)my_skek->canary_data_behind);
#else
    printf("Skek->size:        %ld\n"
           "Skek->type_size:   %ld\n"
           "Skek->capacity:    %ld\n"
           "Skek->hash:                 %lld\n"
           "Skek->canary_front:         %lX\n"
           "Skek->canary_behind:        %lX\n"
           "Skek->canary_data_front:    %lX\n"
           "Skek->canary_data_behind:   %lX\n"
           "Skek->data:\n",
       my_skek->size, my_skek->type_size, my_skek->capacity,
       my_skek->hash, my_skek->canary_front, my_skek->canary_behind,
       *(long*)my_skek->canary_data_front, *(long*)my_skek->canary_data_behind);
#endif
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
        printf("data[%ld] = ", numb_elem);
        for (long numb_byte = 0; numb_byte < type_size; numb_byte ++) {
            printf("%02X",
                    *((char *) ptr + numb_elem * type_size + numb_byte));
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
        fprintf(file, "data[%ld] = ", numb_elem);
        for (long numb_byte = 0; numb_byte < type_size; numb_byte ++) {
            fprintf(file, "%02X",
                   *((char *) ptr + numb_elem * type_size + numb_byte));
        }
        fprintf(file, "\n");
    }
    return "Hex";
}

unsigned long long MyHashCalc(void* ptr, long len, int* error)
{
    const unsigned int m = 0x5bd1e995;
    const unsigned int seed = 0;
    const int r = 24;

    unsigned int h = seed ^ len;

    const unsigned char * data = (const unsigned char *)ptr;
    unsigned int k;

    while (len >= 4)
    {
        k  = data[0];
        k |= data[1] << 8;
        k |= data[2] << 16;
        k |= data[3] << 24;

        k *= m;
        k ^= k >> r;
        k *= m;

        h *= m;
        h ^= k;

        data += 4;
        len -= 4;
    }

    switch (len)
    {
        case 3:
            h ^= data[2] << 16;
        case 2:
            h ^= data[1] << 8;
        case 1:
            h ^= data[0];
            h *= m;
    };

    h ^= h >> 13;
    h *= m;
    h ^= h >> 15;

    return h;
}