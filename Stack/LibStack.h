/*
    Created by KALIK on 20.09.2021.
    This lib is created for my Skek
    I called my Skek that Skek
*/

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

// todo i wish to make Skek with differents types
// todo make this after I make void Skek

struct data {
    void* elem;
    int bytes_amount;
};

/*
 * Struct Skek - specific struct for anything type elems
 * data - ptr on start memory where allocate data
 * size_type - size of type file in byte
 * size - number where top elem + 1
 * capacity or amount of allocated memory
*/
struct Skek {
    void* data;
    long  size_type;
    long  size;
    long  capacity;
};

// func Skek
// Constructor for Skek
char SkekCtor      (struct Skek *, long, long capacity = 10, int* error = (int *) UNDEFINED);
// Destroy Skek
char SkekDtor      (struct Skek *, int* error = (int *) UNDEFINED);
// Extension capacity for Skek
char SkekExtension (struct Skek *, int* error = (int *) UNDEFINED);
// get value of top return this value
void* SkekGet      (struct Skek *, int* error = (int *) UNDEFINED);
// push value of top Skek
char SkekPush      (struct Skek *, void*, int* error = (int *) UNDEFINED);
// Delete element of top Skek return top elem whose deleted and allocate memory for this element
void* SkekPop      (struct Skek* my_skek, int* error = (int *) UNDEFINED);
//
char SkekVerif      (struct Skek* my_skek, int* error = (int *) UNDEFINED);
// You are Dump Kalik(or nuts )
// todo __LINE__, __FILE__, __PRETTY_FUNCTION__, do struct for this
// todo good fump dead say that cool practic
char Skekdump      (struct Skek *, int* error);

// help func for Skek
// todo log file and dump

/// kekset - fills byte memory with one element, started from ptr to count_byte\n\n
/// kekset (void* ptr, void* elem, long count_byte, long size_type, StkError error)\n
/// ptr - pointer on start, elem - elem whose filled memory, count_byte - how many bytes need to be filled\n
/// size_type - size type of input element, error - error variable.

char kekset         (void *, void*,
                     size_t count_byte = 1, size_t size_type = 1, int* error = (int *) UNDEFINED);