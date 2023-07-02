#include<stdio.h>


int main(){
	double height,  //Variables are all double type since user may enter double type values. 
		   weight,
		   BMI;

	printf("Enter your height(m): ");
	scanf("%lf",&height);
	printf("Enter your weight(kg): ");
	scanf("%lf",&weight);
	BMI = weight/(height*height);
	/* I checked the conditions below*/
	if(BMI>=30)
		printf("BMI is: %5.2f , You are : Obese\n",BMI); // Space holders arranged properly.
	else if(BMI>=25)
		printf("BMI is: %5.2f , You are : Overweight\n",BMI);
	else if(BMI>= 18.5)
		printf("BMI is: %5.2f , You are : Avarage weight\n",BMI);
	else 
		printf("BMI is: %5.2f , You are : Underweight\n",BMI);
	
}
