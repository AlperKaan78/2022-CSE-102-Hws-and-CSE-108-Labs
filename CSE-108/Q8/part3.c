#include<stdio.h>

typedef struct 
{
    double third,second,first,constant;

}third_order_polynomial;

typedef struct 
{
    double nineth,eight,seventh,sixth;
    char constant;
}polynomial;


polynomial get_integral(third_order_polynomial p1, third_order_polynomial p2, int a, int b);

int main()
{
    int upper1,upper2,lower1,lower2;

    third_order_polynomial polinom1,polinom2;

    printf("enter the third, second first and zeroth coefficients: ");
    scanf(" %lf %lf %lf %lf", polinom1.third, polinom1.second,polinom1.first,polinom1.constant);
    printf("Enter the upper and lower limits for polionom1: ");
    scanf(" %d %d",upper1,lower1);
    
    
    printf("enter the third, second first and zeroth coefficients: ");
    scanf(" %lf %lf %lf %lf", polinom1.third, polinom1.second,polinom1.first,polinom1.constant);
    printf("Enter the upper and lower limits for polinom2: ");
    scanf(" %d %d",upper2,lower2);

    polynomial get_integral(polinom1, polinom2,lower1,upper1);
    return 0;
}
polynomial get_integral(third_order_polynomial p1, third_order_polynomial p2, int a, int b)
{
     polynomial new; 
     new.nineth = p1.third * p2.third;
}