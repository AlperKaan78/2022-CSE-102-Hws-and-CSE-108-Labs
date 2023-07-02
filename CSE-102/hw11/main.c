#include<stdio.h>
#include<stdlib.h>
#include "util.h"

int main()
{
    char selection;
    while(selection != '4')
    {
        printf("Family Tree System Menu:\n1 -Add Family Tree\n2-Remove Family Tree\n3-Load Family Tree.\n4-Exit.\n");
        scanf(" %c",&selection);
    
        switch (selection)
        {
        case '1':break;
        case '2':break;
        case '3':break;
        case '4':break;
        default:printf("Invalid Selection.\n");break;
        }
    }
}

