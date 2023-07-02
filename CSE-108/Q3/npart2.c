#include<stdio.h>


char calcGrade(int);

void main()
{
	int exam1,
		exam2,
		exam3;
	printf("%s",calcGrade(70));
}

char calcGrade(int exam)
{
	return "A+";
}
