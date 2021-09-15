//
// Created by arlik_null on 14.09.2021.
//


/*programing for sort string in the text "Oneging"
 * MakeFile: None
 * Тест пузырька и Обратного пузырька пройден без ошибок
 * */

#include "onegin_func.h"



int main(int argc, char* argv[], char* envp[]) {

    int user_input_for_mode_setings;
    FILE *file                        = open_file();
    struct myarr arr                  = make_array(file);
    long working_hours_of_the_program = clock();

    printf("Input Your's sort:\n1 - bubble sort"
           "\n2 - reverse bubble sort (rhyme  sort)\n3-quick sort"
           "\n4(1, 2) - checking the validity of sort"
           "(example 41 checking the validity of BUBBLE sort)\n");

    scanf("%d", &user_input_for_mode_setings);
    switch (user_input_for_mode_setings) {
        case 1:
            printf("\n\nYou change bubble sort\n"
                   " sort file: output_file.txt\n");
            arr = bubble_sort(arr);
            break;

        case 2:
            printf("\n\nYou change reverse bubble sort\n"
                   " sort file: output_file.txt\n");
            arr = bubble_sort_revers(arr);
            break;
        case 3:
            printf("\n\nYou change qick sort\n"
                   " sort file: output_file.txt\n");
            qsort(arr.arr, arr.size, sizeof(struct mystr), comp_qsort);
            break;
        case 41:
            printf("\n\nThis unit test bubble sort\n"
                   "program input number this is count missed strings\n\n");
            unit_test_bubble_sort(arr);
            break;
        case 42:
            printf("\n\nThis unit test reverse bubble sort\n"
                   "program input number this is count missed strings\n\n");
            unit_test_reverse_bubble_sort(arr);
            break;
        default:
            printf("\nSorry i don't andesrtand my progrram\n"
                   "plese restard\n\n");
            break;
    }

    //print_array(arr);
    print_array_on_file(arr);

    printf("END OF PROGRAM\n\n\nWorking Time of the Program:"
           " %f sec\nNumber Tacks: %ld\n",
           (float)working_hours_of_the_program / CLOCKS_PER_SEC,
           working_hours_of_the_program);

    fclose(file);
    return 0;
}

