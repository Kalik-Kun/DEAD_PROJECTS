//
// Created by arlik_null on 20.09.2021.
//

#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

extern const int free_error_pointer;
extern const int zombie_number;
struct Stack {
    int *date;
    size_t size;        // number where last elem + 1
    size_t capacity;    // capacity or amount of allocated memory
};

// func stack
char StackCtor      (struct Stack *, size_t );      // Create Stack
char StackDtor      (struct Stack * );              // Destroy stack
char StackExtension (struct Stack *);               // Extension size stack
char StackGet       (struct Stack * );              // get value of top
char StackPush      (struct Stack * , int );        // push value of top stack
char StackPop       (struct Stack * );              // delete top value

