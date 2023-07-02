#include<stdio.h>

int main(){
	int number;
	printf("please enter a number between 1-100: ");
	scanf("%d",&number);
	if(number>=100 || number<=1){
		printf("Invalid input\n");
		return(0);
	}
	else if(number%3 == 0 & number>5 & number<50){
		printf("FizzBuzz\n");
	}
	else if(number>5 & number<50){
		printf("Buzz\n");
	}
	else if(number%3 == 0){
		printf("Fizz\n");
	}
	return(0);
}
