//
// Created by arlik_null on 22.11.2021.
//

#ifndef DIF_KTREE_H
#define DIF_KTREE_H

#include "KLexer.h"

enum KNodeType {
    KN_UND_TYPE,
    KN_SPEC_TYPE,
    KN_SEP_TYPE,
    KN_OPER_TYPE,
    KN_BRACKET_TYPE,
    KN_NUMBER_TYPE,
    KN_VAR_TYPE,
};

struct KNode {

    const char* name    = nullptr;
    KNodeType   TypeKN  = KN_UND_TYPE;
    DF_ID_OPER  TypeV   = IDDF_UND;

};

struct KTree {
    KNode* LeftKNode    = nullptr;
    KNode* RightKNode   = nullptr;
    KNode* ParentKNode  = nullptr;

};


#endif //DIF_KTREE_H
