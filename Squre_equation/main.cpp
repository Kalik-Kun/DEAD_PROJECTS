#include "func.h"



int main() {
    int mod = 0;

    printf("PLease input mode:\n"
                "1 - Count answer of square equation\n"
                "2 - unit test for developer\n");

    scanf("%d", &mod);

    switch(mod) {
        case 1:
            research_ans(USER_MODE);
            break;
        case 2:
            if (unit_test()) {
                printf("UNIT TESTS COMPLETED SUCCESS\n");
            }
            else {
                printf("UNIT TESTS FAILED\n");
            }
            return 0;
        default:
            std::printf("Please input number that i write\n"
                        "Goodbye\n\n");
            break;
    }

    return 0;
}

