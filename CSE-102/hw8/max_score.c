#include<stdio.h>
#include<stdlib.h>
#include "util.h"

void show_best_score(char *best_score_file)
{
    FILE *score_file;
    score_file = fopen(best_score_file,"r");

    int best;

    fscanf(score_file,"%d",&best);
    printf("The best score is: %d\n\n",best);
    fclose(score_file);
}