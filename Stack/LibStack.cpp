//
// Created by arlik_null on 20.09.2021.
//

#include "LibStack.h"

const char free_error_pointer = 13;
const char zombie_number = 17;

char SkekCtor   (struct Skek *my_skek, long amount_byte,
                long capacity, int* error) {
    assert(my_skek);

    if ((my_skek->data = (void *) calloc(capacity, amount_byte)) == nullptr) {
        return false;
    }

    my_skek->size_type = amount_byte;
    my_skek->size      = 0;
    my_skek->capacity  = capacity;

    return true;
}

char SkekDtor(struct Skek *my_skek, int *error) { // todo distrc for void
    assert(my_skek);

    // todo repair this for void Skek
    kekset(my_skek->data, (void *) &zombie_number, my_skek->capacity);

    if (my_skek->data == (void *) &free_error_pointer) {
        *error = TWICE_ALLOCATE;
        return false;
    }

    free(my_skek->data);
    my_skek->size = -1;
    my_skek->size_type = -1;
    my_skek->capacity = -1;
    my_skek->data = (void *) &free_error_pointer;
    return true;
}

char SkekExtension(struct Skek *my_skek, int* error) {
    assert(my_skek);

    if (!my_skek->data || my_skek->data == &free_error_pointer) {
        *error = USE_FREE_MEMORY;
        return false;
    }

    if (my_skek->size == my_skek->capacity) { // resize on

        printf("\n"
               "_____________________________\n"
               "_____________________________\n"
               "I'am SkekExtension\n"
               "I increase resize memory:\n"
               "size: %ld\n"
               "capacity:%ld\n"
               "_____________________________\n"
               "_____________________________\n", my_skek->size, my_skek->capacity);   // todo specificator for
        my_skek->capacity *= 2;
        my_skek->data = (void *)realloc(my_skek->data,
                                        my_skek->capacity * my_skek->size_type);
    }

    if (my_skek->size * 2 == my_skek->capacity) {  // resize low
        printf("\n"
               "_____________________________\n"
               "_____________________________\n"
               "I'am SkekExtension\n"
               "I decrease resize memory:\n"
               "size: %ld\n"
               "capacity:%ld\n"
               "_____________________________\n"
               "_____________________________\n", my_skek->size, my_skek->capacity);
    }

    my_skek->capacity = (long) my_skek->capacity / 2;
    my_skek->data = (void *)   realloc(my_skek->data,
                                     my_skek->capacity * my_skek->size_type);

    return true;
}

void* SkekGet (struct Skek* my_skek, int* error) {
    
}


char SkekPush(struct Skek *my_skek, void* value, int* error) {
    assert(my_skek);

    // todo i you will make diff Skek change this
    if (!SkekExtension(my_skek, error)) return false;
    kekset(my_skek->data, value, my_skek->size_type, my_skek->size_type);
    my_skek->size++;
    return true;
}

void* SkekPop (struct Skek* my_skek, int *error) {
    assert(my_skek);
    void* elem = (void *)calloc(my_skek->size_type, sizeof (char));
    void* top_elem = (char *) my_skek->data + (my_skek->size - 1)*my_skek->size_type;
    kekset(elem, top_elem, my_skek->size_type,  my_skek->size_type);
    my_skek->size--;

    if (!SkekExtension(my_skek, error)) return nullptr;
    return elem;
}




char kekset (void* ptr, void* elem, long count_byte, long size_type, int* error) {
    // todo finish up kekset
    assert(ptr);
    assert(elem);

    long number_byte = 0;

    long long* elem_long_long = (long long*) elem;
    long long* ptr_long_long  = (long long*) ptr;
    while (number_byte + sizeof(long long) < count_byte) {
        *(ptr_long_long + number_byte) = *elem_long_long;
        number_byte += sizeof (long long);
    }

    int* elem_int = (int*) elem;
    int* ptr_int  = (int*) ptr;
    while (number_byte + sizeof(int) < count_byte) {
        *(ptr_int + number_byte) = *elem_int;
        number_byte += sizeof(int);
    }

    short* elem_short = (short*) elem;
    short* ptr_short  = (short*) ptr;
    while (number_byte + sizeof(short) < count_byte) {
        *(ptr_short + number_byte) = *elem_short;
        number_byte += sizeof(short);
    }

    char* elem_char = (char*) elem;
    char* ptr_char  = (char*) ptr;
    while (number_byte < count_byte) {
        *(ptr_char + number_byte) = *elem_char;
        number_byte += sizeof(char);
    }

    return true;
}
