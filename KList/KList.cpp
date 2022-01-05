//
// Created by arlik_null on 15.11.2021.
//

#include "KList.h"

const KL_SIZE_TYPE KL_BUFFER_SIZE = CHAR_MAX;
const KL_SIZE_TYPE KL_START_SIZE_TYPE = sizeof(char);
KL_ERRORS KL_GLOB_ERR = KLIST_UNDEF;

bool KListCtor(KList* klist,
               KL_SIZE_TYPE type_size, KL_SIZE_TYPE buffer_size,
               KL_ERRORS* error) {

    klist->type_size = type_size;
    klist->buffer_size = buffer_size;
    klist->buffer = calloc(buffer_size * type_size, sizeof(char));



    return true;
}
