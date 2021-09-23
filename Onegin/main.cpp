//
// Created by arlik_null on 14.09.2021.
//

/*programing for sort string in the text "Oneging"
 * MakeFile: None
 */

#include "MyLibString.h"


int main() {

//    char *full_input_filename = find_dir_prog(envp);
//    full_input_filename = (char*)realloc(full_input_filename, strlen(full_input_filename) + strlen(_name_output_file_));
//    strcat(full_input_filename, _name_input_file_);

    const char* _name_input_file_  = "/home/arlik_null/Документы/GitHub/DEAD_PROJECTS/Onegin/Files/Onegin.txt";       // old file
    const char* _name_output_file_ = "/home/arlik_null/Документы/GitHub/DEAD_PROJECTS/Onegin/Files/output_file.txt";  // sorted file
    const char* _name_clean_file_  = "/home/arlik_null/Документы/GitHub/DEAD_PROJECTS/Onegin/Files/Clear_Onegin.txt"; // clean file

    long         working_hours_of_the_program = clock();
    int          user_input_for_mode_setings;
    FILE*        file                         = open_file(_name_clean_file_);
    struct myarr arr                          = file_reading(file, _name_clean_file_);

    printf("Cleaning and record file: 0\n"
           "Input Your's sort:\n"
           "1 - bubble sort\n"
           "2 - reverse bubble sort (rhyme  sort)\n"
           "3 - my quick sort\n"
           "4 - my quick reverse sort\n"
           "5 - c quick sort\n"
           "6 - c quick sort reverse\n"
           "10(1, 2, 3, 4) - checking the validity of sort\n"
           "(example 101 checking the validity of BUBBLE sort)\n");
    scanf("%d", &user_input_for_mode_setings);

    switch (user_input_for_mode_setings) {
        case 0:
            printf("\nYou change cleaning file\n"
                  "name_clean_file: %s\n\n", _name_clean_file_);
            cleaning_file_and_record(_name_input_file_, _name_clean_file_);
            return 0;

        case 1:
            printf("\nYou change bubble sort\n"
                   "sort file: %s\n\n", _name_output_file_);
            bubble_sort(&arr);
            break;

        case 2:
            printf("\nYou change reverse bubble sort\n"
                   "sort file: %s\n\n", _name_output_file_);
            bubble_sort_revers(&arr);
            break;

        case 3:
            printf("\nYou change my quick sort\n"
                   "sort file: %s\n\n", _name_output_file_);
            quick_sort(&arr);
            break;

        case 4:
            printf("\nYou change my reverse quick sort\n"
                   "sort file: %s\n\n", _name_output_file_);
            quick_sort_reverse(&arr);
            break;

        case 5:
            printf("\nYou change quick sort\n"
                   "sort file: %s\n\n", _name_output_file_);
            qsort(arr.arr, arr.size, sizeof(struct mystr), comp_qsort);
            break;

        case 6:
            printf("\nYou change quick sort reserve\n"
                   "sort file: %s\n\n", _name_output_file_);
            qsort(arr.arr, arr.size, sizeof (struct mystr), comp_qsort_reverse);
            break;

        case 101:
            printf("\nThis unit test bubble sort\n"
                   "program input number this is count missed strings\n\n");
            unit_test_bubble_sort(arr);
            break;

        case 102:
            printf("\nThis unit test reverse bubble sort\n"
                   "program input number this is count missed strings\n\n");
            unit_test_reverse_bubble_sort(arr);
            break;

        case 103:
            printf("\nThis unit test my quick sort\n"
            "program input number this is count missed strings\n\n");
            unit_test_my_quick_sort(arr);
            break;

        case 104:
            printf("\nThis unit test my reverse quick sort\n"
                   "program input number this is count missed strings\n\n");
            unit_test_reverse_my_quick_sort(arr);
            break;

        default:
            printf("\nSorry you don't understand my program\n"
                   "please restart\n\n");
            return 0;
    }

    print_array_on_file(&arr, _name_output_file_);
//    write_sort_arr_in_file(&arr);

    printf("END OF PROGRAM\n"
           "Working Time of the Program: %f sec\n"
           "Number Tacks: %ld\n\n",
           (float)working_hours_of_the_program / CLOCKS_PER_SEC,
           working_hours_of_the_program);

    free(arr.arr);
    fclose(file);

    return 0;
}


