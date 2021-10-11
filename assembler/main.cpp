#include "Assembler.h"

int main() {
    struct Skek my_skek = {};
    SkekCtor(&my_skek);
//    int pp = 0;
//    int* code[100]; // our code
//    struct Skek my_skek = {};
//    while () {
//        switch(code[pp]) {
//            case 1: /*CMD_PUSH*/
//                SkekPush(&my_skek, code[pp+1]);
//                pp+=2; // CMD_PUSH lenght
//                break;
//
//            case 2: // CMD_ADD
//                SkekPush(&my_skek, SkekPop(&my_skek) + SkekPop(&my_skek));
//                pp+=1;
//                break;
//
//        }
//    }
    return 0;
}
