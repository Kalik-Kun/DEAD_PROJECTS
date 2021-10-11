#include "LibStack.h"


int main() {

    int* a = (int *)calloc(1, sizeof(int));
    int b = 10;
    Skek my_skek = {};
    int error = UNDEFINED;
    int capacity = 10;
    SkekCtor(&my_skek, sizeof(int), capacity, &error);
    for (int i = 0; i < 20; i ++) {
        SkekPush(&my_skek, &b, &error);
//        void* my = SkekGet(&my_skek);
//        printf("%c\n", *((char *)my));
//        SkekDump(&my_skek);
    }

    SkekDump(&my_skek);
    for (int i = 0; i < 1000; i ++) {
        a[i] = 0;
        if (!SkekVerif(&my_skek)) break;
    }


    SkekDtor(&my_skek, &error);
    return 0;
}
