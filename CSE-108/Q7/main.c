#include<stdio.h>
#include<string.h>

void part1();
void part2();
void part3();
void foo_min_max(int arr[], int n);

int main()
{
    part1();
    part3();
}

void part1(){

    char str[100];
    printf("Give a string: ");
    scanf("%s",str);
    
    int len = strlen(str);
    int count = 1;
    char curr = str[0];

    for (int i = 1; i < len; i++) {
        if (str[i] != curr) {
            count++;
            curr = str[i];
        }
    }
    
    if (str[len-1] == curr) {
        count--;
    }
    
    printf("minimum number: %d\n",count);



}




void part3()
{
    int INT_NUM;
    printf("how many integer will you enter:");
    scanf("%d",&INT_NUM);

    int arr[INT_NUM+1];
    int counter = 0;
    while(counter<INT_NUM)
    {
        printf("Enter %d integers for comparison:", INT_NUM);
        scanf("%d",&arr[counter]);
        counter++;
    }
    foo_min_max(arr,INT_NUM);


}

/* I take the max number to the end of the array min number to the 0 index of array.*/
void foo_min_max(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        if(i != n-1)
        {
            if(arr[i]>arr[i+1] && arr[i]>arr[n-1] )
            {
               arr[n-1] = arr[i]; 
            }
            if(arr[i]<= arr[i+1] && arr[i]<arr[0])
            {
                arr[0] = arr[i];
            }
        }
    }
    printf("max: %d , min: %d \n",arr[n-1],arr[0]);
}

// void part2()
// {
//     int isSequenceProblem,isCharProblem;
//     char myStr[100];
//     char newStr[100];
//     char rule[20];
//     int flag = 1;

//     printf("Give a string: ");
//     scanf("%s",myStr);

//     printf("%s",myStr);
//     printf("Give a rule: ");
//     scanf(" %s",rule);

    
//     int i = 0;
//     while(rule[i] != '\0')
//     {
//         if(rule[i] == '*')
//         {
//             isSequenceProblem = 1;
//         }
//         else if(rule[i] == '?')
//         {
//             isCharProblem = 1;
//         }
//     }
//     i=0;
//     if(isCharProblem)
//     {
//         while(myStr[i] != '\0')
//         {
//             char anyStr[20];
//             sscanf(myStr,"%s",anyStr); 
//             int k= 0;
//             while(anyStr[k] != '\0')
//             {
//                 int j= 0;
//                 while(rule[j] != '\0')
//                 {
//                     if(rule[j] == anyStr[k])
//                     {
//                         flag = 0;
//                         break;
//                     }
//                 }
//                 if(flag)
//                 {
//                     strcat(newStr,anyStr);
//                 }
//                 flag = 1;
//             }   
//         }
//     }
//     if(isSequenceProblem)
//     {
//         while(myStr[i] != '\0')
//         {
//             char anyStr[20];
//             sscanf(myStr,"%s",anyStr); 
//             int k= 0;
//             while(anyStr[k] != '\0')
//             {
//                 int j= 0;
//                 while(rule[j] != '\0')
//                 {
//                     if(rule[j] == anyStr[k])
//                     {
//                         while(rule[j] != '?')
//                         {

//                         }
//                         break;
//                     }
//                 }
//                 if(flag)
//                 {
//                     strcat(newStr,anyStr);
//                 }
//                 flag = 1;
//             }   
//         }
//     }
//     printf("%s",newStr);
    
// }