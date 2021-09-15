//
// Created by arlik_null on 14.09.2021.
//

//
// Created by arlik_null on 13.09.2021.
//

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>


#define NAME_INPUT_FILE "Onegin.txt"
#define NAME_OUTPUT_FILE "output_file.txt"

// одна строка
struct mystr {
    char *str;
    long len;
};

// массив указателей на строки
struct myarr {
    struct mystr* arr;
    long size;
};

FILE*           open_file                       ();                             // открывает файл
struct  myarr   make_array                      (FILE*);                        // распределяет текст в двумерный массив чаров
char            checking_for_a_word             (char);                         // смотрит чтобы в массив поподали только слова
void            print_array                     (struct myarr);                 // печатает итоговый массив
void            print_array_on_file             (struct myarr);                 // печатает отсорченый массив в файл
struct  mystr*  size_up_array                   (struct mystr*, const long);    // изменяет длину массива указателей на строки на size
char*           size_up_len_string              (char*, const long);            // изменяет длину строки на size
struct  myarr   bubble_sort                     (struct myarr);                 // возвращает отсортированый пузырком массив
struct  myarr   bubble_sort_revers              (struct myarr);                 // сортирует с конца ищет рифмы
char            comp                            (struct mystr, struct mystr);   // компонатор для пузырьковой сортировки
void            _swap                           (struct mystr*, struct mystr*); // свап который не работает
char            comp_reverse                    (struct mystr, struct mystr);   // компоратор для обратного пузырька
int             comp_qsort                      (const void*, const void*);     // компоратор для квик сорта
int             comp_qsort_reverse              (const void*, const void*);     // компоратор для обратного квик сорта
void            unit_test_bubble_sort            (struct myarr);                // тест пузырька
void            unit_test_reverse_bubble_sort   (struct myarr);                 // тест обратного пузырька


