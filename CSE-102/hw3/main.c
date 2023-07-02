#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define UP 'w'
#define DOWN 's'
#define LEfT 'a'
#define RIGHT 'd'

void drawTheRoom(int, int, int, int, int);
void playGame();
int isCorrectPos(int,int,int, int);
void gameMenu();

void main()
{
	gameMenu();
}



/* The gameMenu was created using while loop and switch-case. 
   The loop will continue till user selects 3. 
   In the case 1 the function goes to the other function called playGame so that the game start.
   In the case 2 and default part, proper messages are shown.
   Case 3 is used for quitting the game and default warn user */

void gameMenu()
{
	int selection = 0;
	while(selection != 3 )
	{
		printf("Welcome to the 2D Puzzle Game!\n1-New Game\n2-Help\n3-Exit\n");
		scanf(" %d",&selection);
		switch(selection)
		{
			case 1:
				playGame();
				break;
			case 2:
				printf("Diagonal moves are not allowed!\n'a' for left\n'd' for right\n'w' for up\n's' for down.\n\n");
				break;
			case 3:
				printf("\nGOODBYE:)\n\n");
				break;
			default:
				printf("Invalid number for operations.Choose again!\n");
				break;	
		}
	}
	
}

void playGame()
{
	int roomSize=0;  // The initial size of the room is considered zero.
	
	int character_X = 0,
		character_Y = 0,
		door_X = 0,
		door_Y = 0,
		moveCounter = 0;

	char move; 

	while(roomSize<5 || roomSize>10)
	{
		printf(" Please enter the room size. It has to be between 5 and 10: ");
		scanf("%d",&roomSize);
	}
	
	/* I seed the random number generator using time function 
	   since I do not want to get same numbers from the rand function.*/
	
	srand(time(0)); 
	
	/* Each starting time the locations of character and door are determined using rand function.
	   I calculate the mode with roomsize since I want to generate loacation in the room. 
	   I do not want to get same positions of character and door. Therefore I am using while loop.*/ 
	
	while(character_X == door_X && character_Y == door_Y)
	{
		character_X = rand() % roomSize;
		character_Y = rand() % roomSize;
		door_X = rand() % roomSize;
		door_Y = rand() % roomSize;
	}

	/* The first drawing the room. */
	
	drawTheRoom(character_X,character_Y,door_X,door_Y,roomSize);	
	
	/* The game will continue untill the player's position is same door's position.*/

	while(!isCorrectPos(character_X,character_Y,door_X,door_Y))
	{
 		
		printf("Enter the next move: ");
		while(getchar() != '\n');
		move = getchar();

		/* In any case we first check can the character's move appropriate using the statusControl function.
		   If character can move (there is no wall to move direction) 
		   the increment or decrement operation is applied.
		   The warning message is shown when character can not move and move is asked for from user again.*/

		switch(move)
		{
			case UP:
				if(!(character_Y >roomSize || character_Y -1<0))
				{
					character_Y -= 1;
					moveCounter++; // The counter is incremented by 1 each time the move is appropriate.
				}
				else
					printf("You can not break the wall! Try again.\n");
				break;
			case DOWN:
				if(!(character_Y +1 >roomSize -1 || character_Y +1<0))
				{
					character_Y += 1;
					moveCounter++; 
				}
				else
					printf("You can not break the wall! Try again.\n");
				break;
			case RIGHT:
				if(!(character_X +1 >roomSize -1 || character_X +1<0))
				{
					character_X += 1;
					moveCounter++; 
				}
				else
					printf("You can not break the wall! Try again.\n");
				break;
			case LEfT:
				if(!(character_X >roomSize || character_X -1<0))
				{
					character_X -= 1;
					moveCounter++; 
				}
				else
					printf("You can not break the wall! Try again.\n");
				break;
			default:
				printf("Invalid operation for moving!\n");
				break;
		}

		/*If character's position is same as door's position, then player win the game and message is shown
			If not new position of character is drawn calling drawTheRoom function.*/
		if(isCorrectPos(character_X,character_Y,door_X,door_Y))
			printf("\nYou win the game. BRAVO!\nTotal: %d move. \n\n",moveCounter);
		else
			drawTheRoom(character_X,character_Y,door_X,door_Y,roomSize);
	}

}






/* The function drawTheRoom takes the input and shows the room situation momentarily.
   If-else condition checks character's situation to win the game.
   I created the for loops since the main map is showed correctly.
   "|" and "-" characters are used for drawing the room*/

void drawTheRoom(int character_X, int character_Y,int door_X, int door_Y, int roomSize)
{
	// This variable holds 1 or 0 depends on character location equals to door location.

	for(int top = 0; top<=2*(roomSize -1)+2; top++)
	{
		printf("-");
	}
	printf("\n");	
	for(int row=0; row<roomSize; row++)
	{
		for(int column=0; column<=roomSize; column++)
		{		
			printf("|");
			
			/* These are boolean variables that controls the coordinates are equal to the character or door coordinates.
				If so the program do not print " " space character, it prints "C" or "D" characters.*/
			
			int isCharacterLoc = (row == character_Y && column == character_X);
			int isDoorLoc = (row == door_Y && column == door_X);

			if(isCharacterLoc)
				printf("C");
			if(isDoorLoc)
				printf("D");
			if(!isDoorLoc && !isCharacterLoc)
				printf(" ");
		}
		printf("\n");
	}
	
	for(int top = 0; top<=2*(roomSize -1)+2; top++)
	{
		printf("-");
	}
	printf("\n");
}




/* isCorrectPos function is created to control whether the move can be possible or not.
    If the character's location and the door's location are the same, the function returns 1. otherwise returns 0*/

int isCorrectPos(int character_X,int character_Y,int door_X,int door_Y)
{
    if (character_X == door_X && character_Y == door_Y) {
        return 1; // position is outside the room boundaries
    }
    else {
        return 0; // position is inside the room boundaries
    }
}
