#include<stdio.h>
#include<math.h>
#define PI 3.14 /* PI was defined as a constant value here*/
/* Alper Kaan Güler 210104004040*/

int main(){
	
	/* I used general named variables in my function.*/
	/* I use math.h library, so I have to add -lm for compiling step. */
	/* Each step has own calculation formulas*/


	int radiusOfSmth,
		lengthOfSmth,
		width,
		height;
	double volume,
		   area,
		   lengthOfCone;

	printf("Enter the edge length for cube:");
	scanf("%d",&lengthOfSmth);
	volume = (lengthOfSmth*lengthOfSmth*lengthOfSmth);
	area = (lengthOfSmth*lengthOfSmth)*6;
	printf("The surface area: %6.2f , Volume: %6.2f\n",area,volume); /* I arranged space holders for proper output.*/
	
	printf("Enter side length for rectangular prism:");
	scanf("%d",&lengthOfSmth);
	printf("Enter side widht:");
	scanf("%d",&width);
	printf("Enter side length:");
	scanf("%d",&height);
	area = (lengthOfSmth*width + lengthOfSmth*height + width*height)*2;
	volume = (lengthOfSmth*height*width);
	printf("The surface area: %6.2f , Volume: %6.2f\n",area,volume);


	printf("Enter the radius for sphere:");
	scanf("%d",&radiusOfSmth);
	volume = (4*PI*radiusOfSmth*radiusOfSmth*radiusOfSmth)/3; 
	area = (radiusOfSmth*radiusOfSmth)*4*PI;
	printf("The surface area: %6.2f , Volume: %6.2f\n",area,volume);
	
	printf("Enter the radius for cone:");
	scanf("%d",&radiusOfSmth);
	printf("Enter the height:");
	scanf("%d",&height);
	lengthOfCone = sqrt((radiusOfSmth*radiusOfSmth) + (height*height)); /* I used sqrt function here*/
	volume = (PI*radiusOfSmth*radiusOfSmth*height)/3;
	area = (radiusOfSmth + lengthOfCone)*radiusOfSmth*PI;
	printf("The surface area: %6.2f , Volume: %6.2f\n",area,volume);


	return 0;
}

		   
