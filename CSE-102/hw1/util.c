#include<stdio.h>
#include"util.h"

void part1(){
	printf("*******PART-1********\n\n");
	

	int bigNumber,smallNumber,stemp,number1, number2; // I determine my variable with type of int.
	
	printf("please enter number1: "); // I get the numbers from the user.
	scanf("%d",&number1);
	printf("please enter number2:");
	scanf("%d",&number2);

	if (number1>=number2) {   // The big number is determined here since the algorithm need to know which is the bigger.
		bigNumber = number1;
		smallNumber = number2;
	}
	else{
		bigNumber = number2;
		smallNumber = number1;
	}

	while(smallNumber != 0){  // My main process of Euclidian Algoritm for GCD is here. 
		stemp = bigNumber%smallNumber; // The remainder from the division is determined and giving value to stemp variable here for using the step after.
		bigNumber = smallNumber; // My new bigNumber is equal to smallNumber now. 
		smallNumber = stemp;
		
	}
	printf("gcd is : %d \n",bigNumber);

}
void part2(){
	int firstNumber, secondNumber, sum;
	
	printf("*******PART-2********\n\n");
	printf("First number: ");
	scanf("%d",&firstNumber);

	printf("Second number: ");
    scanf("%d",&secondNumber);

	sum = firstNumber + secondNumber;

	printf("Result:\n");
	printf("          %4d\n",firstNumber);
	printf("          %4d\n",secondNumber);

	printf("        +\n");
	printf("        ------\n");
	printf("         %5d\n",sum);



}

void part3(){
		printf("*******PART-3********\n\n");		
		int digitFirst,digitSecond,digitThird,
			bigNum,smallNum,firstNum,secondNum, 
			product1,product2,product3,sum;

        printf("First number: ");
		scanf("%d",&firstNum);

        printf("Second number: ");
        scanf("%d",&secondNum);

		//This if-else statement makes easier to multiply and to show the numbers on display.
		if(firstNum > secondNum){
			smallNum = secondNum;
			bigNum=firstNum;
		}
		else{
			smallNum = firstNum;
			bigNum= secondNum;
		}
		
		sum= smallNum*bigNum;
		printf("Result:\n");
		printf("          %3d\n",bigNum);
		printf("          %3d\n",smallNum);

		printf("        *\n");
		printf("        ------\n");
		

		//I found the digits and multiply with bigNum since I wanted the find all the products.
		digitFirst = smallNum%10; // Digits are found using the logic of digits in Math.
		smallNum = (smallNum - digitFirst)/10;
		digitSecond = smallNum%10;
		smallNum = (smallNum - digitSecond)/10;
 		digitThird = smallNum%10;
		smallNum = (smallNum - digitThird)/10;
	
		product1 = digitFirst*bigNum;
		product2 = digitSecond*bigNum;
		product3 = digitThird*bigNum;
			
  	    // I am checking the number of digits below and then the products are written.	
		if(product3 == 0 & product2 != 0){
			printf("         %4d\n",product1);
			printf("        %4d\n",product2);
			printf("       +\n");
			printf("       ------\n");
			printf("        %5d\n",sum); // I determine the place holders according to maximum digit size.(4 digits + 4 digits = maximum 5 digits)
		}
	    else if(product3 == 0 & product2 == 0){
			printf("         %4d\n",product1);

		}

		else if(product3 != 0){
			printf("          %4d\n",product1);
			printf("         %4d\n",product2);
			printf("        %4d\n",product3);
			printf("      +\n");
			printf("      --------\n");
			printf("        %6d\n",sum);
		}

}
void part4(){
	int number;

	printf("*******PART-4********\n\n");

	printf("Enter a number between 1-10(inclusive): ");
	scanf("%d",&number);

    /* I am checking the conditions.*/
	if (number>5 & number<=10 ) {
		printf("The integer you entered is greater than 5\n");
	}
	else if(number<=5 & number>=1){
		printf("The integer you entered is less than or equal to 5\n");
	}
	else{
		printf("Invalid input\n");
	}
}
