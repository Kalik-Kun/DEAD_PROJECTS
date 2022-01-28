//
// Created by arlik_null on 15.11.2021.
//

#ifndef KLIST_KLIST_H
#define KLIST_KLIST_H

#include <climits>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <cstring>

/// DEBUG
#define ABOBADEBAG



#define KL_DEB_ELEM(message) {__LINE__, __FILE__, __PRETTY_FUNCTION__, message}

#define KL_FUNC_ERROR_RTRN(var_error, name_error, return_value) \
    *(var_error) = name_error;\
    SMALL_DUMP(name_error)\
    return return_value;

#define KL_PRINT_ELEMS(spec) { \
    KL_SIZE_TYPE ptr = this->tale; \
    while(ptr != this->head) { \
        printf("buffer[%d]: ", ptr); \
        printf("%d  ->  "#spec"  ->  %d\n", \
                this->buffer[ptr].lp, this->buffer[ptr].val, this->buffer[ptr].rp); \
        ptr = this->buffer[ptr].rp;        \
    }                          \
    printf("buffer[%d]: ", ptr); \
    printf("%d  ->  "#spec"  ->  %d\n", \
            this->buffer[ptr].lp, this->buffer[ptr].val, this->buffer[ptr].rp); \
    printf("\n");\
}\


#define KL_PRINT_BUFF(spec) { \
    for (KL_SIZE_TYPE i = 0; i < this->buffer_size; i ++) {\
        printf("buffer[%d]: ", i);\
        printf("%d  ->  "#spec"  ->  %d\n",\
            this->buffer[i].lp, this->buffer[i].val, this->buffer[i].rp);\
    }\
    printf("\n");                     \
}

#define KL_FILE_PRINT_BUFF(file, spec) { \
    for (KL_SIZE_TYPE i = 0; i < this->buffer_size; i ++) {\
        fprintf(file, "buffer[%d]: ", i);\
        fprintf(file, "%d  ->  "#spec"  ->  %d\n",\
            this->buffer[i].lp, this->buffer[i].val, this->buffer[i].rp);\
    }\
    fprintf(file, "\n");                     \
}


typedef int KL_SIZE_TYPE;

extern const KL_SIZE_TYPE   KL_START_BUFFER_SIZE;


/// DEBUG VAR

// if KList::buffer have ptr 0x(KL_FREE_ERROR_POINTER) that KL_TWICE_ALLOCATE
extern const char KL_FREE_ERROR_POINTER;
// if KList::buffer have ptr 0x(FREE_ERROR_POINTER) that KL_TWICE_ALLOCATE
// (KL_ZOMBIE_NUMBER) fill KList::buffer when klist was deleted
extern const char KL_ZOMBIE_NUMBER;
// KL_BAD_SIZE - size when klist was deleted
extern const KL_SIZE_TYPE KL_BAD_SIZE;
// start value of pointers
extern const KL_SIZE_TYPE KL_START_SIZE;

extern const char*          KL_LOGFILE_NAME;
extern const char*          KL_GRAPHVIZFILE_NAME;
extern const char*          KL_PNG_NAME;




template <typename KL_TYPE = int>
class KList {

private:
    /// errors in KList class
    enum KL_ERRORS {
        KL_UNDEF,
        KL_BUFF_NULLPTR,
        KL_TWICE_ALLOCATE,
        KL_FILE_OPEN,
        KL_NEGATIVE_BUFFER_SIZE,
        KL_NEGATIVE_SIZE,
        KL_NEGATIVE_TALE,
        KL_NEGATIVE_HEAD,
        KL_NEGATIVE_FREE_PTR,
        KL_BUFFER_SIZE_LESS_THAN_HEAD,
        KL_BUFFER_SIZE_LESS_THAN_SIZE,
        KL_NULLPTR_IN_REALLOC,
    };


private:
    // -1 -> val -> -1
    struct KL_Data {
        KL_TYPE  val        = 0;
        KL_SIZE_TYPE lp     = KL_START_SIZE;
        KL_SIZE_TYPE rp     = KL_START_SIZE;
    }
                 *buffer         = nullptr;
    KL_SIZE_TYPE  buffer_size    = KL_START_BUFFER_SIZE;
    KL_SIZE_TYPE  size           = KL_START_SIZE;

    KL_SIZE_TYPE  tale           = KL_START_SIZE;
    KL_SIZE_TYPE  head           = KL_START_SIZE;

    KL_SIZE_TYPE  free_ptr           = KL_START_SIZE;

    const char* name_logfile     = KL_LOGFILE_NAME;
    KL_ERRORS     KL_ERR         = KL_UNDEF;
    KL_ERRORS*    error          = &KL_ERR;


private:
    /// DUMP

    /** kl debug elements - elem which show info about called func
    *  LINE - From which LINE the dump was called
    *  FILE - From which FILE the dump was called
    *  PRETTY_FUNCTION - From which FUNC the dump was called
    *  ERROR_MESSAGE   - error message
    *
    *  P.S.
    *  USE __ after and before name that give this param
    **/
    struct kl_debug_elements {
        int         LINE             = -1;
        const char* FILE             = "Don't know";
        const char* PRETTY_FUNCTION  = "Don't know";
        const char* ERROR_MESSAGE    = "Don't know";
    };

    void small_dump(kl_debug_elements debElem) {
        printf("\x1b[31m"
               "!!! ERROR KLIST!!!\n"
               "FILE: %s\n"
               "FUNC: %s\n"
               "LINE: %d\n"
               "CPU_ERRORS number: %d\n"
               "THAT MEAN: %s \n"
               "\x1b[0m",
               debElem.FILE, debElem.PRETTY_FUNCTION, debElem.LINE,
               *this->error, debElem.ERROR_MESSAGE);
    }


    bool KLVerif     (kl_debug_elements debElem);

    /// printf_buffer - print buffer in cmd\n
    /// WARNING - don't check buffer on errors\n
    void print_buffer();
    void file_print_buffer(FILE* file);

public:

    KList();
    explicit KList(KL_SIZE_TYPE buff_size);

    ~KList();

    bool KLPushBegin(KL_TYPE elem);
    bool KLPushEnd  (KL_TYPE elem);
    bool KLInsertAfter  (KL_SIZE_TYPE index, KL_TYPE elem);
    bool KLInsertBefore (KL_SIZE_TYPE index, KL_TYPE elem);
    KL_TYPE KLDelete (KL_SIZE_TYPE index);

    bool KLExtension ();
    bool KLDump      (kl_debug_elements debElem);


    KL_SIZE_TYPE get_size();
    int get_error();
    const char* get_logfile_name();

    void        set_logfile_name(const char* name);

    void print_elems();
};

#include "KList_impl.h"

#endif //KLIST_KLIST_H
