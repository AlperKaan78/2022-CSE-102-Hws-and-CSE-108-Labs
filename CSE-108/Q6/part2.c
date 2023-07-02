#include<stdio.h>


void main()
{
    FILE *infile;

    int sizeOfArrays;
    int counter = 0;
    char selection;
    float avrgSalary;

    infile = fopen("file.txt","r");

    fscanf(infile,"%d",&sizeOfArrays); // Firstly I am getting line of inputs for determining the size of arrays.

    int ages[sizeOfArrays];
    char occupation[sizeOfArrays];
    float salary[sizeOfArrays];
    char favTeam[sizeOfArrays];

    /*The program getting inputs from txt file till end of file.*/
    while (!feof(infile))
    {
        fscanf(infile,"%d %c %f %c",&ages[counter],&occupation[counter],&salary[counter],&favTeam[counter]);
        counter++;
    }
    
    
    /* The program is running till user enter a q for quit operation.*/
    while(selection != 'q')
    {
        /* In start of each loop my variables equal zero.*/
        counter =0;
        avrgSalary =0;

        printf("\nPlease select a team: ");
        scanf(" %c",&selection);
        for (int i = 0; i<sizeOfArrays; i++)
        {
            if(favTeam[i] == selection)
            {
                counter ++;
                avrgSalary += salary[i];
            }

        }
        if(counter == 0)
            printf("\nThere are no fans of %c in the database! ",selection);
        else
        {
            printf("\nAverage salaries of fans of %c: %.2f",selection,avrgSalary/counter);
        }

    }
    
}