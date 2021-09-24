//
// Created by arlik_null on 20.09.2021.
//

#include "LibStack.h"

const char free_error_pointer = 13;
const char zombie_number = 17;

char StackCtor (struct Stack *my_stack, long amount_byte,
        long capacity, int* error) {
    assert(my_stack);

    if ((my_stack->data = (void *) calloc(capacity, amount_byte)) == nullptr) {
        return false;
    }

    my_stack->size_type = amount_byte;
    my_stack->size      = 0;
    my_stack->capacity  = capacity;

    return true;
}

char StackDtor(struct Stack *my_stack, int *error) { // todo distrc for void
    assert(my_stack);

    // todo repair this for void stack
    kekset(my_stack->data, (void *) &zombie_number, my_stack->capacity);

    if (my_stack->data == (void *) &free_error_pointer) {
        *error = TWICE_ALLOCATE;
        printf("ERROR: free memory twice\n");
        return 0;
    }

    free(my_stack->data);
    my_stack->size = -1;
    my_stack->size_type = -1;
    my_stack->capacity = -1;
    my_stack->data = (void *) &free_error_pointer;
    return true;
}

char StackExtension(struct Stack *my_stack, int* error) {
    assert(my_stack);

    if (!my_stack->data || my_stack->data == &free_error_pointer) {
        *error = USE_FREE_MEMORY;
        return false;
    }

    if (my_stack->size == my_stack->capacity) { // resize on

        printf("\n"
               "_____________________________\n"
               "_____________________________\n"
               "I'am StackExtension\n"
               "I increase resize memory:\n"
               "size: %ld\n"
               "capacity:%ld\n"
               "_____________________________\n"
               "_____________________________\n", my_stack->size, my_stack->capacity);   // todo specificator for
        my_stack->capacity *= 2;
        my_stack->data = (void *)realloc(my_stack->data,
                                        my_stack->capacity * my_stack->size_type);
    }

    if (my_stack->size * 2 == my_stack->capacity) {  // resize low
        printf("\n"
               "_____________________________\n"
               "_____________________________\n"
               "I'am StackExtension\n"
               "I decrease resize memory:\n"
               "size: %ld\n"
               "capacity:%ld\n"
               "_____________________________\n"
               "_____________________________\n", my_stack->size, my_stack->capacity);
    }

    my_stack->capacity = (long) my_stack->capacity / 2;
    my_stack->data = (void *)realloc(my_stack->data,
                                     my_stack->capacity * my_stack->size_type);

    return true;
}

char StackPush(struct Stack *my_stack, void* value, int* error) {
    assert(my_stack);

    // todo i you will make diff stack change this
    StackExtension(my_stack);
    kekset(my_stack->data, value);
    my_stack->size++;
    return true;
}

void* StackPop (struct Stack* my_stack, int *error) {
    void* elem = (void *)calloc(my_stack->size_type, sizeof (char));
    kekset(elem, (void *) (my_stack->data + my_stack->size));


}

char kekset (void* ptr, void* elem, long count_byte, long size_type, int* error = (int *)UNDEFINED) {
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
