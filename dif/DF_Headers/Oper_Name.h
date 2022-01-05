//
// Created by arlik_null on 03.12.2021.
//

#ifndef DIF_OPER_NAME_H
#define DIF_OPER_NAME_H


enum DF_ID_OPER {
    IDDF_UND,
    IDDF_START,
    IDDF_END,
    IDDF_LINE,
    IDDF_SPACE,
    IDDF_PLUS,
    IDDF_MINUS,
    IDDF_DIV,
    IDDF_MULT,
    IDDF_LEFT_CIRCLE_BRACKET,
    IDDF_RIGHT_CIRCLE_BRACKET,
    IDDF_LEFT_SQRT_BRACKET,
    IDDF_RIGHT_SQRT_BRACKET,

};

struct DF_OPER {
    const char* name = nullptr;
    size_t      len  = 0;
};

/// Specififc characters
const DF_OPER     DF_UND    = {};
const DF_OPER     DF_START  = {};
const DF_OPER     DF_END    = {};

/// Separator characters
const DF_OPER     DF_LINE   = {"\n", 1};                 //
const DF_OPER     DF_SPACE  = {" ", 1};                 // operation shares else operation

/// Operators characters
const DF_OPER     DF_PLUS   = {"+", 1};                 // add (mean + in normal)
const DF_OPER     DF_MINUS  = {"-", 1};                 // minus (mean - in normal)
const DF_OPER     DF_DIV    = {"/", 1};                 // div (mean / in normal)
const DF_OPER     DF_MULT   = {"*", 1};                 // mult (mean * in normal)

/// Brackets
const DF_OPER     DF_LEFT_CIRCLE_BRACKET  = {"(", 1};    // parenthesis (mean ( in normal)
const DF_OPER     DF_RIGHT_CIRCLE_BRACKET = {")", 1};
const DF_OPER     DF_LEFT_SQRT_BRACKET    = {"[", 1};    //
const DF_OPER     DF_RIGHT_SQRT_BRACKET   = {"]", 1};

#endif //DIF_OPER_NAME_H
