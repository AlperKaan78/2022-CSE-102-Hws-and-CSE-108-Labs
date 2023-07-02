#include<stdio.h>

void main()
{
	char operation;

	/* I declare my variables as double since I want to do more efficient calculator.*/
	double firstNum,
		   secondNum,
		   result,
		   userResult;

	printf("Enter an arithmetic operation ( + , - , * , / ): ");
	scanf("%c",&operation);

	printf("Enter two numbers: ");
	scanf("%lf %lf",&firstNum,&secondNum);

	/* According to operation signs the result is calculated*/
	switch(operation)
	{
		case '+':
			result = firstNum+secondNum;
			break;
		case '-':
			result = firstNum - secondNum;
			break;
		case '*':
			result = (firstNum*secondNum);
			break;
		case '/':
			result = firstNum / secondNum;
			break;
		default:
			printf("Invalid Operation! \n");
			break;
	}

	/* I am getting from user the answer*/
	
	printf("Enter the result:");
	scanf("%lf",&userResult);
 	
	/* I am checking the conditions */
	
	if(userResult == result)
		printf("Bravo, correct answer!\n");
	else
		printf("Wrong answer, try again. \n");
}
