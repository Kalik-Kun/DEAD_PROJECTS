//
// Created by arlik_null on 20.09.2021.
//

#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <string.h>


enum {
    USE_FREE_MEMORY,
    TWICE_ALLOCATE,
    UNDEFINED
};

extern const char free_error_pointer;
extern const char zombie_number;

// todo i wish to make stack with differents types
// todo make this after I make void Stack

struct data {
    void* elem;
    int bytes_amount;
};

struct Stack {
    void* data;
    long  size_type;   // size of type file
    long  size;        // number where last elem + 1
    long  capacity;    // capacity or amount of allocated memory
};

// func stack

char StackCtor      (struct Stack *, long, long capacity = 10, int* error = (int *) UNDEFINED);   // Create Stack
char StackDtor      (struct Stack *, int *error = (int *) UNDEFINED);              // Destroy stack
char StackExtension (struct Stack *, int *error = (int *) UNDEFINED);              // Extension size stack
char StackGet       (struct Stack *, void*, int *error = (int *) UNDEFINED);              // get value of top
char StackPush      (struct Stack *, void*, int *error = (int *) UNDEFINED);         // push value of top stackchar StackPop       (struct Stack *, int *error = (int *) UNDEFINED);              // delete top value

// help func for stack

/// kekset - fills byte memory with one element, started from ptr to count_byte\n\n
/// kekset (void* ptr, void* elem, long count_byte, long size_type, StkError error)\n
/// ptr - pointer on start, elem - elem whose filled memory, count_byte - how many bytes need to be filled\n
/// size_type - size type of input element, error - error variable.

char kekset         (void *, void*,
                     size_t count_byte = 1, size_t size_type = 1, int error = UNDEFINED);