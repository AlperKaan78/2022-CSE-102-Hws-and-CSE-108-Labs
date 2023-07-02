#ifndef _UTIL_H_
#define _UTIL_H_


#define MAX_WORD_COUNT 100
#define MAX_WORD_SIZE 13
#define MAX_SIZE_WORD_TEXT 40
#define TEXT_WORDS 150000
#define MAX_WORD_DICT 1002
#define MAX_HIST_SIZE (MAX_WORD_SIZE+25)


int read_dict(const char * file_name, char dict[][MAX_WORD_SIZE]);
int read_text(const char * text_file, const char * ignore_file, char words[][MAX_SIZE_WORD_TEXT]);
double dissimilarity(char * w1, char * w2, char dict[][MAX_WORD_SIZE], float threshold, char *file_path);
int histogram(const char words[][MAX_WORD_SIZE], const int occurrences[], const char hist[][MAX_WORD_SIZE+5+20]);

void my_strcpy(char *dest, const char *src);
int max_words_in_dict(char *file_path);
int get_vector_size(char *file_path);
#endif
