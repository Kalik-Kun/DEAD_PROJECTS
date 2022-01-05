//
// Created by KALIK on 22.11.2021.
//
/**
 * Lexer - parser string and lays out these string on lexems
 *
 *
**/

#ifndef DIF_KLEXER_H
#define DIF_KLEXER_H

#include <cstdio>
#include "KDump.h"
#include <MyLibString.h>

// todo ask dania for defines

#include "Oper_Name.h"

struct KLexem {
    char* val = nullptr;
    int indef = IDDF_UND;
};

struct KLexemArr {
    KLexem* data     = nullptr;
    size_t count     = 0;
};

KLexemArr KLexer(const char* file_name, DF_ERRORS* error = &DF_ERR);

bool KLexLine   (size_t* num_buffer, size_t* num_Lex, char* buffer, KLexemArr* LexArr, DF_ERRORS* error = &DF_ERR);
bool KLexSpace  (size_t* num_buffer, size_t* num_Lex, char* buffer, KLexemArr* LexArr, DF_ERRORS* error = &DF_ERR);
bool KLexMult   (size_t* num_buffer, size_t* num_Lex, char* buffer, KLexemArr* LexArr, DF_ERRORS* error = &DF_ERR);
bool KLexDiv   (size_t* num_buffer, size_t* num_Lex, char* buffer, KLexemArr* LexArr, DF_ERRORS* error = &DF_ERR);
bool KLexPlus   (size_t* num_buffer, size_t* num_Lex, char* buffer, KLexemArr* LexArr, DF_ERRORS* error = &DF_ERR);
bool KLexMinus   (size_t* num_buffer, size_t* num_Lex, char* buffer, KLexemArr* LexArr, DF_ERRORS* error = &DF_ERR);

#endif //DIF_KLEXER_H
