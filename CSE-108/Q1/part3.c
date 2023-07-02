#include<stdio.h>


int main(){
	int age, yearsOfExp,salary;
	printf("What is your age: ");
	scanf("%d",&age);
	printf("What is your years of experience: ");
	scanf("%d",&yearsOfExp);
	if((age-yearsOfExp)<0){
		printf("Invalid values\n");
		return(0);
	
	}
	if(age<20){
		if(yearsOfExp>10){
			printf("Error\n");	
			return(0);
		}
		else{
			salary = 10000;
		}
	}
	else if(age>=20 & age<=50){
		if(yearsOfExp>10){
			salary=20000;
		}
		else{
			salary = 15000;
		}
	}
	else if(age>50){
		if(yearsOfExp>10){
			salary=25000;
		}
		else{
			salary = 20000;
		}
	}
	printf("your salary is: %d\n",salary);
	return(0);




}
