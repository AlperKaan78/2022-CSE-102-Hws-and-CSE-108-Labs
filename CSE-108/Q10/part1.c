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
    int size,min,k;
    int* int_arr;

    printf("Enter the size of the array:");
    scanf("%d", &size);
    int_arr = part1(size);

    for(k = 0; k<size; k++)
    {
        if(k==0) min = int_arr[k];

        else{
            if(int_arr[k]<min) min = int_arr[k];
        }
        
    }
    printf("The minimum value of the array is: %d\n",min);
    
    free(int_arr); 

    return 0;
}
