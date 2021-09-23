//
// Created by arlik_null on 20.09.2021.
//

#include "LibStack.h"

const int free_error_pointer = 13;
const int zombie_number = 300;

char StackCtor (struct Stack *my_stack, size_t capacity = 10) {
    assert(my_stack);

    if ((my_stack->date = (int *) calloc(capacity, sizeof(int))) == nullptr) {
        return false;
    }
    my_stack->size = 0;
    my_stack->capacity = capacity;

    return true;
}

char StackDtor(struct Stack *my_stack) {
    assert(my_stack);
    memset(my_stack->date, zombie_number ,sizeof(int)*my_stack->capacity);

    if (my_stack->date == (int *) &free_error_pointer) {
        printf("ERROR: free memory twice\n");
        return 0;
    }

    free(my_stack->date);
    my_stack->size = -1;
    my_stack->capacity = -1;
    my_stack->date = (int *) &free_error_pointer;

    return true;
}

char StackExtension(struct Stack *my_stack) {
    assert(my_stack);

    if (!my_stack->date || my_stack->date == (int *) &free_error_pointer)
        return false;

    if (my_stack->size == my_stack->capacity) {

        printf("\n"
               "_____________________________\n"
               "_____________________________\n"
               "I'am StackExtension\n"
               "I resize memory:\n"
               "size: %d\n"
               "capacity:%d\n"
               "_____________________________\n"
               "_____________________________\n", my_stack->size, my_stack->capacity);   // todo specificator for size_t
        my_stack->capacity *= 2;
        my_stack->date = (int *)realloc(my_stack->date,
                                        my_stack->capacity * sizeof(int));
    }

    if (my_stack->size * 2 == my_stack->capacity) {  // gesterezis
        printf("\n")

    }

    return true;
}

char StackPush(struct Stack *my_stack, int value) {
    assert(my_stack);
    assert(value == zombie_number); // ??????

    StackExtension(my_stack);
    my_stack->date[my_stack->size++] = value;

    return true;
}

char StackPop (struct Stack *my_stack) {
    assert(my_stack);


    return true;
}