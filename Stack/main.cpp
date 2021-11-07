#include "LibStack.h"


int main() {

    int b = 200000;
    Skek my_skek = {};
    int buff  = 1;
    int error = UNDEFINED_SKEK;
    int capacity = 10;

    SkekCtor(&my_skek, sizeof(int), capacity, &error);

    for (int i = 0; i < 10; i ++) {
        SkekPush(&my_skek, &b, &error);
//        void* my = SkekGet(&my_skek);
//        printf("%c\n", *((char *)my));
//        SkekDump(&my_skek);
    }

    SkekDump(&my_skek);

    for (int i = 0; i < 100; i ++) {
        SkekDump(&my_skek);
        SkekPush(&my_skek, &b, &error);
        SkekDump(&my_skek);
        SkekPop(&my_skek, &buff,&error);
        SkekGet(&my_skek, &buff, &error);
        SkekPush(&my_skek, &b, &error);
//        void* my = SkekGet(&my_skek);
//        printf("%c\n", *((char *)my));
//        SkekDump(&my_skek);
    }


//    for (int i = 0; i < 1000; i ++) {
//        a[i] = 0;
//        if (!SkekVerif(&my_skek)) break;
//    }


    SkekDtor(&my_skek, &error);
    return 0;
}
