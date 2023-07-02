#include<stdio.h>

int main()
{
	/* I declare my variables as an integer*/
	int first,
		second,
		third,
		median;
	
	/* I wanted user to give 3 integers*/
	printf("Enter 3 integers: ");
	scanf("%d %d %d",&first,&second,&third);
	
	/* I made nested if conditions below. Each statements include several condition according to possible circumstances.*/
	if(first>second)
	{
		if(second>third)
			median = second;
		else if(third > first)
			median = second;
		else if(third > second)
			median = third;
		else
			median = third; 

	}
	else if(first < second)
	{
		if(first > third)
			median = first;
		else if(third > second)
			median = second;
		else if(third > first)
			median = third;
		else
			median = third;
	}

	/* else statement is for equality between first and second */
	else
		median = second; /* It can be second */

	printf("Median number is : %d \n",median);
}
