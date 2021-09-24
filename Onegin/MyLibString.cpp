//
// Created by arlik_null on 14.09.2021.
//

#include "MyLibString.h"

            /// WORK WITH FILE ///
//char* find_dir_prog(char* envp[]) {
//    for (int i = 0; envp[i] != NULL; i++) {
//        if (strncmp("PWD", envp[i], 3) == 0) {
//            char *a = (char *)calloc(strlen(&envp[i][4]) - strlen("cmake-build-debug"), sizeof (char));
//            strncpy(a, &envp[i][4], strlen(&envp[i][4]) - strlen("cmake-build-debug"));
//            return a;
//        }
//    }
//    return nullptr;
//}

FILE* open_file(const char *full_filename) {

    FILE  *fp = fopen(full_filename, "r");

    // use assert for find BAGS. when I will do program i disconnect they
    if (fp == nullptr) {
        printf("ERROR: file can't input\n"
                      "Please reload program\n");
    }

    return fp;
}


        /// WORK WITH ARRAY FUNCTION ///
struct myarr file_reading(FILE* fp, const char* name_file) {
    long number_line = 0;
    struct mystr *arr_string = nullptr;
    char *buff = nullptr;
    size_t size_file = out_file_size(name_file);

    buff = (char*) calloc(size_file + 1, sizeof(char));
    fread(buff, sizeof(char), size_file, fp);

    size_t count_line = find_count_elems(buff, '\n');

    // todo virtalspace
    arr_string = (struct mystr *) calloc(count_line + 1, sizeof(struct mystr));

    arr_string[0].str = buff;
    arr_string[0].len = strchr(buff, '\n') - buff;
    number_line = 1;

    for (char* str_line_pointer = strchr(buff, '\n');
         str_line_pointer != nullptr && number_line < count_line + 1;
         str_line_pointer = strchr(str_line_pointer + 1, '\n')) {

        *str_line_pointer = '\0';
        arr_string[number_line].str = str_line_pointer + 1;

        if (strchr(str_line_pointer + 1, '\n'))
            arr_string[number_line].len =
                    strchr(str_line_pointer + 1, '\n') - str_line_pointer - 1;
        else
            arr_string[number_line].len = strlen(arr_string[number_line].str);

        number_line++;
    }
    return {arr_string, count_line};
}

void free_memory_for_string_array (struct myarr* arr_string) {
    assert(arr_string->arr);
//    if (!arr_string->arr) return;

    for (size_t i = 0; i < arr_string->arr->len; i++) {
        if (arr_string->arr[i].str) free(arr_string->arr[i].str);
    }
    // i don't know how cleaning memory because i use buffer and pointer on buffer in arr_string in first string
    assert(arr_string->arr);
    free(arr_string->arr);
}

void write_sort_arr_in_file (struct myarr* arr_string, const char* file_name) {
    FILE* output_file = fopen(file_name, "w");
//    fprintf(output_file, "size array: %ld\n", arr_string->size);

    for (long i = 0; i < arr_string->size; i++) {
        fwrite(arr_string->arr[i].str, sizeof(char), arr_string->arr->len, output_file);
    }

    fclose(output_file);
}


            /// SORT FUNCTIONS ///
void  bubble_sort(struct myarr* arr) {
    for (size_t i = 1; i <= arr->size; i ++) {
        for (size_t k = 0; k < arr->size - i; k ++) {
//            printf("%d %s %s\n", k, arr->arr[k].str, arr->arr[k + 1].str);
            if (comp(&arr->arr[k], &arr->arr[k + 1]) == 1) {
                swap_mystr(&arr->arr[k], &arr->arr[k + 1]);
            }
        }
    }
}

void bubble_sort_revers(struct myarr* arr) {

    for (int i = 1; i <= arr->size; i ++) {
        for (int k = 0; k < arr->size - i; k ++ ) {
            if (comp_reverse(&arr->arr[k], &arr->arr[k + 1]) == 1) {
                swap_mystr(&arr->arr[k], &arr->arr[k + 1]);
            }
        }
    }
}

void quick_sort(struct myarr* arr_string) {
    quick_sort_arr_string(arr_string->arr, 0, arr_string->size - 1);
}

void quick_sort_arr_string (struct mystr* arr_string, size_t left, size_t right) {
    if (left >= right) return;
    if (left + 1 == right) {
        if (comp(&arr_string[left], &arr_string[right]) == 1)
            swap_mystr(&arr_string[left], &arr_string[right]);
        return;
    }
    size_t l = left, r = right;
    struct mystr support_elem = {};

    copy_string(&support_elem, &arr_string[(size_t) (left + right) / 2]);

    while (l <= r) {
//        printf("%s, %s\n", arr_string[l].str, arr_string[r].str);
        while (comp(&support_elem, &arr_string[l]) == 1 && (l <= r)) l++;
        while (comp(&arr_string[r], &support_elem) == 1 && (l <= r)) r--;

        if (l <= r) {
            swap_mystr(&arr_string[l], &arr_string[r]);
            l++;
            r--;
        }
    }

//    if (support_elem.str[0] == '*') {
//        printf("left: %d, l: %d, right: %d, r: %d\n", left, l, right, r);
//        printf("SUPPORT ELEMENT: %s\n", support_elem.str);
//        printf("LEFT SIDE:\n");
//        print_arr_left_to_right(arr_string, left, r);
//        printf("\nRIGHT SIDE:\n");
//        print_arr_left_to_right(arr_string, l, right);
//        printf("END\n\n");
//    }

//    printf("left: %d, l: %d, right: %d, r: %d\n", left, l, right, r);
//    printf("SUPPORT ELEMENT: %s\n", support_elem.str);
//    print_arr_left_to_right(arr_string, 0, 10);
//    printf("END\n\n");

    free(support_elem.str);

    quick_sort_arr_string(arr_string, left, r);
    quick_sort_arr_string(arr_string, l, right);
}

void quick_sort_reverse (struct myarr* arr_string) {
    quick_sort_reverse_arr_string(arr_string->arr, 0, arr_string->size - 1);
}

void quick_sort_reverse_arr_string (struct mystr* arr_string, size_t left, size_t right) {
    if (left >= right) return;
    if (left + 1 == right) {
        if (comp_reverse(&arr_string[left], &arr_string[right]) == 1)
            swap_mystr(&arr_string[left], &arr_string[right]);
        return;
    }

    size_t l = left, r = right;
    struct mystr support_elem = {};
    copy_string(&support_elem, &arr_string[(size_t) (left + right) / 2]);

    while (l <= r) {
//        printf("%s, %s\n", arr_string[l].str, arr_string[r].str);
        while (comp_reverse(&support_elem, &arr_string[l]) == 1 && (l <= r)) l++;
        while (comp_reverse(&arr_string[r], &support_elem) == 1 && (l <= r)) r--;
        if (l <= r) {
            swap_mystr(&arr_string[l], &arr_string[r]);
            l++;
            r--;
        }
    }

    free(support_elem.str);

    quick_sort_reverse_arr_string(arr_string, left, r);
    quick_sort_reverse_arr_string(arr_string, l, right);
}

// todo uneverse comp
            /// COMPARATORS FOR SORT FUNCTIONS ///
char comp(struct mystr* str1, struct mystr* str2) {

    // if string havn't letters then  this string go back
    size_t count_letters1 = 0;
    size_t count_letters2 = 0;
    for (size_t i = 0, j = 0; (i < str1->len) && (j < str2->len);) {
        if (is_it_letter(str1->str[i]) && is_it_letter(str2->str[j])) {
            if (str1->str[i] > str2->str[j]) {
                return 1;
            }

            if (str1->str[i] < str2->str[j]) {
                return -1;
            }
            i++; j++; count_letters1++; count_letters2++;
        }

        while ((i < str1->len))
            if (!is_it_letter(str1->str[i])) i++;
            else {
                count_letters1++;
                break;
            }

        while ((j < str2->len))
            if (!is_it_letter(str2->str[j])) j++;
            else {
                count_letters2++;
                break;
            }
    }

    if (count_letters1 == 0 && count_letters2 == 0) {
        if (str1->len > str2->len) return 1;
        if (str1->len < str2->len) return -1;
        return 0;
    }
    if (count_letters2 == 0)    return 1;
    if (count_letters1 == 0)    return -1;
    if (str1->len > str2->len)  return 1;
    if (str1->len < str2->len)  return -1;
    return 0;
}

char comp_reverse(struct mystr* str1, struct mystr* str2) {
    // don't start i with str->len it's bad idea size_t have't 0 and when j or i come in 0 then j = 324234234234234 (many)

    // if string havn't letters then  this string go back
    size_t count_letters1 = 0;
    size_t count_letters2 = 0;
//    printf("%s %s\n", str1->str, str2->str);
    for (size_t i = 1, j = 1; (i <= str1->len) && (j <= str2->len);) {

//        printf("%d %c  %d %c\n", i, str1->str[i], j, str2->str[j]);
        if (is_it_letter(str1->str[str1->len - i]) &&
            is_it_letter(str2->str[str2->len - j])) {

            if (str1->str[str1->len - i] > str2->str[str2->len - j]) {
                return 1;
            }

            if (str1->str[str1->len - i] < str2->str[str2->len - j]) {
                return -1;
            }
            i++; j++; count_letters1++; count_letters2++;
        }

        while ((i <= str1->len))
            if (!is_it_letter(str1->str[str1->len - i])) i++;
            else {
                count_letters1++;
                break;
            }

        while ((j <= str2->len))
            if (!is_it_letter(str2->str[str2->len - j])) j++;
            else {
                count_letters2++;
                break;
            }
    }

    if (count_letters1 == 0 && count_letters2 == 0) {
        if (str1->len > str2->len) return 1;
        if (str1->len < str2->len) return -1;
        return 0;
    }
    if (count_letters2 == 0)    return 1;
    if (count_letters1 == 0)    return -1;
    if (str1->len > str2->len)  return 1;
    if (str1->len < str2->len)  return -1;
    return 0;
}

int comp_qsort(const void* vd1, const void* vd2) {
    struct mystr* str1 = (struct mystr*)vd1;
    struct mystr* str2 = (struct mystr*)vd2;
    return comp(str1, str2);
}

int comp_qsort_reverse(const void* vd1, const void* vd2) {
    struct mystr* str1 = (struct mystr*)vd1;
    struct mystr* str2 = (struct mystr*)vd2;

    return comp_reverse(str1, str2);
}


            /// UNIT TESTS ///
void unit_test_bubble_sort(struct myarr arr) {
    int time_before_bubble_sort     = 0;
    int time_bubble_sort            = 0;
    int time_quick_sort             = 0;
    int time_after_bubble_sort      = 0;
    int time_before_quick_sort      = 0;
    int time_after_quick_sort       = 0;

    int wrong_num = 0;

    struct myarr arr_bubble = arr;
    struct myarr arr_qsort  = {};

    copy_arr_string(&arr_qsort, &arr);

    time_before_bubble_sort = time(0);
    bubble_sort(&arr_bubble);
    time_after_bubble_sort = time(0);
    time_bubble_sort = time_after_bubble_sort - time_before_bubble_sort;

    time_before_quick_sort = time(0);
    qsort(arr_qsort.arr, arr_qsort.size, sizeof (struct mystr), comp_qsort);
    time_after_quick_sort = time(0);
    time_quick_sort = time_after_quick_sort - time_before_quick_sort;

    for (int i = 0; i < arr.size; i ++) {
        if(comp(&arr_qsort.arr[i], &arr_bubble.arr[i])) {
            printf("numb error: %d\n"
                   "line: %d\n"
                   "qsort string: %s\n"
                   "bubble string: %s\n",
                   ++wrong_num, i, arr_qsort.arr[i].str, arr_bubble.arr[i].str);
        }
    }

    printf("Time bubble sort: %d\n"
           "Time quick sort: %d\n", time_bubble_sort, time_quick_sort);

    if (wrong_num == 0) printf("SUCCESSFUL COMPLETED\n");
    else                printf("Num wrongs: %d\n\n", wrong_num);

    free_memory_for_string_array(&arr_qsort); // because copy_string allocate memory
}

void unit_test_reverse_bubble_sort(struct myarr arr) {
    int time_before_revers_bubble_sort  = 0;
    int time_revers_bubble_sort         = 0;
    int time_revers_quick_sort          = 0;
    int time_after_revers_bubble_sort   = 0;
    int time_before_revers_quick_sort   = 0;
    int time_after_revers_quick_sort    = 0;

    int wrong_num = 0;

    struct myarr arr_bubble = arr;
    struct myarr arr_qsort  = {};

    copy_arr_string(&arr_qsort, &arr);

    time_before_revers_bubble_sort = time(0);
    bubble_sort_revers(&arr_bubble);
    time_after_revers_bubble_sort = time(0);
    time_revers_bubble_sort = time_after_revers_bubble_sort - time_before_revers_bubble_sort;

    time_before_revers_quick_sort = time(0);
    qsort(arr_qsort.arr, arr_qsort.size, sizeof (struct mystr), comp_qsort_reverse);
    time_after_revers_quick_sort = time(0);
    time_revers_quick_sort = time_after_revers_quick_sort - time_before_revers_quick_sort;

    for (int i = 0; i < arr.size; i ++) {
        if(comp(&arr_qsort.arr[i], &arr_bubble.arr[i])) {
            printf("numb error: %d\n"
                   "line: %d\n"
                   "qsort reverse string: %s\n"
                   "bubble reverse string: %s\n",
                   ++wrong_num, i, arr_qsort.arr[i].str, arr_bubble.arr[i].str);
        }
    }
    printf("Time reverse bubble sort: %d\n"
           "Time quick sort: %d\n", time_revers_bubble_sort, time_revers_quick_sort);

    if (wrong_num == 0) printf("SUCCESSFUL COMPLETED\n");
    else                printf("Num wrongs: %d\n\n", wrong_num);


    free_memory_for_string_array(&arr_qsort);
}

void unit_test_my_quick_sort (struct myarr arr) {
    int time_my_quick_sort         = 0;
    int time_before_my_quick_sort  = 0;
    int time_after_my_quick_sort   = 0;
    int time_quick_sort            = 0;
    int time_before_quick_sort     = 0;
    int time_after_quick_sort      = 0;

    int wrong_num = 0;

    struct myarr arr_my_qsort = arr;
    struct myarr arr_qsort    = {};

    copy_arr_string(&arr_qsort, &arr);

    time_before_my_quick_sort  = time(0);
    quick_sort(&arr_my_qsort);
    time_after_my_quick_sort = time(0);
    time_my_quick_sort = time_after_my_quick_sort - time_before_my_quick_sort;

    time_before_quick_sort  = time(0);
    qsort(arr_qsort.arr, arr_qsort.size, sizeof (struct mystr), comp_qsort);
    time_after_quick_sort = time(0);
    time_quick_sort = time_after_quick_sort - time_before_quick_sort;


    for (int i = 0; i < arr.size; i ++) {
        // todo when i use strcmp i have 222 errors i don't know why(ends of copy strings have random simbols) with my compare all ok
        if(comp(&arr_qsort.arr[i], &arr_my_qsort.arr[i])) {
            printf("numb error: %d\n"
                    "line: %d\n"
                    "qsort string: %s\n"
                    "my qsort string: %s\n",
                    ++wrong_num, i, arr_qsort.arr[i].str, arr_my_qsort.arr[i].str);
        }
    }

    printf("Time my qsort sort: %d\n"
           "Time quick sort: %d\n", time_my_quick_sort, time_quick_sort);

    if (wrong_num == 0) printf("SUCCESSFUL COMPLETED\n");
    else                printf("Num wrongs: %d\n\n", wrong_num);

    free_memory_for_string_array(&arr_qsort); //because copy_string allocate new memmory
}

void unit_test_reverse_my_quick_sort (struct myarr arr) {
    int time_revers_my_qsort_sort         = 0;
    int time_after_revers_my_qsort_sort   = 0;
    int time_before_revers_my_qsort_sort  = 0;
    int time_revers_quick_sort            = 0;
    int time_before_revers_quick_sort     = 0;
    int time_after_revers_quick_sort      = 0;

    int wrong_num = 0;

    struct myarr arr_my_qsort = arr;
    struct myarr arr_qsort    = {};

    copy_arr_string(&arr_qsort, &arr);

    time_before_revers_my_qsort_sort = time(0);
    quick_sort_reverse(&arr_my_qsort);
    time_after_revers_my_qsort_sort = time(0);
    time_revers_my_qsort_sort = time_after_revers_my_qsort_sort - time_before_revers_my_qsort_sort;

    time_before_revers_quick_sort = time(0);
    qsort(arr_qsort.arr, arr_qsort.size, sizeof (struct mystr), comp_qsort_reverse);
    time_after_revers_quick_sort = time(0);
    time_revers_quick_sort = time_after_revers_quick_sort - time_before_revers_quick_sort;

    for (int i = 0; i < arr.size; i ++) {
        if(comp(&arr_qsort.arr[i], &arr_my_qsort.arr[i])) {
            printf("numb error: %d\n"
                   "line: %d\n"
                   "qsort reverse string: %s\n"
                   "my qsort reverse string: %s\n",
                   ++wrong_num, i, arr_qsort.arr[i].str, arr_my_qsort.arr[i].str);
        }
    }
    printf("Time mu quick sort: %d\n"
           "Time quick sort: %d\n", time_revers_my_qsort_sort, time_revers_quick_sort);

    if (wrong_num == 0) printf("SUCCESSFUL COMPLETED\n");
    else                printf("Num wrongs: %d\n\n", wrong_num);


    free_memory_for_string_array(&arr_qsort);
}


            ///HELP FUNCTIONS///
void swap_mystr(struct mystr* str1, struct mystr* str2) {
    struct mystr str3 = *str1;
    *str1 = *str2;
    *str2 = str3;
}

void copy_string(struct mystr* str1, struct mystr* str2) {
    str1->str = (char *)calloc(str2->len, sizeof(char));
    str1->len = str2->len;

    for (size_t i = 0; i < str2->len; i ++) {
        str1->str[i] = str2->str[i];
    }
}

void copy_arr_string(struct myarr* arr1,  struct myarr* arr2) {
    arr1->arr = (struct mystr *)calloc(arr2->size, sizeof(struct mystr));
    arr1->size = arr2->size;

    for (size_t i = 0; i < arr2->size; i ++) {
        copy_string(&arr1->arr[i], &arr2->arr[i]);
    }
}

size_t out_file_size (const char* filename) {
    struct stat stat_file = {};
    stat(filename, &stat_file);
    return stat_file.st_size;
}

size_t find_count_elems (char* string, const char elem) {
    size_t count_lenght = 0;
    for (size_t i = 0; string[i] != '\0'; i++)
        if (string[i] == elem)
            count_lenght++;

    return count_lenght;
}

void print_array(struct myarr arr) {
    printf("size array: %ld\n", arr.size);

    for (long i = 0; i < arr.size; i ++) {
        printf("%s\n", arr.arr[i].str);
    }
}

void print_array_on_file(struct myarr *arr, const char* file_name) {

    FILE *fp = fopen(file_name, "w");
    fprintf(fp, "size array: %ld\n", arr->size);

    for (long i = 9; i < arr->size; i++) {
        for (long k = 0; k < arr->arr[i].len; k++) {
            fprintf(fp, "%c", arr->arr[i].str[k]);

        }
        fprintf(fp, "\n");
    }

    fclose(fp);
}

void reverse_mystr(struct mystr* str) {
    for (size_t i = 0; i < (size_t) str->len / 2; i ++) {
        my_swap(&str->str[i], &str->str[str->len - i - 1]);
    }
}

char is_it_letter (const char simb) {
    if (('a' <= simb && simb <= 'z') ||
        ('A' <= simb && simb <= 'Z') ||
        ('0' <= simb && simb <= '9')
//        (simb == ' ')
        ) {
        return true;
    }

    return false;
}

void print_arr_left_to_right (struct mystr* arr, size_t left, size_t right) {
    for (size_t i = left; i <= right; i ++) {
        printf("%s\n", arr[i].str);
    }
}

/* This func cleans input text from:
 * Repeating spaces
 * Repeating enters
 * Incomprehensible symbols
 * Tabs change of spaces
 * */

void cleaning_file_and_record(const char *_name_input_file_, const char *_name_output_file) {
    FILE* input_file = fopen(_name_input_file_, "r");
    FILE* output_file = fopen(_name_output_file, "w");
    struct stat stat_file = {};
    char* buff = nullptr;
    struct mystr new_buff = {};
    int real_size = 0;

    stat(_name_input_file_, &stat_file);
    buff = (char *)calloc (stat_file.st_size/sizeof(char), sizeof(char));
    fread(buff, sizeof(char), stat_file.st_size, input_file);

    new_buff = clean(buff, stat_file.st_size/sizeof(char));

    fwrite(new_buff.str, sizeof(char), new_buff.len, output_file);
//    fprintf(output_file, "%s", new_buff);

    free(buff);
    free(new_buff.str);
}

struct mystr clean(const char* buff, const long buff_size) {
    char* new_buff = (char*)calloc(buff_size, sizeof(char));
    char Repeating_spaces     = false;
    char Repeating_enters     = false;
    size_t number_elem_new_buff = 0;     // number elem in new buff

    for(size_t i = 0; buff[i] != '\0'; i++) {

        if (buff[i] == '\n' || buff[i] == '\r') {
            Repeating_spaces = true;
            if (Repeating_enters) continue;
            Repeating_enters = true;
            new_buff[number_elem_new_buff++] = '\n';
            continue;
        }
        else Repeating_enters = false;

        if (buff[i] == ' ' ||
            buff[i] == '\t' ||
            !(33 <= buff[i] && buff[i] <= 126)) {

            if (Repeating_spaces) continue;
            Repeating_spaces = true;
            new_buff[number_elem_new_buff++] = ' ';
            continue;
        }
        else Repeating_spaces = false;

        if (0 <= buff[i] && buff[i] <= 127) {
            new_buff[number_elem_new_buff++] = buff[i];
        }
        else {
            Repeating_spaces = true;
            new_buff[number_elem_new_buff++] = ' ';
        }
    }

//    new_buff[number_elem_new_buff++] = '\0';
    new_buff = (char* ) realloc(new_buff, (number_elem_new_buff) * sizeof(char));

    return {new_buff, number_elem_new_buff};
}