#include <stdio.h>
#include <stdlib.h>

int* part1(int size) {
    int* int_arr = (int*)malloc(sizeof(int) * size);

    int i = 0;
    printf("Enter the elements of the array:");
    while (i < size) {
        scanf("%d", &int_arr[i++]);
    }

    return int_arr;
}

int main() {
    int size;
    int* int_arr;
    int* cumi_sum;

    printf("Enter the size of the array:");
    scanf("%d", &size);

    int_arr = part1(size);

    cumi_sum = (int*)calloc(sizeof(int), size);

    for(int i= 0; i<size; i++)
    {
        for(int m=0; m<=i; m++)
        {
            cumi_sum[i] += int_arr[m]; 
        }
    }
    
    printf("First Array:");
    for(int l= 0; l<size; l++)
    {
        printf("%d ",int_arr[l]);
    }
    printf("\n");

    printf("Second Array(cumulative sum):");
    
    for(int l= 0; l<size; l++)
    {
        printf("%d ",cumi_sum[l]);
    }
    printf("\n");

    free(int_arr); 
    free(cumi_sum);

    return 0;
}