#include<stdio.h>



int f(int a)
{
    if(a<=1)
    {
        return 1;
    }
    return a* f(a-1);

}

int main()
{
    printf("%d",f(0));
    return 0;
}