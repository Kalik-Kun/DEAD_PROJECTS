
#include "KList.h"


const KL_SIZE_TYPE KL_START_BUFFER_SIZE = CHAR_MAX;
const KL_SIZE_TYPE KL_START_SIZE_TYPE = sizeof(char);


// debug
const char KL_FREE_ERROR_POINTER       = 13;
const char KL_ZOMBIE_NUMBER            = 17;
const KL_SIZE_TYPE KL_BAD_SIZE         = INT_MAX - 228;
const KL_SIZE_TYPE KL_START_SIZE       = -57;

const char* KL_LOGFILE_NAME       = "KListLogFile.txt";
const char* KL_GRAPHVIZFILE_NAME  = "KListGraphVizFile.txt";
const char* KL_PNG_NAME           = "KListViz.txt";


template<>
void KList<char>::print_elems() {
    KL_PRINT_ELEMS(%c)
}

//template<>
//void KList<unsigned int>::print_elems() {
//    KL_PRINT_ELEMS(%ud)
//}

template<>
void KList<int>::print_elems() {
    KL_PRINT_ELEMS(%d)
}

template<>
void KList<unsigned long>::print_elems() {
    KL_PRINT_ELEMS(%lud)
}

template<>
void KList<long>::print_elems() {
    KL_PRINT_ELEMS(%ld)
}

template<>
void KList<unsigned long long>::print_elems() {
    KL_PRINT_ELEMS(%llud)
}

template<>
void KList<long long>::print_elems() {
    KL_PRINT_ELEMS(%lld)
}

template<>
void KList<float>::print_elems() {
    KL_PRINT_ELEMS(%f)
}

template<>
void KList<double>::print_elems() {
    KL_PRINT_ELEMS(%lf)
}

template<>
void KList<char>::file_print_buffer(FILE* file) {
    KL_FILE_PRINT_BUFF(file, %c)
}

//template<>
//void KList<unsigned int>::file_print_buffer(FILE* file) {
//    KL_FILE_PRINT_BUFF(file, %ud)
//}

template<>
void KList<int>::file_print_buffer(FILE* file) {
    KL_FILE_PRINT_BUFF(file, %d)
}

template<>
void KList<unsigned long>::file_print_buffer(FILE* file) {
    KL_FILE_PRINT_BUFF(file, %lud)
}

template<>
void KList<long>::file_print_buffer(FILE* file) {
    KL_FILE_PRINT_BUFF(file, %ld)
}

template<>
void KList<unsigned long long>::file_print_buffer(FILE* file) {
    KL_FILE_PRINT_BUFF(file, %llud)
}

template<>
void KList<long long>::file_print_buffer(FILE* file) {
    KL_FILE_PRINT_BUFF(file, %lld)
}

template<>
void KList<float>::file_print_buffer(FILE* file) {
    KL_FILE_PRINT_BUFF(file, %f)
}

template<>
void KList<double>::file_print_buffer(FILE* file) {
    KL_FILE_PRINT_BUFF(file, %lf)
}


template<>
void KList<char>::print_buffer() {
    KL_PRINT_BUFF(%c)
}

//template<>
//void KList<unsigned int>::print_buffer() {
//    KL_PRINT_BUFF(%ud)
//}

template<>
void KList<int>::print_buffer() {
    KL_PRINT_BUFF(%d)
}

template<>
void KList<unsigned long>::print_buffer() {
    KL_PRINT_BUFF(%lud)
}

template<>
void KList<long>::print_buffer() {
    KL_PRINT_BUFF(%ld)
}

template<>
void KList<unsigned long long>::print_buffer() {
    KL_PRINT_BUFF(%llud)
}

template<>
void KList<long long>::print_buffer() {
    KL_PRINT_BUFF(%lld)
}

template<>
void KList<float>::print_buffer() {
    KL_PRINT_BUFF(%f)
}

template<>
void KList<double>::print_buffer() {
    KL_PRINT_BUFF(%lf)
}
