/* This func cleans input text from:
 * Repeating spaces
 * Repeating enters
 * Incomprehensible symbols
 * Tabs change of spaces
 * */


#include <iostream>
#include <sys/stat.h>

struct mybuff {
    char* buff;
    long size;
};


void cleaning_file_and_record(const char*, const char*);
struct mybuff clean(const char*, const long);

int main() {
    const char *_name_input_file_ =  "/home/arlik_null/Документы/GitHub/DEAD_PROJECTS/untitled1/Onegin.txt";
    const char *_name_output_file = "/home/arlik_null/Документы/GitHub/DEAD_PROJECTS/untitled1/New_Onegin.txt";

    cleaning_file_and_record(_name_input_file_, _name_output_file);

    return 0;
}

void cleaning_file_and_record(const char *_name_input_file_, const char *_name_output_file) {
    FILE* input_file = fopen(_name_input_file_, "r");
    FILE* output_file = fopen(_name_output_file, "w");
    struct stat stat_file = {};
    char* buff = nullptr;
    struct mybuff new_buff = {};
    int real_size = 0;

    stat(_name_input_file_, &stat_file);
    buff = (char *)calloc (stat_file.st_size/sizeof(char), sizeof(char));
    fread(buff, sizeof(char), stat_file.st_size, input_file);

    new_buff = clean(buff, stat_file.st_size/sizeof(char));

    fwrite(new_buff.buff, sizeof(char), new_buff.size, output_file);
//    fprintf(output_file, "%s", new_buff);

    free(buff);
    free(new_buff.buff);
}

struct mybuff clean(const char* buff, const long buff_size) {
    char* new_buff = (char*)calloc(buff_size, sizeof(char));
    char Repeating_spaces     = false;
    char Repeating_enters     = false;
    long number_elem_new_buff = 0;    // number elem in new buff

    for(int i = 0; buff[i] != '\0'; i++) {

        if (buff[i] == '\n' || buff[i] == '\r') {
            Repeating_spaces = true;
            if (Repeating_enters) continue;
            Repeating_enters = true;
            new_buff[number_elem_new_buff++] = '\n';
            continue;
        }
        else Repeating_enters = false;

        if (buff[i] == ' ' ||
            buff[i] == '\t' ||
            !(33 <= buff[i] && buff[i] <= 126)) {

            if (Repeating_spaces) continue;
            Repeating_spaces = true;
            new_buff[number_elem_new_buff++] = ' ';
            continue;
        }
        else Repeating_spaces = false;

        if (0 <= buff[i] && buff[i] <= 127) {
             new_buff[number_elem_new_buff++] = buff[i];
        }
        else {
            Repeating_spaces = true;
            new_buff[number_elem_new_buff++] = ' ';
        }
    }

//    new_buff[number_elem_new_buff++] = '\0';
    new_buff = (char*) realloc(new_buff, (number_elem_new_buff) * sizeof(char));

    return {new_buff, number_elem_new_buff};
}


