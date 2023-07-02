#include<stdio.h>

int main(){
	double x,y,max;
	double z;
	printf("enter the X: ");
	scanf("%lf",&x);
 	printf("enter the Y: ");
	scanf("%lf",&y);
	max = y;
	if(x>y){
		max = x;
	}
	z = (x/y) + max/(x+y);
	printf("your z value is : %lf \n",z);


}



