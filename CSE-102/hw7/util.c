#include<stdio.h>
#include"util.h"
#include<string.h>
#include<math.h>

int read_dict(const char * file_name, char dict[][MAX_WORD_SIZE])
{
    FILE *dict_file;
    dict_file = fopen(file_name,"r");
    
    
    if(dict_file == NULL)
    {
        printf("There is an error while opening the file!\n");
        return -1;
    }
    char buffer[100];
    /*The first line must be skipped. So I write this code.*/
    if (fgets(buffer, sizeof(buffer), dict_file) == NULL) {
        printf("Error handling the first line");
    }

    int num_of_words = 0;
    char a = '\0';  // initialize a to the first character in the file
    
    while ((fscanf(dict_file, "%s", dict[num_of_words]) == 1) && a != EOF) {
        num_of_words++;
        while ((a = fgetc(dict_file)) != '\n' && a != EOF){}
    // add this check to avoid reading beyond the end of the file
        if (feof(dict_file)) {
            break;
        }
    }

    dict[num_of_words][0] = '-';
    fclose(dict_file);
    return num_of_words;
}

int read_text(const char *text_file, const char *ignore_file, char words[][MAX_SIZE_WORD_TEXT]) {
    FILE *textFile;
    FILE *ignoreFile;

    int num_of_words = 0;
    
    textFile = fopen(text_file, "r");
    ignoreFile = fopen("ignore.txt","r");
    
    
    if (textFile == NULL) {
        printf("There is an error while opening the file!\n");
        return -1;
    }

    char ch = '\0';
    int ignore_counter = 0;
    char ignore_words[MAX_WORD_COUNT][13];

    while (fscanf(ignoreFile, "%12[A-Za-z0-9'-]", ignore_words[ignore_counter]) == 1 && ch != EOF) {
        // Skip to the next word
        fscanf(ignoreFile, "%*[^\n]");
        ch = fgetc(ignoreFile);
        ignore_counter++;
    }

    char a = '\0'; 
    char buffer[20];
    int counter,isFound;

    while ((fscanf(textFile, "%[A-Za-z0-9'-]", buffer) == 1) && a != EOF) {
        counter = 0;
        isFound = 1;
        while(counter<=ignore_counter)
        {
            /* If buffer word is in the ignore file then program skip that word.*/
            if(strcmp(ignore_words[counter],buffer))
            {
                isFound = 0;
                break;
            }
            counter++;
        }
        if(!isFound)
        {    
            my_strcpy(words[num_of_words],buffer);
            num_of_words++; 
        }
        fscanf(textFile, "%*[^A-Za-z0-9'-]");
        
    }
    /* The first index of the last word must be '-' as it is wanted.*/
    words[num_of_words][0] = '-';

    fclose(textFile);
    fclose(ignoreFile);

    return num_of_words;
}

/*In this function w1 represents the given word and w2 represents output word.*/
double dissimilarity(char * w1, char * w2, char dict[][MAX_WORD_SIZE], float threshold, char *file_path)
{
    FILE *dict_file;

    dict_file = fopen(file_path,"r");


    char main_word[MAX_WORD_SIZE];
    char closest_word[MAX_WORD_SIZE];

    double main_vec[200],closest_vec[200];
    char b ='\0';

    char dict_buffer[MAX_WORD_SIZE], a= '\0';

    float sum = 0,result = 100;

    int index_of_main;

    //The first line of the dict_file is passed using while loop.
    while(b=getc(dict_file) != '\n'){}
    getc(dict_file);

    /*Firstly the program try to read the main word's vector.*/
    while ((fscanf(dict_file, "%s", dict_buffer) == 1) && !feof(dict_file)) { 
        
        if(strcmp(dict_buffer,w1) == 0){
            index_of_main = 0;
            while (fscanf(dict_file, "%lf",&main_vec[index_of_main++]) == 1){}
        }
    }
    /*The cursor is moved at the beginning of the file.*/
    fseek(dict_file,0,SEEK_SET);

    //Again the first line of the dict_file is passed using while loop.
    b= '\0';
    while(b=getc(dict_file) != '\n'){}
    getc(dict_file);
    int index_of_closest;

    /* Here, program reads the words and vectors.Then calculates distance between main word and candidate of closest words.
        As a result program calculates the closest word and returns the closest distance and closest word as a function argument. */
    while((fscanf(dict_file, "%s", dict_buffer) == 1) && !feof(dict_file))
    {
        sum = 0;
        index_of_closest = 0;
        while (fscanf(dict_file, "%lf",&closest_vec[index_of_closest++]) == 1){}
        for(int l=0; l<200; l++)
        {
            sum += (main_vec[l]-closest_vec[l])*(main_vec[l]-closest_vec[l]);
            
        }
        sum = sqrt(sum);
        if(result>sum && sum!=0.0)
        {
            result = sum;
            my_strcpy(w2,dict_buffer);
        }
        
    }
    
    return result;

}
/* Mainly histogram function gets the words that user's enters, occurences that are calculated the main function
     and hist array that includes "word" or "word->closest". Function creates a histogram using given parameters.*/
int histogram(const char words[][MAX_WORD_SIZE], const int occurrences[], const char hist[][MAX_HIST_SIZE]) {
    int scale = 0, max = 0, i;
    int wordCount = 0;

    // Find the maximum occurrence to find scale.
    for (i = 0; hist[i][0] != '-'; i++) {
        if (occurrences[i] > max) {
            max = occurrences[i];
        }
        wordCount++;
    }

    scale = max / 20 + 1; // Adjusted scale for wanted output. 20 can be changed.
    
    /* If value of scale is not 1 then it will be printed*/
    if(scale != 1 && i!=2)
    {
        printf("SCALE: %d\n",scale);
    }

    for (int k = 0; k < wordCount-1; k++) {

        /* If the number of entered word is one then different messages will be shown to the user. */
        if(wordCount-1 == 1)
        {
            if(occurrences[k] != 0)
                printf("\"%s\" appears %d times in the \"input.txt\" \n",hist[k],occurrences[k]);
            else
                printf("\"%s\" does not appear in the \"input.txt\" \n",hist[k]);
        }
        /* While creating a histogram firstly: print the word and if the closest word have been used (find result checking '>') 
            then different symbol('+') is used for printing the histogrambut if actual word have been used then '*' symbol is used to print the histogram.*/

        else{
            int c = 0,closest_flag = 0;
            printf("%-*s", MAX_HIST_SIZE, hist[k]);
            /* If the closest word is searched '+' will be printed if not '*' is printed when histogram is creating.*/
            while(hist[k][c] != '\0')
            {
                if(hist[k][c] =='>')
                    closest_flag = 1;
                c++;
            }
            if (occurrences[k] == 0) {
                printf("NO MATCHES\n");
            } else {
                if(closest_flag)
                {
                    int numStars = occurrences[k] / scale;
                    for (int m = 0; m < numStars; m++) {
                        printf("+");
                    }
                    printf("\n"); 
                }
                else
                {
                    int numStars = occurrences[k] / scale;
                    for (int m = 0; m < numStars; m++) {
                        printf("*");
                    }
                    printf("\n");
                }
            }
        }
    }
}
