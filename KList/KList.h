//
// Created by arlik_null on 15.11.2021.
//

#ifndef KLIST_KLIST_H
#define KLIST_KLIST_H

#include <climits>
#include <stdlib.h>

typedef int KL_SIZE_TYPE;
typedef int KL_TYPE;

enum KL_ERRORS {
    KLIST_UNDEF,
};


extern const KL_SIZE_TYPE   KL_BUFFER_SIZE;
extern const KL_SIZE_TYPE   KL_START_SIZE_TYPE;
extern KL_ERRORS            KL_GLOB_ERR;

struct KL_Data {
    KL_TYPE* val    = nullptr;
    KL_Data* lp = nullptr;
    KL_Data* rp = nullptr;
};

struct KList {
    KL_Data* buffer                 = nullptr;

    KL_SIZE_TYPE  buffer_size    = KL_BUFFER_SIZE;

    KL_SIZE_TYPE  left_ptr       = 0;
    KL_SIZE_TYPE  right_ptr      = 0;

};

bool KListCtor  (KList* klist,
                 KL_SIZE_TYPE type_size = KL_START_SIZE_TYPE,
                 KL_SIZE_TYPE buffer_size = KL_BUFFER_SIZE,
                 KL_ERRORS* error = &KL_GLOB_ERR);

bool KLISTDtor  (KList* klsit,
                 KL_ERRORS* error = &KL_GLOB_ERR);

bool KListExtension (KList* klist,
                     KL_ERRORS* error = &KL_GLOB_ERR);

bool KListPop       (KList* klist, KL_SIZE_TYPE number,
                     KL_ERRORS* error = &KL_GLOB_ERR);

bool KListAdd       (KList)

#endif //KLIST_KLIST_H
