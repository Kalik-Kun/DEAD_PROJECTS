//
// Created by arlik_null on 22.11.2021.
//

#include "../DF_Headers/KLexer.h"


KLexemArr KLexer (const char* file_name, DF_ERRORS* error) {
    FILE* file = fopen(file_name, "w");
    size_t size_file = out_file_size(file_name);

    KLexemArr LexArr    = {};
    char* buffer        = nullptr;

    LexArr.data = (KLexem*) calloc(size_file, sizeof(KLexem));
    buffer      = (char*)   calloc(size_file, sizeof(KLexem));

    if (LexArr.data == nullptr) {
        FUNC_ERROR_RTRN(error, DFERR_NULLPTR_IN_CALLOC, {})
    }
    if (buffer == nullptr) {
        FUNC_ERROR_RTRN(error, DFERR_NULLPTR_IN_CALLOC, {});
    }

    fread(buffer, sizeof(char), size_file, file);

    for (size_t num_buffer = 0, num_lex; num_buffer < size_file;) {
        size_t old_buffer = num_buffer;
        bool ind_error = false;

        ind_error = KLexLine(&num_buffer, &num_lex, buffer, &LexArr, error);

        if (old_buffer == num_buffer && ind_error) {
            FUNC_ERROR_RTRN(error, DFERR_POINTER_DONT_MOVE_IN_OWN, {})
        }

    }

}

bool KLexLine (size_t* num_buffer, size_t* num_lex, char* buffer, KLexemArr* LexArr, DF_ERRORS* error) {

    size_t old_buffer = *num_buffer;

    if (strncmp(&buffer[*num_buffer],
                DF_LINE.name,
                DF_LINE.len) != 0) {
        if (!KLexSpace(num_buffer, num_lex, buffer, LexArr, error)) {
            return false;
        }
    }

    if (strncmp(&buffer[*num_buffer],
                DF_LINE.name,
                DF_LINE.len) == 0) {

        LexArr->data[*num_lex].val = (char*)calloc(DF_LINE.len, sizeof(char));
        strncpy(LexArr->data[*num_lex].val, DF_LINE.name, DF_LINE.len);
        LexArr->data[*num_lex].indef = IDDF_LINE;


        *num_buffer += DF_LINE.len;
        *num_lex    += DF_LINE.len;
        return true;
    }

    Sintax_error(old_buffer, *num_buffer, DFERR_POINTER_DONT_MOVE_IN_LINE)
    return true;
}

bool KLexSpace  (size_t* num_buffer, size_t* num_lex, char* buffer, KLexemArr* LexArr, DF_ERRORS* error) {

    size_t old_buffer = *num_buffer;

    if (strncmp(&buffer[*num_buffer],
                DF_SPACE.name,
                DF_SPACE.len) != 0) {
        if (!KLexPlus(num_buffer, num_lex, buffer, LexArr, error))
            return false;
    }

    if (strncmp(&buffer[*num_buffer],
                DF_SPACE.name,
                DF_SPACE.len) == 0) {

        LexArr->data[*num_lex].val = (char*)calloc(DF_SPACE.len, sizeof(char));
        strncpy(LexArr->data[*num_lex].val, DF_SPACE.name, DF_SPACE.len);
        LexArr->data[*num_lex].indef = IDDF_SPACE;


        *num_buffer += DF_SPACE.len;
        *num_lex    += DF_SPACE.len;
        return true;
    }

    Sintax_error(old_buffer, *num_buffer, DFERR_POINTER_DONT_MOVE_IN_SPACE)
    return true;
}


bool KLexPlus  (size_t* num_buffer, size_t* num_lex, char* buffer, KLexemArr* LexArr, DF_ERRORS* error) {
    if(strncmp(&buffer[*num_buffer],
               DF_PLUS.name,
               DF_PLUS.len) == 0) {
        FUNC_ERROR_RTRN(error, DFERR_SECOND_PLUS, false)
    }

    size_t old_buffer = *num_buffer;

    if (strncmp(&buffer[*num_buffer],
                DF_PLUS.name,
                DF_PLUS.len) != 0) {
        if (!KLexMinus(num_buffer, num_lex, buffer, LexArr, error))
            return false;
    }

    if (strncmp(&buffer[*num_buffer],
                DF_PLUS.name,
                DF_PLUS.len) == 0) {

        LexArr->data[*num_lex].val = (char*)calloc(DF_PLUS.len, sizeof(char));
        strncpy(LexArr->data[*num_lex].val, DF_PLUS.name, DF_PLUS.len);
        LexArr->data[*num_lex].indef = IDDF_PLUS;


        *num_buffer += DF_PLUS.len;
        *num_lex    += DF_PLUS.len;

        if(!KLexPlus(num_buffer, num_lex, buffer, LexArr, error))
            return false;

        return true;
    }

    Sintax_error(old_buffer, *num_buffer, DFERR_POINTER_DONT_MOVE_IN_PLUS)
    return true;
}

bool KLexMinus  (size_t* num_buffer, size_t* num_lex, char* buffer, KLexemArr* LexArr, DF_ERRORS* error) {

    if(strncmp(&buffer[*num_buffer],
               DF_PLUS.name,
               DF_PLUS.len) == 0) {
        FUNC_ERROR_RTRN(error, DFERR_SECOND_PLUS, false)
    }

    size_t old_buffer = *num_buffer;

    if (strncmp(&buffer[*num_buffer],
                DF_MINUS.name,
                DF_MINUS.len) != 0) {
        if(!KLexMult(num_buffer, num_lex, buffer, LexArr, error))
            return false;
    }

    if (strncmp(&buffer[*num_buffer],
                DF_MINUS.name,
                DF_MINUS.len) == 0) {

        LexArr->data[*num_lex].val = (char*)calloc(DF_MINUS.len, sizeof(char));
        strncpy(LexArr->data[*num_lex].val, DF_MINUS.name, DF_MINUS.len);
        LexArr->data[*num_lex].indef = IDDF_MINUS;


        *num_buffer += DF_MINUS.len;
        *num_lex    += DF_MINUS.len;

        if(!KLexPlus(num_buffer, num_lex, buffer, LexArr, error))
            return false;

        return true;
    }

    Sintax_error(old_buffer, *num_buffer, DFERR_POINTER_DONT_MOVE_IN_MINUS)
    return true;
}

bool KLexMult  (size_t* num_buffer, size_t* num_lex, char* buffer, KLexemArr* LexArr, DF_ERRORS* error) {

    size_t old_buffer = *num_buffer;

    if (strncmp(&buffer[*num_buffer],
                DF_MULT.name,
                DF_MULT.len) != 0) {
        if(!KLexDiv(num_buffer, num_lex, buffer, LexArr, error))
            return false;
    }

    if (strncmp(&buffer[*num_buffer],
                DF_MULT.name,
                DF_MULT.len) == 0) {

        LexArr->data[*num_lex].val = (char*)calloc(DF_MULT.len, sizeof(char));
        strncpy(LexArr->data[*num_lex].val, DF_MULT.name, DF_MULT.len);
        LexArr->data[*num_lex].indef = IDDF_MULT;


        *num_buffer += DF_MULT.len;
        *num_lex    += DF_MULT.len;

        if(!KLexMult(num_buffer, num_lex, buffer, LexArr, error))
            return false;
        return true;
    }

    Sintax_error(old_buffer, *num_buffer, DFERR_POINTER_DONT_MOVE_IN_MULT)
    return true;
}


