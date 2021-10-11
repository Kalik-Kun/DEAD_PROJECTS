/*
    Created by KALIK on 20.09.2021.
    This lib is created for my Stack
    I called my Stack that Skek
*/

#ifndef LIB_STACK_H_
#define LIB_STACK_H_

#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include <map>

#define DEB_ELEM(message) {__LINE__, __FILE__, __PRETTY_FUNCTION__, message}


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
    CANARY_FRONT_DIE,
    CANARY_BEHIND_DIE,
    CANARY_DATA_FRONT_DIE,
    CANARY_DATA_BEHIND_DIE,
    INCONSISTENCY_HASHES,

    // kekset erros
    NULLPTR_ARRAY,
    NULLPTR_ELEM,

    // file errors
    FILE_OPEN,


};

/// DEFENSE
/*
 * Showing program defense level
 *   NO_DEFENSE             - Program haven't defense
 *   FIRST_DEFENSE_LAYER    - Program have canary defence
 *   SECOND_DEFENSE_LAYER   - Program have hash and canary defence
 */
//#define NO_DEFENSE
//#define FIRST_DEFENSE_LAYER
#define SECOND_DEFENSE_LAYER

            /// CONSTS
// if skek->data have ptr 0x(FREE_ERROR_POINTER) that TWICE_ALLOCATE
extern const char FREE_ERROR_POINTER;
// if skek->data have ptr 0x(FREE_ERROR_POINTER) that TWICE_ALLOCATE
// (ZOMBIE_NUMBER) fill skek->data when skek was deleted
extern const char ZOMBIE_NUMBER;
// BAD_SIZE - size when skek was deleted
extern const long BAD_SIZE;
// Canary numbers
extern const long  CANARY_FRONT;
extern const long  CANARY_BEHIND;
extern const long  CANARY_DATA_FRONT;
extern const long  CANARY_DATA_BEHIND;
// capacity with skek started
extern long        START_CAPACITY;
// type size with skek started
extern long        START_SIZE_TYPE;
// UNDEFINED error if func havn't error
extern int         ERR_UNDEFINED;
// factor when capacity increase
extern const int   FACTOR_INCR_CAPACITY;
// factor when capacity decrease
extern const int   FACTOR_DECR_CAPACITY;
// log file for skek have info about skek
extern const char* LOGFILE_NAME;


/*
 * PRINT_TYPE - Show you whose type you print in
 *              print_void_arr and file_print_void_arr, these types:
 *      0 - bool type\n
 *      1 - integer type\n
 *      2 - fractional type\n
 */
extern const int   PRINT_TYPE;


/* debug elements - elem which show info about called func
 *  LINE - From which LINE the dump was called
 *  FILE - From which FILE the dump was called
 *  PRETTY_FUNCTION - From which FUNC the dump was called
 *  ERROR_MESSAGE   - error message
 *
 *  P.S.
 *  USE __ after and before name that give this param
 */
struct debug_elements {
    int LINE                     = -1;
    const char* FILE             = "Don't know";
    const char* PRETTY_FUNCTION  = "Don't know";
    const char* ERROR_MESSAGE    = "Don't know";
};

/*
 * Struct Skek - specific struct for anything type elems
 * data      - ptr on start memory where allocate data
 * type_size - size of type file in byte
 * size      - numbers elements
 * capacity  -  amount of allocated memory
*/
struct Skek {
    #ifndef NO_DEFENSE
    long  canary_front          = CANARY_FRONT;
    void* canary_data_front     = nullptr;
    #endif

    void* data      = nullptr;
    long  type_size = 0;
    long  size      = 0;
    long  capacity  = 0;

    #ifdef SECOND_DEFENSE_LAYER
    unsigned long long  hash    = 0;
    #endif

    #ifndef NO_DEFENSE
    void* canary_data_behind    = nullptr;
    long canary_behind          = CANARY_BEHIND;
    #endif
};


// func Skek

/// Constructor for Skek\n
/// Allocate memory size capacity * amount byte type
/// \param my_skek           - pointer on your skek
/// \param amount_byte_type  - amount byte in your type
/// \param capacity          - allocate memory in skek
/// \param error             - errors
/// \return True if operation successfully or False if not
char SkekCtor      (struct Skek * my_skek,
        long amount_byte_type = START_SIZE_TYPE,
        long capacity = START_CAPACITY,
        int* error = &ERR_UNDEFINED);

/// Destroy your skek\n
/// free memory and are filling skek by zombie numbers
/// \param my_skek - pointer on your skek
/// \param error   - errors
/// \return True if operation successfully or False if not
char SkekDtor      (struct Skek * my_skek, int* error = &ERR_UNDEFINED);

/// Extension capacity for Skek\n
/// (help function use in SkekPush and SkekPop)
/// \param my_skek - pointer on your skek
/// \param error   - errors
/// \return True if operation successfully or False if not
char SkekExtension (struct Skek * my_skek, int* error = &ERR_UNDEFINED);

/// Get value of top
/// \param my_skek - pointer on your skek
/// \param error   - errors
/// \return return pointer on yop element of skek
void* SkekGet      (struct Skek * my_skek, int* error = &ERR_UNDEFINED);

/// Push value of top Skek
/// \param my_skek - pointer on your skek
/// \param elem    - Elem which push
/// \param error   - errors
/// \return True if operation successfully or False if not
char SkekPush      (struct Skek * my_skek, void* elem, int* error = &ERR_UNDEFINED);

/// Delete element in top Skek
/// \param my_skek - pointer on your skek
/// \param error   - errors
/// \return Return pointer on top elem whose deleted and allocate memory for this element
void* SkekPop      (struct Skek* my_skek, int* error = &ERR_UNDEFINED);

/// Verificator use for find errors in stack
/// \param my_skek       - pointer on your skek
/// \param error         - errors
/// \param name_logfile  - name logfile
/// \return True if operation successfully or False if not
char SkekVerif     (struct Skek* my_skek, int* error = &ERR_UNDEFINED,
                    struct debug_elements = {}, const char* name_logfile = LOGFILE_NAME);


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
///                 4. error message\n
/// name_logfile  - the name of the file into which our stack is written\n
/// If you want change name log file use variable - LOGFILE_NAME\n
/// WARNING!!! Before SkekDump are completed logfile isn't cleaning\n
/// You need to clean logfile all time than you program is completed\n
/// Use func CleanLogFile() for this\n\n
// todo use html not txt for output logfile
char SkekDump      (struct Skek* my_skek, int* error = &ERR_UNDEFINED,
                    struct debug_elements debugElements = {}, const char* name_logfile = LOGFILE_NAME);

/// CleanLofFile - clean input log file\n
/// CleanLogFile  (const char* name_logfile = LOGFILE_NAME, int* errors = &ERR_UNDEFINED)\n
/// name_logfile - name input file\n
/// errors - errors\n
char CleanLogFile  (const char* name_logfile = LOGFILE_NAME, int* errors = &ERR_UNDEFINED);

/// print in file inputting status skek\n
/// (Help func for SkekDump)
/// \param my_skek - input skek
/// \param logfile - your logfile\n
/// (please if you wanna change logfile, change const LOGFILE_NAME
/// \param error   - your errors
/// \return
/// True or false ending operation
char fprint_status_skek (struct Skek* my_skek,
                        FILE* logfile, int* error= &ERR_UNDEFINED);

/// print in console inputting status skek\n
/// (Help func for SkekDump)
/// \param my_skek - input skek
/// \param error   - your errors
/// \return
/// True or false ending operation
char print_status_skek (struct Skek* my_skek, int* error= &ERR_UNDEFINED);

/// print_void_arr - print void arrays\n
/// const char* print_void_arr(void* ptr,
///                      int type = 1, long count_elem = 1,
///                      long type_size = 1, int* error = &ERR_UNDEFINED);\n\n
/// \param ptr         - pointer on you array\n
/// \param type        - type of type:\n
///                             0     - bool type\n
///                             1     - integer type\n
///                             2     - fractional type\n
///                             other - Hex type\n\n
///
/// \param count_elem  - count elements in input array\n
/// \param type_size   - size of your type\n
const char* print_void_arr(void* ptr,
                     int type = 1, long count_elem = 1, long type_size = 1);

/// file_print_void_arr - fprint void arrays in file\n
/// const char* file_print_void_arr(FILE* file, void* ptr,
///                      int type = 1, long count_elem = 1,
///                      long type_size = 1, int* error = &ERR_UNDEFINED);\n\n
/// \param file        - your file\n
/// \param ptr         - pointer on you array\n
/// \param type        - type of type:\n
///                             0     - bool type\n
///                             1     - integer type\n
///                             2     - fractional type\n
///                             other = Hex type\n\n
///
/// \param count_elem  - count elements in input array\n
/// \param type_size   - size of your type\n
const char* file_print_void_arr(FILE* file, void* ptr,
                     int type = 1, long count_elem = 1, long type_size = 1);

//todo understand what is shit. I steal this in iskander
/// this func calculate hash on inout data.
/// \param ptr   - pointer on array
/// \param size  - size input array
/// \param error - error
/// \return
/// Calculated hash
unsigned long long MyHashCalc(void* ptr, long size = 1, int* error = &ERR_UNDEFINED);

#endif