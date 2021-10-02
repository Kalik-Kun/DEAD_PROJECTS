/*
    Created by KALIK on 20.09.2021.
    This lib is created for my Skek
    I called my Skek that Skek
*/

#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <limits.h>
#include <map>


// errors lib
enum {
    // own for lib
    UNDEFINED,

    // func skek erros
    NULLPTR_ON_SKEK,
    SIZE_LARGE_CAPACITY,
    STACK_ALREADY_CREATED,
    ERROR_ALLOCATE_MEMORY,
    GET_WITHOUT_ELEM,
    POP_WITHOUT_ELEM,
    TWICE_ALLOCATE,
    NEGATIVE_SIZE,
    NULLPTR_IN_DATA,

    // kekset erros
    NULLPTR_ARRAY,
    NULLPTR_ELEM,

    // file errors
    FILE_OPEN,


};
// todo you must update map when you update enum
// todo when you update enum is shifting
extern const std::map<int, char*> NAME_ERRORS;



            /// CONST
// if skek->data have ptr 0x(FREE_ERROR_POINTER) that TWICE_ALLOCATE
extern const char FREE_ERROR_POINTER;
// (ZOMBIE_NUMBER) fill skek->data when skek was deleted
extern const char ZOMBIE_NUMBER;
// BAD_SIZE - size when skek was deleted
extern const long BAD_SIZE;
//
extern const long CANARY_NUMBER;
// UNDEFINED error if func havn't error
// todo check for update
extern int        ERR_UNDEFINED;
// factor when capacity increase
extern const int FACTOR_INCR_CAPACITY;
// factor when capacity decrease
extern const int FACTOR_DECR_CAPACITY;
// log file for skek have info about skek
extern char* LOGFILE_NAME;

extern const int PRINT_TYPE;

// todo i wish to make Skek with differents types
// todo make this after I make void Skek
// todo canary with data and anythere
// todo hash
struct debug_elements {
    int LINE                = 0;
    char* FILE              = nullptr;
    char* PRETTY_FUNCTION   = nullptr;
};

/*
 * Struct Skek - specific struct for anything type elems
 * data - ptr on start memory where allocate data
 * size_type - size of type file in byte
 * size - numbers elements
 * capacity or amount of allocated memory
*/
struct Skek {
    void* data      = nullptr;
    long  size_type = 1;
    long  size      = 0;
    long  capacity  = 10;
};

// func Skek
// Constructor for Skek
char SkekCtor      (struct Skek * my_skek, long, long capacity = 10, int* error = &ERR_UNDEFINED);
// Destroy Skek
char SkekDtor      (struct Skek * my_skek, int* error = &ERR_UNDEFINED);
// Extension capacity for Skek
char SkekExtension (struct Skek * my_skek, int* error = &ERR_UNDEFINED);
// get value of top return this value
void* SkekGet      (struct Skek * my_skek, int* error = &ERR_UNDEFINED);
// push value of top Skek
char SkekPush      (struct Skek * my_skek, void*, int* error = &ERR_UNDEFINED);
// Delete element of top Skek return top elem whose deleted and allocate memory for this element
void* SkekPop      (struct Skek* my_skek, int* error = &ERR_UNDEFINED);
// Verificator use for find errors in stack
char SkekVerif     (struct Skek* my_skek, int* error = &ERR_UNDEFINED);

// You are Dump Kalik(or nuts )
// todo __LINE__, __FILE__, __PRETTY_FUNCTION__, do struct for this
// todo good fump dead say that cool practic
char SkekDump      (struct Skek * my_skek,
                    const char* name_logfile = LOGFILE_NAME, struct debug_elements debugElements = {},
                    int* error = &ERR_UNDEFINED);

// help func for Skek

/// kekset - fills byte memory with one element, started from ptr to count_elem * size_type\n\n
/// kekset (void* ptr, void* elem, long count_elem, long size_type, StkError error)\n
///         ptr        - pointer on start,\n
///         elem       - elem whose filled memory,\n
///         count_elem - count elem with size in bytes: size_type\n
///         size_type  - size type of input element, error - error variable.\n\n
/// ELEM MUST BE ALLOCATED

char kekset        (void *, void*,
                     long count_elem = 1, long size_type = 1, int* error = &ERR_UNDEFINED);

// Clean skek logfile
char CleanLogFile  (const char* name_logfile = LOGFILE_NAME, int* errors = &ERR_UNDEFINED);

/// print_void_arr - print void arrays\n
/// char* print_void_arr(void* ptr,
///                      int type = 1, long count_elem = 1,
///                      long size_type = 1, int* error = &ERR_UNDEFINED);\n
///         ptr         - pointer on you array\n
///         type        - type of type:\n
///                             0 - bool type\n
///                             1 - integer type\n
///                             2 - fractional type\n
///
///         count_elem  - count elements in input array\n
///         size_type   - size of your type\n

char* print_void_arr(void* ptr,
                     int type = 1, long count_elem = 1, long size_type = 1);

/// file_print_void_arr - fprint void arrays in file\n
/// char* file_print_void_arr(FILE* file, void* ptr,
///                      int type = 1, long count_elem = 1,
///                      long size_type = 1, int* error = &ERR_UNDEFINED);\n
///         file        - your file\n
///         ptr         - pointer on you array\n
///         type        - type of type:\n
///                             0 - bool type\n
///                             1 - integer type\n
///                             2 - fractional type\n
///
///         count_elem  - count elements in input array\n
///         size_type   - size of your type\n

char* file_print_void_arr(FILE* file, void* ptr,
                     int type = 1, long count_elem = 1, long size_type = 1);