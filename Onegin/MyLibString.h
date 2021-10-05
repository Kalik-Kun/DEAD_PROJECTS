//
// Created by arlik_null on 14.09.2021.
//

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <iostream>
#include <sys/stat.h>
#include <assert.h>
#define DEBAG      printf("\ndebag\n");

// This is one string
struct mystr {
    char *str;
    size_t len;
};

// array pointers on my string
struct myarr {
    void* buff;
    struct mystr* arr;
    size_t size;
};

// work with file func
//char*           find_dir_prog                   (char *envp[]);
FILE*           open_file                       (const char *);     // open file

// work with array function
struct  myarr   file_reading                    (FILE*, const char*);           // reading file and write line on arr string
void            free_memory_for_string_array    (struct myarr*);                // to free memory of myarr variable
void            write_sort_arr_in_file          (struct myarr*, const char*);   // don't work

// sort func for dead
void            bubble_sort                     (struct myarr*);                 // sorted array is outputted by bubble
void            bubble_sort_revers              (struct myarr*);                 // sort from the end (rhyme sort)
void            quick_sort                      (struct myarr*);                 // my quick sort
void            quick_sort_arr_string           (struct mystr*, size_t, size_t); // func with algo of quick sort
void            quick_sort_reverse              (struct myarr*);                 // reverse my quick sort
void            quick_sort_reverse_arr_string   (struct mystr*, size_t, size_t); // func wigh algo of reverse quick sort

// comparators for sort func
char            comp                            (struct mystr*, struct mystr*); // comp for my strings if first string > second string return true else return false
char            comp_reverse                    (struct mystr*, struct mystr*); // reverse comp for my string
int             comp_qsort                      (const void*, const void*);     // comparator for c qsort
int             comp_qsort_reverse              (const void*, const void*);     // reverse comparator for c qsort not optimize because do esy thing

// unit test
void            unit_test_bubble_sort           (struct myarr);                 // bubble test
void            unit_test_reverse_bubble_sort   (struct myarr);                 // reverse bubble test
void            unit_test_my_quick_sort         (struct myarr);                 // my quick sort test
void            unit_test_reverse_my_quick_sort (struct myarr);                 // reverse my quick sort test

// help func
void            swap_mystr                      (struct mystr*, struct mystr*); // swap string
void            copy_string                     (struct mystr*, struct mystr*); // copy second string in first input string (also allocate memory for first string)
void            copy_arr_string                 (struct myarr*, struct myarr*); // copy second array of string in first input arr_of_string (also allocate memory for first string)
size_t          out_file_size                   (const char *);                 // return size of file(inout name file in const char*
size_t          find_count_elems                (char* , const char);           // to count amount of input simb in inout strung
void            print_array                     (struct myarr);                 // print final array
void            print_array_on_file             (struct myarr*, const char*);                // print sorted array in file
void            reverse_mystr                   (struct mystr*);                // reverse input string
char            is_it_letter                    (const char);                   // checks a character for a letter return true if it is letter else false
template <typename type>
void            my_swap                         (type* , type* );               // swap all type elements
void            print_arr_left_to_right         (struct mystr*, size_t, size_t);// print array in certain interval (left ot right) with broader
void            cleaning_file_and_record        (const char*, const char*);     // enter: inout_file, file (whose will be clean) func clean files and is recording them on second const char
struct mystr    clean                           (const char*, const long);      // cleans files from extra spaces, etc.





template <typename type>
void my_swap(type* a, type* b) {
    type c = *a;
    *a = *b;
    *b = c;
}


