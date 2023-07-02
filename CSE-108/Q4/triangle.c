#include<stdio.h>

void main()
{
	int size = 5;

    for(int a = 1; a<=size; ++a)
    {
        for(int k =1; k<=(2*a -1); ++k)
        {
            if(a == 1 || a == size)
            {
                printf("* ");
            }
            else
            {
                if(k ==1 || k == size)
                {
                    printf("* ");
                }
                else
                    printf("  ");
            }
        }
        printf("\n");
    }
}
