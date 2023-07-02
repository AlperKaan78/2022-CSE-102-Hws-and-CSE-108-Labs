#include<stdio.h>   

void temperatureConversion();
void reverseInteger();
int digitCount(int number);
void convertNumber();


void decimalToBinary(int);
void decimalToOctal(int);
void decimalToHexa(int);

void main()
{
    temperatureConversion();
    reverseInteger();
    convertNumber();
}

void temperatureConversion()
{
    int selection;
    double value;
    double converted;
    while(selection != 3)
    {
        printf("------ Temperature Conversion Menu ------  \n");
        printf("1-Convert celcius to fahrenheit\n");
        printf("1-Convert fahrenheit to celcius\n");
        printf("3-Quit\n");
        printf("Enter your choice:");
        scanf(" %d",&selection);

        switch (selection)
        {
        case 1:
            printf("Enter the tempereture value to convert:");
            scanf(" %lf",&value);
            converted = (value *9/5) +32;
            printf("%.2lf Celcius = %.2lf Fahrenheit. \n",value,converted);
            break;
        case 2:
            printf("Enter the tempereture value to convert:");
            scanf(" %lf",&value);
            converted = (value -32) * 5/9;
            printf("%.2lf Fahrenheit = %.2lf Celcius.\n ",value,converted);
            break;
        case 3:
            printf("Quitting...\n");
            break;
        default:
            printf("Your choice is unvalid\n");
            break;
        }  
    }  
}

void reverseInteger()
{
    int number;
    int reversed = 0;   

    printf("enter a number (3,4 or 5 digits):");
    scanf("%d",&number);
    digitCount(number);
    if(digitCount(number)>5 || digitCount(number)<3)
    {
        printf("unvalid number.\n");
    }
    else
    {
        
        while (number > 0) {
            reversed = reversed * 10 + number % 10;
            number /= 10;
        }
    }
    printf("reversed: %d \n",reversed);
}


int digitCount(int number)
{
    int digit;
    int counter = 0;
    while(number >0)
    {
        counter++;
        digit = number%10;
        number -= digit;
        number /= 10;
    }
    return counter;
}
void convertNumber()
{
    int decimalNum;
    int selection = 0;
    while(selection != 2)
    {
        int number;
        
        printf("1- Convert a number to decimal, binary, octal and hexadecimal. \n");
        printf("2- Quit. \n");
        scanf("%d",&selection);
        switch (selection)
        {
        case 1:
            printf("Enter a decimal Number:");
            scanf("%d",&decimalNum);
            decimalToBinary(decimalNum);
            decimalToOctal(decimalNum);
            decimalToHexa(decimalNum);
            break;
        
        default:
            break;
        }
    }
}

void decimalToBinary(int number)
{
    int size = digitCount(number);
    int result[size];

    while(size>0)
    {
        result[size-1] = number%2;
        number /= 10;
        size--;
    }
    printf("%ls",result);
}

void decimalToOctal(int decimalNum)
{
}

void decimalToHexa(int decimalNum){
}
