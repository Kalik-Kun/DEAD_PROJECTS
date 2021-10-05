#include "LibStack.h"


int main() {

    Skek my_skek = {};
    int error = UNDEFINED;
    int capacity = 10;
    int a = 2;
    SkekCtor(&my_skek, sizeof(int), capacity, &error);
    for (int i = 0; i < 10; i ++) {
        SkekPush(&my_skek, &a, &error);
//        void* my = SkekGet(&my_skek);
//        printf("%c\n", *((char *)my));
        SkekDump(&my_skek);
    }

    SkekDtor(&my_skek, &error);
    return 0;
}
