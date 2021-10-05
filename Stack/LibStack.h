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
#include <time.h>
#include <map>

#define DEB_ELEM {__LINE__, __FILE__, __PRETTY_FUNCTION__}

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

extern long START_CAPACITY;

extern long START_SIZE_TYPE;

// UNDEFINED error if func havn't error
// todo check for update
extern int        ERR_UNDEFINED;
// factor when capacity increase
extern const int FACTOR_INCR_CAPACITY;
// factor when capacity decrease
extern const int FACTOR_DECR_CAPACITY;
// log file for skek have info about skek
extern const char* LOGFILE_NAME;


/*
 * PRINT_TYPE - Show you whose type you print in
 *              print_void_arr and file_print_void_arr, these types:
 *      0 - bool type\n
 *      1 - integer type\n
 *      2 - fractional type\n
 */
extern const int PRINT_TYPE;

// todo i wish to make Skek with differents types
// todo make this after I make void Skek
// todo canary with data and anythere
// todo hash

/* debug elements - elem which show info about called func
 *  LINE - From which LINE the dump was called
 *  FILE - From which FILE the dump was called
 *  PRETTY_FUNCTION - From which FUNC the dump was called
 *
 *  P.S.
 *  USE __ after and before name that give this param
 */

struct debug_elements {
    int LINE                     = -1;
    const char* FILE             = "Don't know";
    const char* PRETTY_FUNCTION  = "Don't know";
};

/*
 * Struct Skek - specific struct for anything type elems
 * data      - ptr on start memory where allocate data
 * type_size - size of type file in byte
 * size      - numbers elements
 * capacity  -  amount of allocated memory
*/
struct Skek {
    void* data      = nullptr;
    long  type_size = 0;
    long  size      = 0;
    long  capacity  = 0;
};

// func Skek
// Constructor for Skek
char SkekCtor      (struct Skek * my_skek,
        long amount_byte_type = START_SIZE_TYPE,
        long capacity = START_CAPACITY,
        int* error = &ERR_UNDEFINED);
// Destroy Skek
char SkekDtor      (struct Skek * my_skek, int* error = &ERR_UNDEFINED);
// Extension capacity for Skek
char SkekExtension (struct Skek * my_skek, int* error = &ERR_UNDEFINED);
// get value of top return this value
void* SkekGet      (struct Skek * my_skek, int* error = &ERR_UNDEFINED);
// push value of top Skek
char SkekPush      (struct Skek * my_skek, void* elem, int* error = &ERR_UNDEFINED);
// Delete element of top Skek return top elem whose deleted and allocate memory for this element
void* SkekPop      (struct Skek* my_skek, int* error = &ERR_UNDEFINED);
// Verificator use for find errors in stack
char SkekVerif     (struct Skek* my_skek, int* error ,
                    struct debug_elements = {}, const char* name_logfile = LOGFILE_NAME);

// You are Dump Kalik(or nuts )

/// SkekDump - func print your skek in file\n
/// also print errors skeks in console with red color\n
/// SkekDump      (struct Skek * my_skek, int* error = &ERR_UNDEFINED,\n
///                struct debug_elements debugElements = {}, const char* name_logfile = LOGFILE_NAME);\n\t
/// my_skek       - your inout skek\n
/// error         - error flag\n
/// debugElements - element for debug\n
///                 1. From which LINE the dump was called\n
///                 2. From which FILE the dump was called\n
///                 3. From which FUNC the dump was called\n
/// name_logfile  - the name of the file into which our stack is written\n
/// If you want change name log file use variable - LOGFILE_NAME\n
/// WARNING!!! Before SkekDump are completed logfile isn't cleaning\n
/// You need to clean logfile all time than you program is completed\n
/// Use func CleanLogFile() for this\n\n
// todo use html not txt for output logfile
char SkekDump      (struct Skek* my_skek, int* error = &ERR_UNDEFINED,
                    struct debug_elements debugElements = {}, const char* name_logfile = LOGFILE_NAME);

// help func for Skek

/// kekset - fills byte memory with one element, started from ptr to count_elem * type_size\n\n
/// kekset (void* ptr, void* elem, long count_elem, long type_size, StkError error)\n
///         ptr        - pointer on start,\n
///         elem       - elem whose filled memory,\n
///         count_elem - count elem with size in bytes: type_size\n
///         type_size  - size type of input element, error - error variable.\n
/// ELEM MUST BE ALLOCATED\n
char kekset        (void* ptr, void* elem,
                     long count_elem = 1, long type_size = 1, int* error = &ERR_UNDEFINED);

/// CleanLofFile - clean input log file\n
/// CleanLogFile  (const char* name_logfile = LOGFILE_NAME, int* errors = &ERR_UNDEFINED)\n
/// name_logfile - name input file\n
/// errors - errors\n
char CleanLogFile  (const char* name_logfile = LOGFILE_NAME, int* errors = &ERR_UNDEFINED);

/// print_void_arr - print void arrays\n
/// const char* print_void_arr(void* ptr,
///                      int type = 1, long count_elem = 1,
///                      long type_size = 1, int* error = &ERR_UNDEFINED);\n\n
///         ptr         - pointer on you array\n
///         type        - type of type:\n
///                             0     - bool type\n
///                             1     - integer type\n
///                             2     - fractional type\n
///                             other - Hex type\n\n
///
///         count_elem  - count elements in input array\n
///         type_size   - size of your type\n
const char* print_void_arr(void* ptr,
                     int type = 1, long count_elem = 1, long type_size = 1);

/// file_print_void_arr - fprint void arrays in file\n
/// const char* file_print_void_arr(FILE* file, void* ptr,
///                      int type = 1, long count_elem = 1,
///                      long type_size = 1, int* error = &ERR_UNDEFINED);\n\n
///         file        - your file\n
///         ptr         - pointer on you array\n
///         type        - type of type:\n
///                             0     - bool type\n
///                             1     - integer type\n
///                             2     - fractional type\n
///                             other = Hex type\n\n
///
///         count_elem  - count elements in input array\n
///         type_size   - size of your type\n
const char* file_print_void_arr(FILE* file, void* ptr,
                     int type = 1, long count_elem = 1, long type_size = 1);