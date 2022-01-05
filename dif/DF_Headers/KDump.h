//
// Created by arlik_null on 22.11.2021.
//

#ifndef DIF_KDUMP_H
#define DIF_KDUMP_H

#define RED     "\x1b[31m"
#define ZERO    "\x1b[0m"

#define SMALL_DUMP(error_text) \
printf( RED                    \
        "ERROR\n"\
        "FILE: %s\n"\
        "FUNC: %s\n"\
        "LINE: %d\n"\
        "DF_ERRORS number: %d\n"\
        "THAT MEAN:" #error_text "\n"\
        ZERO,              \
        __FILE__, __PRETTY_FUNCTION__, __LINE__, error_text);

#define FUNC_ERROR(var_error, name_error) \
    *(var_error) = name_error;\
    SMALL_DUMP(name_error)\
    return false;

#define FUNC_ERROR_RTRN(var_error, name_error, return_value) \
    *(var_error) = name_error;\
    SMALL_DUMP(name_error)\
    return return_value;


#define CHECK_FOR_ERR(error, return_value) \
    if(*(error) != DF_UND) return (return_value);

#define Sintax_error(old_size, new_size, name_error) \
    if (old_size == new_size) {           \
        FUNC_ERROR_RTRN(error, name_error, false)                                      \
    }


enum DF_ERRORS {
    DFERR_UND,

    DFERR_POINTER_DONT_MOVE_IN_OWN,
    DFERR_POINTER_DONT_MOVE_IN_LINE,
    DFERR_POINTER_DONT_MOVE_IN_SPACE,
    DFERR_POINTER_DONT_MOVE_IN_PLUS,
    DFERR_POINTER_DONT_MOVE_IN_MINUS,
    DFERR_POINTER_DONT_MOVE_IN_MULT,
    DFERR_POINTER_DONT_MOVE_IN_DIV,
    DFERR_SECOND_PLUS,

    DFERR_NULLPTR_IN_CALLOC,
};

extern DF_ERRORS DF_ERR;

#endif //DIF_KDUMP_H
