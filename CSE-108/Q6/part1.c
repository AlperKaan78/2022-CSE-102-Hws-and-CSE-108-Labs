#include<stdio.h>

void printResults(int integerList[], int);
void read(int integerList[], int *counter);
void main()
{
    int integerList[100] = {0};
    int counter = 0;

    read(integerList,&counter);
    printResults(integerList,counter);
}
void read(int integerList[],int *counter)
{
    int myNumber = 0;

    while(myNumber >=0)
    {
        scanf("%d",&myNumber);
        if(myNumber>= 0)
        {
            integerList[*counter] = myNumber;
            (*counter)++;
        } 
    }
}
void printResults(int integerList[], int counter)
{
    for (int i= 0; i<counter; i++)
    {
        if(integerList[i]%2 == 0)
        {
            printf("%d e\n",integerList[i]);
        }
        else
            printf("%d o\n",integerList[i]);
    }
}

