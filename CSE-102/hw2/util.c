#include<stdio.h>
#include"util.h"


void part1()
{
	printf("***********|PART-1|***********\n\n");

	int year;

	printf("Please enter a year:");
	scanf("%d",&year);

    /* I am checking whether the year is leap year or not. */
	/* Leap year rule: The number must be divisible by 4 and the number can not be
	 * divisible by just 100 from between the two number that are 100 and 400. It can be just divisible by 400. */
			
	if((year%4) == 0)
		if((year%400) == 0 )
			printf("%d is a leap year.\n",year);
		else if ((year%100) == 0)
			printf("%d is not a leap year. \n",year);
		else
			printf("%d is a leap year\n",year);
	else	
		printf("%d is not a leap year. \n",year);
}

void part2()
{
	printf("*************|Part-2|*************\n\n");

	char operation,
		 formatOfOut;

	int m=0, /* Total digit */
		n=0; /* The number of digits after decimal point*/

	double firstOp,
	   	   secondOp,
		   result;

	printf("Enter the format of output(S or I): ");
	scanf(" %c",&formatOfOut);
	
	/* I am checking the format of output. If it is s or S then I want user to give m and n values. */
	/* n value must be greater than the m value. Therefore I am using while loop. */
	
	if(formatOfOut == 's' || formatOfOut == 'S' ){
		while (n>=m){
			printf("Please enter m and n: (m must be greater than n) ");
			scanf("%d %d",&m,&n);
		}

}
	printf("Enter the operation---> ( +,-,/,*,%%,^,! ) "); /* The % operation must be written like this --> %% */
	scanf(" %c",&operation); /* I have to use space character at the beginning because of input buffer.*/

    /* Operation is checked below and operands or operand is asked from the user  */
	if(operation == '+' || operation == '-' || operation == '/' || operation == '*' || operation == '%' || operation == '^')
	{
		printf("Enter a first operand: ");
		scanf("%lf",&firstOp);
		printf("Enter a second operand: ");
		scanf("%lf",&secondOp);
	}
	/* ! character needs to one operand so I seperated it.*/
	else if(operation =='!')
	{
		printf("Enter the operand: ");
		scanf("%lf",&firstOp);
	}
	else
		printf("Invalid operation.\n");
	
	/* I find the result according to the operation.*/
	/* I use my own power and factorial function.*/

	switch(operation)
	{
		
		case '+':
			result = firstOp+secondOp;
			break;
		case '-':
			result = firstOp - secondOp;
			break;
		case '/':
			result = firstOp / secondOp;
			break;
		case '*':
			result = firstOp * secondOp;
			break;
		case '%':
			result =(int)firstOp % (int)secondOp;
			break;
		case '^':
			result = powerFunc(firstOp,secondOp);
			break;
		case '!':
			result = factorialFunc(firstOp);
			break;
		default:
			break;
	}
	
	/* The format of output is checked below and the result is printed according to format of output.
	 * But I considered the '!' character has one operand and I seperated it from the others.
	 * The %.* place holder allows me to print result according to n value.
	 * and I print 0 at the beginning of the result because of to complete digits for m value */

	if(formatOfOut == 'S' || formatOfOut == 's')
	{
		if(operation == '!')
		{
			printf("%.3lf %c = ",firstOp,operation);
			for(int i =1; i<(m-n); i++)
			{
				printf("0");
			}
			printf("%.*e\n",n,result);
		}

		else 
		{
			printf("%.3lf %c %.3lf = ",firstOp,operation,secondOp);
			for(int i =1; i<(m-n); i++)
			{
				printf("0");
			}
			printf("%.*e\n",n,result);
		}

	
	}
	/* If do user select integer format the result will be printed integer format.
	 * Since the values are double type the place holders should be like this: "%.0lf"*/
	else if(formatOfOut == 'I' || formatOfOut == 'i')
	{
		if(operation == '!')
			printf("%.0lf %c = %.0lf\n",firstOp,operation,result);
		else
			printf("%.0lf %c %.0lf = %.0lf\n",firstOp,operation,secondOp,result);
	}
	
}
void part3()
{
	printf("**********|Part-3|**********\n\n");
	/* The exams and assignments are integer type because they are integer in the assignment pdf too.*/
	int exam1,
		exam2,
		exam3,
		assignment1,
		assignment2;
	/* The final grade can be floating point number. Since I define as a double. */
	double finalGrade;

	printf("Enter 3 exam grades of student: ");
	scanf("%d %d %d",&exam1,&exam2,&exam3);

	printf("Enter 2 assignment grades of student: ");
	scanf("%d %d",&assignment1,&assignment2);

	finalGrade = (exam1+exam2+exam3)/5 + (assignment1+assignment2)/5;
	if(finalGrade<0 || finalGrade>100)
		printf("You have entered wrong numbers");
	else if(finalGrade>=60)
		printf("Final Grade: %4.1f Passed\n",finalGrade);
	else
		printf("Final Grade: %4.1f Failed!\n",finalGrade);
}

/* I generate these functions for power and factorial arithmetic operations in part2.*/

int powerFunc(int firstOp, int secondOp)
{
	int k,
		result = 1;

	for(k =1; k<=secondOp; k++)
	{
		result *= firstOp;
	}
	return result;
}

int factorialFunc(int firstOp)
{
	int k,
		result = 1;

	for(k=1; k<=firstOp; k++)
	{
		result *= k;
	}
	return result;
}

