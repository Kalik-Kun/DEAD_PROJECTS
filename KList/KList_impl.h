//
// Created by arlik_null on 28.01.2022.
//

#ifndef KLIST_KLIST_IMPL_H
#define KLIST_KLIST_IMPL_H

//
// Created by arlik_null on 15.11.2021.
//

template <typename KL_TYPE>
KList<KL_TYPE>::KList() {

    FILE* file = fopen(this->name_logfile, "w");
    if (file == nullptr) {
        printf("\x1b[31;5m"
               "ERROR: file can't input\n"
               "Please reload program\n"
               "\x1b[0m");
        *this->error = KL_FILE_OPEN;
        exit(KL_FILE_OPEN);
    }
    fclose(file);

    this->buffer_size = KL_START_BUFFER_SIZE;
    this->tale        = 0;
    this->head        = 0;
    this->size        = 0;
    this->free_ptr        = 0;
    this->KL_ERR      = KL_UNDEF;

    for (KL_SIZE_TYPE i = 0; i < this->buffer_size;  i++) {
        this->buffer[i].rp  = i + 1;
        this->buffer[i].lp  = -1;
        this->buffer[i].val = (KL_TYPE)KL_ZOMBIE_NUMBER;
    }
    this->buffer[this->buffer_size - 1].val = 0;

    this->buffer = (KL_Data*)
            calloc(this->buffer_size, sizeof(KL_Data));

    if (!this->KLVerif(KL_DEB_ELEM("Don't know"))) {
        exit(*this->error);
    }
}

template <typename KL_TYPE>
KList<KL_TYPE>::KList(KL_SIZE_TYPE buff_size) {

    FILE* file = fopen(this->name_logfile, "w");
    if (file == nullptr) {
        printf("\x1b[31;5m"
               "ERROR: file can't input\n"
               "Please reload program\n"
               "\x1b[0m");
        *this->error = KL_FILE_OPEN;
        exit(KL_FILE_OPEN);
    }
    fclose(file);

    if (buff_size > KL_START_BUFFER_SIZE)
        this->buffer_size = buff_size;
    else
        this->buffer_size = KL_START_BUFFER_SIZE;
    this->tale        = 0;
    this->head        = 0;
    this->size        = 0;
    this->free_ptr        = 0;
    this->KL_ERR      = KL_UNDEF;

    this->buffer = (KL_Data*)
            calloc(this->buffer_size, sizeof(KL_Data));

    // for free_ptr pointer
    for (KL_SIZE_TYPE i = 0; i < this->buffer_size;  i++) {
        this->buffer[i].rp  = i + 1;
        this->buffer[i].lp  = -1;
        this->buffer[i].val = (KL_TYPE)KL_ZOMBIE_NUMBER;
    }
    this->buffer[this->buffer_size - 1].val = 0;


    if (!this->KLVerif(KL_DEB_ELEM("Don't know"))) {
        exit(*this->error);
    }
}

template<typename KL_TYPE>
KList<KL_TYPE>::~KList(){
    if (!this->KLVerif(KL_DEB_ELEM("Don't know"))) {
        exit(*this->error);
    }

    memset(this->buffer, KL_ZOMBIE_NUMBER, this->buffer_size*sizeof(KL_Data));
    free(this->buffer);


    this->buffer_size = KL_BAD_SIZE;
    this->tale        = KL_BAD_SIZE;
    this->head        = KL_BAD_SIZE;
    this->size        = KL_BAD_SIZE;
    this->free_ptr        = KL_BAD_SIZE;
    this->buffer      = (KL_Data*) KL_FREE_ERROR_POINTER;
}

template <typename KL_TYPE>
bool KList<KL_TYPE>::KLPushBegin(KL_TYPE elem) {
    if (!this->KLVerif(KL_DEB_ELEM("Don't know"))) {
        return false;
    }

    KL_SIZE_TYPE Index = this->free_ptr;
    this->free_ptr         = this->buffer[this->free_ptr].rp;
    this->buffer[this->head].rp = Index;
    this->buffer[Index].val     = elem;
    this->buffer[Index].lp      = this->head;
    this->buffer[Index].rp      = this->tale;
    this->head                  = Index;
    this->size++;

    if(!this->KLExtension()) return false;

    if (!this->KLVerif(KL_DEB_ELEM("Don't know"))) {
        return false;
    }
    return true;
}

template <typename KL_TYPE>
bool KList<KL_TYPE>::KLPushEnd(KL_TYPE elem) {
    if (!this->KLVerif(KL_DEB_ELEM("Don't know"))) {
        return false;
    }

    KL_SIZE_TYPE  Index = this->free_ptr;
    this->free_ptr          = this->buffer[this->free_ptr].rp;
    this->buffer[this->tale].lp = Index;
    this->buffer[Index].val     = elem;
    this->buffer[Index].rp      = this->tale;
    this->buffer[Index].lp      = this->head;
    this->tale                  = Index;
    this->size++;

    if(!this->KLExtension()) return false;


    if (!this->KLVerif(KL_DEB_ELEM("Don't know"))) {
        return false;
    }
    return true;
}

template <typename KL_TYPE>
bool KList<KL_TYPE>::KLInsertAfter(KL_SIZE_TYPE index, KL_TYPE elem) {
    if (!this->KLVerif(KL_DEB_ELEM("Don't know"))) {
        return false;
    }

    if (this->tale == index) {
        if (!this->KLPushEnd(elem)) {
            return false;
        }
        return true;
    }

    KL_SIZE_TYPE NewIndex       = this->free_ptr;
    this->free_ptr              = this->buffer[this->free_ptr].rp;

    this->buffer[NewIndex].val  = elem;
    this->buffer[NewIndex].rp   = index;
    this->buffer[NewIndex].lp   = this->buffer[index].lp;
    this->buffer[this->buffer[NewIndex].lp].rp = NewIndex;
    this->buffer[index].lp      = NewIndex;
    this->size++;

    if(!this->KLExtension()) return false;

    if (!this->KLVerif(KL_DEB_ELEM("Don't know"))) {
        return false;
    }
    return true;
}

template <typename KL_TYPE>
bool KList<KL_TYPE>::KLInsertBefore(KL_SIZE_TYPE index, KL_TYPE elem) {
    if (!this->KLVerif(KL_DEB_ELEM("Don't know"))) {
        return false;
    }

    if (this->head == index) {
        if (!this->KLPushBegin(elem)) {
            return false;
        }
        return true;
    }

    KL_SIZE_TYPE NewIndex   = this->free_ptr;
    this->free_ptr              = this->buffer[this->free_ptr].rp;

    this->buffer[NewIndex].val = elem;
    this->buffer[NewIndex].rp  = this->buffer[index].rp;
    this->buffer[NewIndex].lp  = index;
    this->buffer[this->buffer[NewIndex].rp].lp = NewIndex;
    this->buffer[index].rp    = NewIndex;
    this->size++;

    if (!this->KLExtension()) return false;

    if (!this->KLVerif(KL_DEB_ELEM("Don't know"))) {
        return false;
    }
    return true;
}

template <typename KL_TYPE>
KL_TYPE KList<KL_TYPE>::KLDelete(KL_SIZE_TYPE index) {
    if (!this->KLVerif(KL_DEB_ELEM("Don't know"))) {
        return false;
    }

    this->buffer[this->buffer[index].rp].lp = this->buffer[index].lp;
    this->buffer[this->buffer[index].lp].rp = this->buffer[index].rp;

    this->buffer[index].rp  = this->free_ptr;
    this->buffer[index].lp  = -1;
    this->buffer[index].val = (KL_TYPE) KL_ZOMBIE_NUMBER;
    this->free_ptr = index;
    this->size--;

    if (!this->KLVerif(KL_DEB_ELEM("Don't know"))) {
        return false;
    }
    return true;
}





template <typename KL_TYPE>
bool KList<KL_TYPE>::KLExtension() {
    if (!this->KLVerif(KL_DEB_ELEM("Don't know"))) {
        return false;
    }

    if (this->size + 3 >= this->buffer_size) {

        KL_SIZE_TYPE new_len = buffer_size * 2;

#ifdef ABOBADEBAG
        printf("\n\x1b[32;1m"
               "_____________________________\n"
               "_____________________________\n"
               "I'm KLExtension\n"
               "I increase buffer:\n"
               "KList::buffer:            %p\n"
               "KList::buffer_size:       %d\n"
               "KList::size:              %d\n"
               "will KList::buffer_size:  %d\n"
               "_____________________________\n"
               "_____________________________\n"
               "\x1b[0m",
        this->buffer, this->buffer_size, this->size, new_len);

#endif

        KL_Data* error_var = (KL_Data*)realloc(this->buffer, sizeof(KL_Data)*new_len);
        if (error_var == nullptr) {
            *this->error = KL_NULLPTR_IN_REALLOC;
            KLDump(KL_DEB_ELEM("Nullptr in realloc in KList Extension"));
            return false;
        }

        for (KL_SIZE_TYPE i = buffer_size - 1; i < new_len; i ++) {
            this->buffer[i].rp  = i + 1;
            this->buffer[i].lp  = -1;
            this->buffer[i].val = (KL_TYPE)KL_ZOMBIE_NUMBER;
        }
        this->buffer[new_len - 1].val = 0;

        this->buffer_size = new_len;
        this->buffer      = error_var;

        if (!this->KLVerif(KL_DEB_ELEM("Don't know"))) {
            return false;
        }

        return true;
    }

    if (!this->KLVerif(KL_DEB_ELEM("Don't know"))) {
        return false;
    }

    return true;
}


template <typename KL_TYPE>
KL_SIZE_TYPE KList<KL_TYPE>::get_size() {
    return this->size;
}

template <typename KL_TYPE>
int KList<KL_TYPE>::get_error() {
    return *this->error;
}

template <typename KL_TYPE>
const char* KList<KL_TYPE>::get_logfile_name() {
    return this->name_logfile;
}

template <typename KL_TYPE>
void KList<KL_TYPE>::set_logfile_name(const char* name) {
    this->name_logfile = name;
}

template <typename KL_TYPE>
void KList<KL_TYPE>::print_elems() {
    KL_SIZE_TYPE ptr = this->tale;
    while (ptr != this->head) {
        printf("buffer[%d]: ", ptr);
        printf("%d  ->  ", this->buffer[ptr].lp);
        for (int pos_byte = 0; pos_byte < sizeof(KL_TYPE); pos_byte++) {
            printf("%02X",
                   *((char *)this->buffer + ptr * sizeof(KL_Data) + pos_byte));
        }
        printf("  ->  %d\n", this->buffer[ptr].rp);
        ptr = this->buffer[ptr].rp;
    }
    printf("buffer[%d]: ", ptr);
    printf("%d  ->  ", this->buffer[ptr].lp);
    for (int pos_byte = 0; pos_byte < sizeof(KL_TYPE); pos_byte++) {
        printf("%02X",
               *((char *)this->buffer + ptr * sizeof(KL_Data) + pos_byte));
    }
    printf("  ->  %d\n", this->buffer[ptr].rp);
    printf("\n");
}

/// DUMP

template <typename KL_TYPE>
bool KList<KL_TYPE>::KLDump(kl_debug_elements debElem) {
    FILE* file = fopen(KL_LOGFILE_NAME, "a");
    if (file == nullptr) {
        printf("\x1b[31;5m"
               "ERROR: file can't input\n"
               "Please reload program\n"
               "\x1b[0m");
        *this->error = KL_FILE_OPEN;
        return false;
    }

    // time
    struct tm *ptr;
    time_t It;
    It = time(NULL);
    ptr = localtime(&It);

    if (*this->error != KL_UNDEF) {
        small_dump(debElem);

        printf("KList::buffer_size:     %d\n"
               "KList::size:            %d\n"
               "KList::tale:            %d\n"
               "KList::head:            %d\n"
               "KList::free_ptr:            %d\n"
               "KList:buffer:\n",
               this->buffer_size, this->size,
               this->tale, this->head, this->free_ptr);

        if(this->buffer == nullptr ||
           this->buffer == (KL_Data*)KL_FREE_ERROR_POINTER) {
            printf("KList hasn't buffer\n");
        }
        else {
            this->print_buffer();
        }

        printf("END ERROR KList\n"
               "END DUMP\n\n");
    }

    // block input in file
    fprintf(file,"\n"
                 "TIME : %s"
                 "START DUMP\n"
                 "LAUNCHED FROM:\n"
                 "FILE: %s\n"
                 "FUNC: %s\n"
                 "LINE: %d\n"
                 "MESSAGE: %s\n",
            asctime(ptr),
            debElem.FILE, debElem.PRETTY_FUNCTION,
            debElem.LINE, debElem.ERROR_MESSAGE);

    if(*this->error != KL_UNDEF) {
        fprintf(file,"!!!!ERROR KLIST!!!!\n"
                     "SKEK ERROR NUMBER: %d\n"
                     "That's mean: %s\n\n",
                *this->error, debElem.ERROR_MESSAGE);
    }

    else
        fprintf(file, "NORMAL SKEK\n");

    fprintf(file, "KList::buffer_size:     %d\n"
                  "KList::size:            %d\n"
                  "KList::tale:            %d\n"
                  "KList::head:            %d\n"
                  "KList::free_ptr:        %d\n"
                  "KList:buffer:\n",
            this->buffer_size, this->size,
            this->tale, this->head, this->free_ptr);

    if (this->buffer == nullptr ||
        this->buffer == (KL_Data*)KL_FREE_ERROR_POINTER) {
        fprintf(file, "KList hasn't buffer\n");
    }
    else {
        file_print_buffer(file);
    }

    if (*this->error == KL_UNDEF) fprintf(file, "END ERROR KLIST\n");
    else                         fprintf(file, "END KLIST\n");

    fprintf(file, "END DUMP\n\n");

    fclose(file);
    return true;
}


template<typename KL_TYPE>
bool KList<KL_TYPE>::KLVerif(kl_debug_elements debElem) {
    if (this->buffer == nullptr) {
        *this->error = KL_BUFF_NULLPTR;
        KLDump(debElem);
        return false;
    }

    if (this->buffer_size == KL_BAD_SIZE ||
        this->size        == KL_BAD_SIZE ||
        this->tale        == KL_BAD_SIZE ||
        this->head        == KL_BAD_SIZE ||
        this->free_ptr    == KL_BAD_SIZE ||
        this->buffer      == (KL_Data*) KL_FREE_ERROR_POINTER) {
        *this->error = KL_TWICE_ALLOCATE;
        debElem.ERROR_MESSAGE = "KList was twice allocate";
        KLDump(debElem);
        return false;
    }

    if (this->buffer_size < 0) {
        *this->error = KL_NEGATIVE_BUFFER_SIZE;
        debElem.ERROR_MESSAGE = "KList have negative buffer size";
        KLDump(debElem);
        return false;
    }

    if (this->size < 0) {
        *this->error = KL_NEGATIVE_SIZE;
        debElem.ERROR_MESSAGE = "KList have negative size";
        KLDump(debElem);
        return false;
    }

    if (this->tale < 0) {
        *this->error = KL_NEGATIVE_TALE;
        debElem.ERROR_MESSAGE = "KList have negative tale";
        KLDump(debElem);
        return false;
    }

    if (this->head < 0) {
        *this->error = KL_NEGATIVE_HEAD;
        debElem.ERROR_MESSAGE = "KList have negative head";
        KLDump(debElem);
        return false;
    }

    if (this->free_ptr < 0) {
        *this->error = KL_NEGATIVE_FREE_PTR;
        debElem.ERROR_MESSAGE = "KList have negative free_ptr pointer on data";
        KLDump(debElem);
        return false;
    }

    if (this->size >= this->buffer_size) {
        *this->error = KL_BUFFER_SIZE_LESS_THAN_SIZE;
        debElem.ERROR_MESSAGE = "buffer size less than size (real)";
        KLDump(debElem);
        return false;
    }

    if (this->buffer_size <= this->head) {
        *this->error = KL_BUFFER_SIZE_LESS_THAN_HEAD;
        debElem.ERROR_MESSAGE = "buffer size less than head";
        KLDump(debElem);
        return false;
    }

    return true;
}

template <typename KL_TYPE>
void KList<KL_TYPE>::print_buffer() {
    for (KL_SIZE_TYPE i = 0; i < this->buffer_size; i++) {
        printf("buffer[%d]: ", i);
        printf("%d  ->  ", this->buffer[i].lp);
        for (int pos_byte = 0; pos_byte < sizeof(KL_TYPE); pos_byte++) {
            printf("%02X",
                   *((char *)this->buffer + i * sizeof(KL_Data) + pos_byte));
        }
        printf("  ->  %d\n", this->buffer[i].rp);
    }
    printf("\n");
}


template <typename KL_TYPE>
void KList<KL_TYPE>::file_print_buffer(FILE* file) {
    for (KL_SIZE_TYPE i = 0; i < this->buffer_size; i++) {
        fprintf(file, "buffer[%d]: ", i);
        fprintf(file, "%d  ->  ", this->buffer[i].lp);
        for (int pos_byte = 0; pos_byte < sizeof(KL_TYPE); pos_byte++) {
            fprintf(file, "%02X",
                    *((char *)this->buffer + i * sizeof(KL_Data) + pos_byte));
        }
        fprintf(file,"  ->  %d\n", this->buffer[i].rp);
    }
    fprintf(file, "\n");
}



#endif //KLIST_KLIST_IMPL_H
