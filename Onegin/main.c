/*programing for sort string in the text "Oneging"
 * MakeFile: None
 * Тест пузырька и Обратного пузырька пройден без ошибок
 * */

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>

const char *name_file = "Onegin.txt";
const char *output_name = "output_file";

struct mystr {
    char *str;
    long len;
};  // одна строка
struct myarr {
    struct mystr* arr;
    long size;
}; // массив указателей на строки

FILE* open_file(); // открывает файл
struct myarr make_array(FILE*); // распределяет текст в двумерный массив чаров
char checking_for_a_word(char); // смотрит чтобы в массив поподали только слова
void print_array(struct myarr); // печатает итоговый массив
void print_array_on_file(struct myarr); // печатает отсорченый массив в файл
struct mystr* size_up_array(struct mystr*, const long); // изменяет длину массива указателей на строки на size
char* size_up_len_string(char*, const long); // изменяет длину строки на size
struct myarr bubble_sort(struct myarr); // возвращает отсортированый пузырком массив
struct myarr bubble_sort_revers(struct myarr);// сортирует с конца ищет рифмы
char comp(struct mystr, struct mystr);// компонатор для пузырьковой сортировки
void _swap(struct mystr*, struct mystr*);//свап который не работает
char comp_reverse(struct mystr, struct mystr); //компоратор для обратного пузырька
int comp_qsort(const void*, const void*); // компоратор для квик сорта
int comp_qsort_reverse(const void*, const void*); // компоратор для обратного квик сорта
void unit_test_bubble_sort(struct myarr); //тест пузырька
void unit_test_reverse_bubble_sort(struct myarr); // тест обратного пузырька


int main() {
    FILE *file = open_file();
    struct myarr arr = make_array(file);
    int user_input_for_mode_setings;
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



FILE* open_file() {

    FILE *fp = fopen(name_file, "r");
    return fp;

}

struct myarr make_array(FILE *file) {

    char error_point = 0;

    char *arr = NULL;
    struct mystr *values = NULL;

    long string_count = 0;
    long len = 0;

    char symb;


    while (fscanf(file, "%c", &symb) != -1) {

        if (symb == '\n' && arr != NULL) {
            //printf("count++\n");

            string_count++;
            values = size_up_array(values, string_count);

            if (values == NULL) {
                error_point = 1;
                break;
            }

            values[string_count - 1].str = arr;
            values[string_count - 1].len = len;
            arr = NULL;
            len = 0;

            continue;
        }
        if(checking_for_a_word(symb)) {
            len++;
            arr = size_up_len_string(arr, len);
            if (arr == NULL) {
                error_point = 1;
                break;
            }
            arr[len - 1] = symb;
        }
    }

    if (error_point == 1) {
        return (struct myarr) {NULL, 0};
    }


    return (struct myarr) {values, string_count};
}
char checking_for_a_word(char symb) {
    if ((symb >= 'A' && symb <= 'Z') || (symb >= 'a' && symb <= 'z') || symb == ' ') {
        return 1;
    }
    return 0;
}
void print_array(struct myarr arr) {

    printf("size array: %ld\n", arr.size);

    for (long i = 0; i < arr.size; i ++) {
        for(long k = 0; k < arr.arr[i].len; k++) {

            printf("%c", arr.arr[i].str[k]);

        }
        printf("\n");
    }
}

void print_array_on_file(struct myarr arr) {

    FILE *fp = fopen(output_name, "w");
    fprintf(fp, "size array: %ld\n", arr.size);

    for (long i = 9; i < arr.size; i++) {
        for (long k = 0; k < arr.arr[i].len; k++) {

            fprintf(fp, "%c", arr.arr[i].str[k]);

        }

        fprintf(fp, "\n");
    }
    fclose(fp);
}

struct mystr* size_up_array(struct mystr* values, const long size) {

    values = (struct mystr*)realloc(
            values, size * sizeof(struct mystr));
    return values;
}

char* size_up_len_string(char* values, const long size) {

    values = (char*)realloc(values, size * sizeof(char));
    return values;
}

struct myarr bubble_sort(struct myarr arr) {
    for (int i = 1; i <= arr.size; i ++) {
        for (int k = 0; k < arr.size - i; k ++) {

            if (comp(arr.arr[k], arr.arr[k + 1])) {
            //if (strcmp(arr.arr[k].str, arr.arr[k + 1].str) > 0){
                //_swap(&arr.arr[k], &arr.arr[k + 1]); // я не знаю почему это не работает
                struct mystr str3;
                str3 = arr.arr[k];
                arr.arr[k] = arr.arr[k + 1];
                arr.arr[k + 1] = str3;
            }

        }
    }
    return arr;
}
struct myarr bubble_sort_revers(struct myarr arr) {

    for (int i = 1; i <= arr.size; i ++) {
        for (int j = 0; j < arr.size - i; j ++ ) {
            if (comp_reverse(arr.arr[j], arr.arr[j + 1])) {
                struct mystr string_for_comparate_strings = arr.arr[j];
                arr.arr[j] = arr.arr[j + 1];
                arr.arr[j + 1] = string_for_comparate_strings;
            }
        }
    }
    return arr;
}

char comp(struct mystr str1, struct mystr str2) {

    char swap_pointer = 0;

    if (str1.len > str2.len) {

        for (long i = 0; i < str2.len; i ++) {

            if (str1.str[i] > str2.str[i]) {
                swap_pointer = 1;
                break;
            }
            if (str1.str[i] < str2.str[i]) {
                swap_pointer = 0;
                break;
            }

        }

        if (swap_pointer == 1)
            return 1;
        return 0;
    }

    if (str1.len < str2.len) {
        for (long i = 0; i < str1.len; i ++) {

            if (str1.str[i] > str2.str[i]) {
                swap_pointer = 1;
                break;
            }
            if (str1.str[i] < str2.str[i]) {
                swap_pointer = 0;
                break;
            }

        }
        if (swap_pointer == 1)
            return 1;
        return 0;
    }

    for (long i = 0; i < str1.len; i ++) {

        if (str1.str[i] > str2.str[i]) {
            swap_pointer = 1;
            break;
        }
        if (str1.str[i] < str2.str[i]) {
            swap_pointer = 0;
            break;
        }

    }
    if (swap_pointer == 1) {
        return 1;
    }
    return 0;
}
char comp_reverse(struct mystr str1, struct mystr str2) {

    char swap_pointer = 0;

    if (str1.len > str2.len) {
        for (long i = 1; i <= str2.len; i ++) {

            if (str1.str[str1.len - i] > str2.str[str2.len - i]) {
                swap_pointer = 1;
                break;
            }
            if (str1.str[str1.len - i] < str2.str[str2.len - i]) {
                swap_pointer = 0;
                break;
            }

        }

        if (swap_pointer == 1)
            return 1;
        return 0;
    }

    if (str1.len < str2.len) {
        for (long i = 1; i <= str1.len; i ++) {

            if (str1.str[str1.len - i] > str2.str[str2.len - i]) {
                swap_pointer = 1;
                break;
            }
            if (str1.str[str1.len - i] < str2.str[str2.len - i]) {
                swap_pointer = 0;
                break;
            }

        }
        if (swap_pointer == 1)
            return 1;
        return 0;
    }

    for (long i = 1; i <= str1.len; i ++) {

        if (str1.str[str1.len - i] > str2.str[str2.len - i]) {
            swap_pointer = 1;
            break;
        }
        if (str1.str[str1.len - i] < str2.str[str2.len - i]) {
            swap_pointer = 0;
            break;
        }

    }
    if (swap_pointer == 1) {
        return 1;
    }
    return 0;
}
int comp_qsort(const void* vd1, const void* vd2) {
    struct mystr* str1 = (struct mystr*)vd1;
    struct mystr* str2 = (struct mystr*)vd2;
    return strcmp(str1->str, str2->str);
}
int comp_qsort_reverse(const void* vd1, const void* vd2) {
    struct mystr* str1 = (struct mystr*)vd1;
    struct mystr* str2 = (struct mystr*)vd2;

    //хз можно ли копировать тут в указатель и потом его изменять боюсь поменять изнаальный массив

    struct mystr new_str1 = *str1;
    struct mystr new_str2 = *str2;

    for (int i = 0; i < (int)str1->len/2; i ++) {
        new_str1.str[i] = str1->str[str1->len - i - 1];
        new_str1.str[str1->len - i - 1] = str1->str[i];
    }
    for (int i = 0; i < (int)str2->len/2; i ++) {
        new_str2.str[i] = str2->str[str2->len - i - 1];
        new_str2.str[str2->len - i - 1] = str2->str[i];
    }

    return strcmp(new_str1.str, new_str2.str);
}
void _swap(struct mystr* str1, struct mystr* str2) {

    //printf("%p  %p\n", str1, str2);

    struct mystr* str3;
    str3 = str1;
    str1 = str2;
    str2 = str3;

    //printf("%p  %p\n", str1, str2);
    //getchar();
}

void unit_test_bubble_sort(struct myarr arr) {

    int time_before_bubble_sort;
    int time_bubble_sort;
    int time_quick_sort;
    int time_after_bubble_sort;
    int time_before_quick_sort;
    int time_after_quick_sort;

    int wrong_num = 0;

    struct myarr arr_bubble;
    struct myarr arr_qsort;

    time_before_bubble_sort = time(0);

    arr_bubble= bubble_sort(arr);

    time_after_bubble_sort = time(0);
    time_bubble_sort = time_after_bubble_sort - time_before_bubble_sort;


    time_before_quick_sort = time(0);

    arr_qsort = arr;
    qsort(arr_qsort.arr, arr_qsort.size, sizeof (struct mystr), comp_qsort);

    time_after_quick_sort = time(0);
    time_quick_sort = time_after_quick_sort - time_before_quick_sort;

    for (int i = 0; i < arr.size; i ++) {
        if(strcmp(arr_qsort.arr[i].str, arr_bubble.arr[i].str)) wrong_num++;
    }
    printf("Time bubble sort: %d\n"
           "Time quick sort: %d\n", time_bubble_sort, time_quick_sort);

    printf("Num wrongs: %d\n\n", wrong_num);
}
void unit_test_reverse_bubble_sort(struct myarr arr) {


    int time_before_revers_bubble_sort;
    int time_revers_bubble_sort;
    int time_revers_quick_sort;
    int time_after_revers_bubble_sort;
    int time_before_revers_quick_sort;
    int time_after_revers_quick_sort;

    int wrong_num = 0;

    struct myarr arr_bubble;
    struct myarr arr_qsort;

    time_before_revers_bubble_sort = time(0);
    arr_bubble= bubble_sort_revers(arr);

    time_after_revers_bubble_sort = time(0);
    time_revers_bubble_sort = time_after_revers_bubble_sort - time_before_revers_bubble_sort;
    time_before_revers_quick_sort = time(0);

    arr_qsort = arr;
    qsort(arr_qsort.arr, arr_qsort.size, sizeof (struct mystr), comp_qsort_reverse);

    time_after_revers_quick_sort = time(0);
    time_revers_quick_sort = time_after_revers_quick_sort - time_before_revers_quick_sort;

    for (int i = 0; i < arr.size; i ++) {
        if(strcmp(arr_qsort.arr[i].str, arr_bubble.arr[i].str)) wrong_num++;
    }
    printf("Time bubble sort: %d\n"
           "Time quick sort: %d\n", time_revers_bubble_sort, time_revers_quick_sort);

    printf("Num wrongs: %d\n\n", wrong_num);
}
