#include <stdio.h>
#include "util.h"
#include <string.h>
#include <stdlib.h>

int main()
{
    char file_name[] = "dictionary.txt";
    char text_file[] = "input.txt";
    char ignore_file[] = "ignore.txt";

    /* If user wants to enter different file paths then they are received.*/
    char answer;
    printf("Do you want to enter different file paths? (Y or N):");
    scanf(" %c",&answer);
    if(answer == 'y' || answer =='Y')
    {
        printf("Enter the file path for dictionary file: ");
        scanf("%s",file_name);
        printf("Enter the file path for input file: ");
        scanf("%s",text_file);
        printf("Enter the file path for ignore file: ");
        scanf("%s",ignore_file);
    }
    char user_words[MAX_WORD_COUNT][MAX_WORD_SIZE];
    
    char dict[MAX_WORD_DICT][MAX_WORD_SIZE];
    char words[TEXT_WORDS][MAX_SIZE_WORD_TEXT];
    int occurences[MAX_WORD_COUNT] ={0}; // Occurences will be stored in this array.It is initialized with 0's. 
    char hist[MAX_WORD_COUNT][MAX_WORD_SIZE+5+20];

    FILE *dict_file;
    dict_file = fopen(file_name,"r");

    if(dict_file == NULL)
    {
        printf("There is an error while opening dictionary file!\n");
        return 0;
    }
    int VECTOR_SIZE =get_vector_size(file_name);
    /* I am getting word(s) from the user. */


    int index_of_word = 0;
    char ch = '\0'; // Initialize ch to avoid undefined behavior.
   
    printf("Enter word(s): "); 
    while (ch != '\n' && index_of_word < MAX_WORD_COUNT)
    {
        scanf("%s", user_words[index_of_word]);
        index_of_word++;
        ch = getchar();  // When user presses enter, the while loop will exit. 
    }
    user_words[index_of_word+1][0] = '-';
    // printf("%d",index_of_word);

    int num_dict = read_dict(file_name, dict);

    int num_words = read_text(text_file, ignore_file,  words);


    /* There are some operations that find the occurences of the words or closest words. */
    // printf("%d\n",num_words);


    int user_words_counter = 0;
    int text_words_counter;

    char main_word[MAX_WORD_SIZE];
    char closest_word[MAX_WORD_SIZE];

    /* The vectors are declared as a pointer and arranged their sizes using malloc. */
    double *main_vec,*closest_vec;
    main_vec =(double*)malloc(VECTOR_SIZE*sizeof(double));
    closest_vec =(double*)malloc(VECTOR_SIZE*sizeof(double));

    float threshold = 7;

    while(user_words_counter < index_of_word)
    {
        /* The words are checked till the last index equals '-' character. */
        text_words_counter = 0;
        while(words[text_words_counter][0] != '-')
        {
            if(!strcmp(user_words[user_words_counter], words[text_words_counter]))
            {
                occurences[user_words_counter]++;
            }
            text_words_counter++;
        }
        int flag = 0;
        if(occurences[user_words_counter] == 0)
        {
            
            for(int k=0; k<num_dict; k++)
            {
                if(strcmp(dict[k],user_words[user_words_counter]) == 0)
                {
                    flag = 1;
                    break;
                }
            }
            char dict_buffer[MAX_WORD_SIZE], a= '\0';
            /* If the word not in the input file but in the dictionary file then these operations are made*/
            if(flag)
            {
                dissimilarity(user_words[user_words_counter],closest_word,dict,threshold,file_name);
                text_words_counter = 0;
                while(words[text_words_counter][0] != '-')
                {
                    if(!strcmp(closest_word, words[text_words_counter]))
                    {
                        occurences[user_words_counter]++;
                    }
                    text_words_counter++;
                }
                strcat(hist[user_words_counter],user_words[user_words_counter]);
                strcat(hist[user_words_counter],"->");
                strcat(hist[user_words_counter],closest_word);
            }
            /* If the word is not in the dictionary file then just word is copied to the hist array.*/
            else{
                strcat(hist[user_words_counter],user_words[user_words_counter]);
            }
            
        }
        else{
            strcat(hist[user_words_counter],user_words[user_words_counter]);
        }
        user_words_counter++;
    }
    hist[user_words_counter+1][0] = '-';

    histogram(user_words,occurences,hist);

    free(main_vec);
    free(closest_vec);

    return 0;
    

   
}
