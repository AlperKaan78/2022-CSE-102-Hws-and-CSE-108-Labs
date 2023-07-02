#include<stdio.h>
#include"util.h"
#include<string.h>

/* The copy function for strings.*/
void my_strcpy(char *dest, const char *src) 
{
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

int max_words_in_dict(char *file_path)
{
    FILE *dictFile;
    dictFile = fopen(file_path,"r");
    int max_word;

    fscanf(dictFile,"%*[^=]");
    getc(dictFile);
    fscanf(dictFile,"%d",&max_word);
    fclose(dictFile);

    return max_word;

}


/* This program finds the vector size. */
int get_vector_size(char *file_path)
{
    FILE *dict_file;
    dict_file = fopen(file_path,"r");
    if(dict_file == NULL)
    {
        printf("There is an error while opening the file.");
    }

    int size = 0;
    fscanf(dict_file,"%*[^=]");
    getc(dict_file);
    fscanf(dict_file,"%*d");
    getc(dict_file);
    getc(dict_file);
    fscanf(dict_file,"%*[^=]");
    getc(dict_file);
    fscanf(dict_file,"%d",&size);
    return size;

}

