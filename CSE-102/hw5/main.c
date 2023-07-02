#include<stdio.h>
#include<math.h>
#include<stdlib.h>

/* The max and min numbers of upper and lower cases in ASCII is defined below as a constant variable.*/
#define UPPER_MAX 90
#define UPPER_MIN 65
#define LOWER_MAX 122
#define LOWER_MIN 97

/* The color type is defined below.*/
typedef enum {RED,GREEN,BLUE,YELLOW,ORANGE}color;

void freqOfLetters();
void mixTheColors();
void ticTacToe();
float calculateDistance(float mixedArr[] ,float colorArr[]);
void colorMixer(color first, color second, color(*mix)(color,color));
color mix(color, color);


int main()
{
	/*I am sending file.txt as an argument since it is wanted in the instructions.*/
	freqOfLetters();
	mixTheColors();
	ticTacToe();
}

void freqOfLetters()
{
	printf("\n***********|PART-1|***********\n");
	FILE *letterFile;
	
	int counter[26] = {0};   // I did all calculations according to the ASCII table.So Firstly I initialized the array with zeros.

	char character;
	int isCharacterLetter,isUpperCase,isLowerCase;
	char file_name[50];

	int k;

	printf("Enter the file name:");
	scanf(" %s",file_name);
	fflush(stdin);
	letterFile = fopen(file_name,"r");

	if(letterFile == NULL)
	{
		printf("The file is not found.\n");
		return;
	}

	while(!feof(letterFile))
	{
		fscanf(letterFile,"%c",&character);

		/* I am checking the letters are uppercase or lowercase. Then I check the character is letter or not.*/

		isUpperCase = (character>=UPPER_MIN && character<=UPPER_MAX);
		isLowerCase = (character>=LOWER_MIN && character<=LOWER_MAX);
		
		isCharacterLetter = (isUpperCase || isLowerCase );
		
		/* If the character is letter the program will control that the character is uppercase or lowercase.
			The alphabetic number of the character is incremented by 1. If uppercase: 'A' ASCII equivalent is 65.
			Then the location of the A in the counter[] array is 0 point. The program calculates the point according to 
			ASCII - UPPER_MIN. Otherwise if lowercase 'a': ASCII equivalent is 97. The location is again 0 point.
			The location is found using same logic: ASCII - LOWER_MIN. */

		if(isCharacterLetter)
		{
			if(isUpperCase)
				counter[(int)character - UPPER_MIN] += 1;
			else
				counter[(int)character - LOWER_MIN] += 1;
		}
	}
	printf("Letter frequency: \n");
	
	/*The array is printed here.*/
	for(k=0; k<26; k++)
		printf("%c: %d\n",k+UPPER_MIN, counter[k]);
}

void mixTheColors()
{
	char firstChar,secondChar;
	color firstColor,secondColor;
	int trueColors = 0;

	printf("\n***********|PART-2|***********\n");

	while (!trueColors)
	{
		printf("\nEnter the first color (r,g,b,y,o): ");
		scanf(" %c",&firstChar);
		printf("Enter the second color (r,g,b,y,o): ");
		scanf(" %c",&secondChar);

		trueColors =( firstChar =='r' || firstChar == 'g' || firstChar == 'b' || firstChar == 'y' || firstChar == 'o')
					&& (secondChar =='r' || secondChar == 'g' || secondChar == 'b' || secondChar == 'y' || secondChar == 'o');
	}

	/* It is wanted that the colorMixer function must take colors as an enumerated type.
	   So that I use 2 switch-case and determine my parameters according to inputs. */

	switch (firstChar)
	{
	case 'r':firstColor = RED;break;
	case 'g':firstColor = GREEN;break;
	case 'b':firstColor = BLUE;break;
	case 'y':firstColor = YELLOW;break;
	case 'o':firstColor = ORANGE;break;
	default:printf("Invalid firstChar");break;
	}

	switch (secondChar)
	{
	case 'r':secondColor = RED;break;
	case 'g':secondColor = GREEN;break;
	case 'b':secondColor = BLUE;break;
	case 'y':secondColor = YELLOW;break;
	case 'o':secondColor = ORANGE;break;
	default:printf("Invalid color2");break;
	}
	/* The colorMixer function is called here. It takes 2 color type variable and 1 function pointer.*/
	colorMixer(firstColor,secondColor, mix);
}

void colorMixer(color firstColor, color secondColor, color(*mix)(color,color))
{
	color mixedColor;
	mixedColor = mix(firstColor,secondColor);
	
	/* The proper message is printed according to the result of mix() function.*/
	switch (mixedColor)
	{
	case 0:printf("Mixed Color: RED [1,0,0]\n");break;
	case 1:printf("Mixed Color: GREEN [0,1,0]\n");break;
	case 2:printf("Mixed Color: BLUE [0,0,1]\n");break;
	case 3:printf("Mixed Color: YELLOW [0.5,0.5,0]\n");break;
	case 4:printf("Mixed Color: ORANGE [0.5,0.4,0.2]\n");break;
	default:printf("Something went wrong :(\n");break;
	}	
}

color mix(color firstColor, color secondColor)
{
	float minDistance = 0;

	float firstArr[3];
	float secondArr[3];
	float mixedArr[3];

	/* These arrays is used for comparison to other two arrays.*/

	float red[3] = {1,0,0};
	float green[3] = {0,1,0};
	float blue[3] = {0,0,1};
	float yellow[3] = {0.5,0.5,0};
	float orange[3] = {0.5,0.4,0.2}; 
	
	color mixedColor;
	
	/* These switch cases is used for creating an array according to the firstColor and secondColor.*/

	switch (firstColor)
	{
	case RED:
		 firstArr[0] = 1;
		 firstArr[1] = 0;
		 firstArr[2] = 0;
		 break;
	case GREEN:
		 firstArr[0] = 0;
		 firstArr[1] = 1;
		 firstArr[2] = 0;
		 break;
	case BLUE:
		 firstArr[0] = 0;
		 firstArr[1] = 0;
		 firstArr[2] = 1;
		 break;
	case YELLOW:
		 firstArr[0] = 0.5;
		 firstArr[1] = 0.5;
		 firstArr[2] = 0;
		 break;
	case ORANGE:
		 firstArr[0] = 0.5;
		 firstArr[1] = 0.4;
		 firstArr[2] = 0.2;
		 break;
	default:printf("Invalid firstChar");break;
	}

	switch (secondColor)
	{
	case RED:
		 secondArr[0] = 1;
		 secondArr[1] = 0;
		 secondArr[2] = 0;
		 break;
	case GREEN:
		 secondArr[0] = 0;
		 secondArr[1] = 1;
		 secondArr[2] = 0;
		 break;
	case BLUE:
		 secondArr[0] = 0;
		 secondArr[1] = 0;
		 secondArr[2] = 1;
		 break;
	case YELLOW:
		 secondArr[0] = 0.5;
		 secondArr[1] = 0.5;
		 secondArr[2] = 0;
		 break;
	case ORANGE:
		 secondArr[0] = 0.5;
		 secondArr[1] = 0.4;
		 secondArr[2] = 0.2;
		 break;
	default:printf("Invalid color2");break;
	}


	/* The mixed color's array is created here.*/
	for(int i = 0; i<3; i++)
		mixedArr[i] = (firstArr[i]+ secondArr[i])/2;
	
	/* Firstly the program accepts that the RED is the closest and then program checks the other colors.*/

	minDistance = calculateDistance(mixedArr,red);
	mixedColor = RED;

	if(calculateDistance(mixedArr,green) < minDistance)
	{
		mixedColor = GREEN;
		minDistance =  calculateDistance(mixedArr,green);
	}
		
	if(calculateDistance(mixedArr,blue) < minDistance)
	{
		mixedColor = BLUE;
		minDistance =  calculateDistance(mixedArr,blue);
	}
	if(calculateDistance(mixedArr,yellow) < minDistance)
	{
		mixedColor = YELLOW;
		minDistance =  calculateDistance(mixedArr,yellow);
	}
	if(calculateDistance(mixedArr,orange) < minDistance)
	{
		mixedColor = ORANGE;
		minDistance =  calculateDistance(mixedArr,orange);
	}

	/*According to the operations above function returns mixedcolor.*/
	return mixedColor;
}

/* The function below is created to apply "euclidian sum".*/

float calculateDistance(float mixedArr[] ,float colorArr[])
{
	float sum = 0;
	float distance;

	for(int i=0; i<3; i++)
	{
		sum += pow(colorArr[i] - mixedArr[i] , 2);
	}
	distance = sqrt(sum);

	return distance;
}

void ticTacToe()
{
	/* The locations of X and O are defined seperately below.*/
	int rowX,columnX,
		rowO,columnO;

	int i,k,counter = 0;

	int gameWin = 0;
	int isCorrectEntries; // This is for checking whether entry is proper or not.
	char gameBoard[3][3] = {{'-','-','-'},{'-','-','-'},{'-','-','-'}};
	char playAgain;

	printf("\n***********|PART-3|***********\n");

	while(gameWin == 0 && counter != 9)
	{
		printf("Player-1 (X), enter your move (row,column): ");
		scanf("%d %d",&rowX,&columnX);
		fflush(stdin); // This is for cleaning the scanf's buffer.

		/* The isCorrectEntries checks conditions that player can move desired location or not.*/
		isCorrectEntries = (rowX < 3 && rowX>=0) && (columnX < 3 && columnX>=0) && (gameBoard[rowX][columnX] != 'O' && gameBoard[rowX][columnX] != 'X');

		/* The program wants user to enter entries till user enter proper entries.*/
		while(!isCorrectEntries)
		{
			printf("Player-1 (X), enter your move (row,column): ");
			scanf("%d %d",&rowX,&columnX);
			fflush(stdin);
			isCorrectEntries = (rowX < 3 && rowX>=0) && (columnX < 3 && columnX>=0) && (gameBoard[rowX][columnX] != 'O' && gameBoard[rowX][columnX] != 'X');
		}	

		/* The location that user's input is changed with character 'X'.*/
		gameBoard[rowX][columnX] = 'X';
		
		/* Counter is used for counting the number of total move */
		counter++;  

		for(i=0; i<3;i++)
		{
			for(k=0; k<3; k++)
				printf("%c ",gameBoard[i][k]);
			
			printf("\n");
		}

		/* In this for loop I am checking the winning situation.*/
		for(i=0; i<=2; i++)
		{
			if((gameBoard[i][0] == gameBoard[i][1] && gameBoard[i][1] == gameBoard[i][2] && gameBoard[i][0] == 'X') 
			||(gameBoard[0][0] == gameBoard[1][1] && gameBoard[1][1] == gameBoard[2][2] && gameBoard[0][0] == 'X') 
			||(gameBoard[0][2] == gameBoard[1][1] && gameBoard[1][1] == gameBoard[2][0] && gameBoard[0][2] == 'X') 
			||(gameBoard[0][i] == gameBoard[1][i] && gameBoard[1][i] == gameBoard[2][i] && gameBoard[0][i] == 'X')) gameWin = 1;	
		}
		if(gameWin)
			printf("Player-1 (X) won the game.\n");

		/* Player-2 can play if given conditions is provided then.*/
		if(counter<9 && !gameWin)
		{
			printf("Player-2 (O), enter your move (row,column): ");
			scanf("%d %d",&rowO,&columnO);
			fflush(stdin);
			
			/* The isCorrectEntries checks conditions that player can move desired location or not.*/
			isCorrectEntries = (rowO < 3 && rowO>=0) && (columnO < 3 && columnO>=0) && (gameBoard[rowO][columnO] != 'X' && gameBoard[rowO][columnO] != 'O');

			while(!isCorrectEntries)
			{
				printf("Player-2 (O), enter your move (row,column): ");
				scanf("%d %d",&rowO,&columnO);
				fflush(stdin);
				isCorrectEntries = (rowO < 3 && rowO>=0) && (columnO < 3 && columnO>=0) && (gameBoard[rowO][columnO] != 'X' && gameBoard[rowO][columnO] != 'O');
			}	
			gameBoard[rowO][columnO] = 'O';
			counter++;

			for(i=0; i<3;i++)
			{
				for(k=0; k<3; k++)
					printf("%c ",gameBoard[i][k]);
				
				printf("\n");
			}

			for(i=0; i<=2; i++)
			{
				if((gameBoard[i][0] == gameBoard[i][1] && gameBoard[i][1] == gameBoard[i][2] && gameBoard[i][0] == 'O') 
				||(gameBoard[0][0] == gameBoard[1][1] && gameBoard[1][1] == gameBoard[2][2] && gameBoard[0][0] == 'O') 
				||(gameBoard[0][2] == gameBoard[1][1] && gameBoard[1][1] == gameBoard[2][0] && gameBoard[0][2] == 'O') 
				||(gameBoard[0][i] == gameBoard[1][i] && gameBoard[1][i] == gameBoard[2][i] && gameBoard[0][i] == 'O')) gameWin = 1;	
			}
			if(gameWin)
				printf("Player-2 (O) won the game.\n");

		}
		/* If the board is full but the game not ends with winning situation then this message will be shown.*/
		else if(counter>=9 && !gameWin)
			printf("It is a tie for this game !\n");
		
	}
	
}
