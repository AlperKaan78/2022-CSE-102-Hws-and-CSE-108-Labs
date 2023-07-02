#include<stdio.h>
#include<time.h>
#include<stdlib.h>

void orderProgram();
//These 2 functions is created for using in the orderProgram() function.
void readAndShow();
float getPrice(int);

void rockPaperScissors();

void main()
{
    orderProgram();
    rockPaperScissors();
}

void orderProgram()
{ 
    FILE *receipt;  // This is my receip txt file.

    int chosenProduct;
    int servingsNum = 1;
    float totalPrice = 0;

    char isStudent, receiptChar;
    float studentDiscount;
    float VAT;

    receipt = fopen("receipt.txt","w"); // The receipt file is opened here.

    readAndShow(); // The readAndShow function is called here and proccess starts.


    /* These 5 line for getting time informations and printing it to the receipt. 
        I could not do these operations without using array or struct type.*/

    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char s[64];
    strftime(s,sizeof(s),"%d.%m.%Y/%H:%M",tm);
    fprintf(receipt,"\n210104004040    %s\n",s);

    // The receipt have been created here.

    fprintf(receipt,"--------------------------------\n");
    fprintf(receipt,"Product                Price(TL)\n");
    fprintf(receipt,"--------------------------------\n");

    // While loop continues till the servingsNum variable is zero.

    while (servingsNum != 0)
    {
        
        printf("Please choose a product (1-12):");
        scanf(" %d", &chosenProduct);

        printf("How many servings do you want?");
        scanf(" %d", &servingsNum);
        
        
        /* If statement controls the situation that user may want to end choosing and servingsNum is printed 0.
            Each chosen product, serving number and its price is written to receipt.txt file.
            I can not do this without using product names.(doner, lahmacun)*/

        if(servingsNum != 0)
        {
            switch (chosenProduct)
                {
                case 1:
                    fprintf(receipt,"%d* Kebap                  %.2f\n",servingsNum,servingsNum*getPrice(1));
                    break;
                case 2:
                    fprintf(receipt,"%d* Lahmacun               %.2f\n",servingsNum,servingsNum*getPrice(2));
                    break;
                case 3:
                    fprintf(receipt,"%d* Pide                   %.2f\n",servingsNum,servingsNum*getPrice(3));
                    break;
                case 4:
                    fprintf(receipt,"%d* Doner                  %.2f\n",servingsNum,servingsNum*getPrice(4));
                    break;
                case 5:
                    fprintf(receipt,"%d* Kola                   %.2f\n",servingsNum,servingsNum*getPrice(5));
                    break;
                case 6:
                    fprintf(receipt,"%d* Su                     %.2f\n",servingsNum,servingsNum*getPrice(6));
                    break;
                case 7:
                    fprintf(receipt,"%d* Kunefe                 %.2f\n",servingsNum,servingsNum*getPrice(7));
                    break;
                case 8:
                    fprintf(receipt,"%d* Sutlac                 %.2f\n",servingsNum,servingsNum*getPrice(8));
                    break;
                case 9:
                    fprintf(receipt,"%d* Pizza                  %.2f\n",servingsNum,servingsNum*getPrice(9));
                    break;
                case 10:
                    fprintf(receipt,"%d* Kanat                  %.2f\n",servingsNum,servingsNum*getPrice(10));
                    break;
                case 0:
                    break;
                default:
                    printf("Invalid selection for product!\n");
                    break;  
            }
        }
        // The price for the each product is added to the total price.

        totalPrice += servingsNum*getPrice(chosenProduct);
    }
    fprintf(receipt,"\nTotal:                    %.2f\n",totalPrice);
    /* The program controls whether user is student.
        If so student discount will be calculated and printed.
        But student discount is not substracted from the total price.*/

	while(isStudent != 'Y' && isStudent != 'y' && isStudent != 'N' && isStudent != 'n')
	{

    	printf("Are you Student (Y or N): ");
    	scanf(" %c",&isStudent);

	}
	if(isStudent == 'Y' || isStudent == 'y')
    {
       studentDiscount = (totalPrice * 0.125);
       fprintf(receipt,"Student Discount:         %.2f\n", -studentDiscount);
    }

    /*If the total price bigger than 150 then program calculates additional discount and prints it to the receipt.*/
    if(totalPrice>=150)
    {
        fprintf(receipt,"Add Discount:             %.2f\n",totalPrice*(-0.1));
        totalPrice += totalPrice*(-0.1);
    }

    /* The student discount that have been found before is substracted from total price here */
    totalPrice -= studentDiscount;
    fprintf(receipt,"--------------------------------\n");
    fprintf(receipt,"Price:                    %.2f\n",totalPrice);

    /* Vat price is calculated here and total price with Vat is printed to txt file.*/

    VAT = totalPrice*(0.18);
    fprintf(receipt,"Price + VAT:              %.2f\n",totalPrice + VAT);
    
    fclose(receipt);

    /* The program reopen the receip.txt since to print receipt on to the terminal*/

    receipt = fopen("receipt.txt","r");
    while(!feof(receipt))
    {
        fscanf(receipt,"%c",&receiptChar);
        printf("%c",receiptChar);
    }
    fclose(receipt);
}

/* The readAndShow function reads product names and prices from the menu.txt file
    and it just print product names on to the terminal.
    product,price --> This variables is for products (but the program gets the names as a character) and prices.
    spaceFlag --> I use this variable to seperate product and price int while scanning the file.
    counter --> It is used to print number of the product.*/

void readAndShow()
{
    FILE *menu;

    char product;
    float price;

    int spaceFlag = 0, counter = 1;

    menu = fopen("menu.txt","r");
	
	printf("----------------|PART-1|----------------\n");
    printf("Yemek Listesi: \n");
    printf("%d.",counter);

    while(!feof(menu))
    {
        if(spaceFlag == 0)
        {
            fscanf(menu,"%c",&product);
            printf("%c",product);

            /* If product equals to the space character then spaceFlag will be 1
                and program stops getting characters temporarily.*/

            if(product == ' ')
            {
                spaceFlag = 1;
                continue;
            }

            /* This if statement for printing the product number. 
                Each line counter is incremented by 1 and counter is printed.*/

            if(product == '\n' )
            {
                counter++;
                printf("%d.",counter);
            }
        }
        else 
        {
            /* When the spaceFlag equals to the 1 then price is scanning from the file
                SpaceFlag will be equals to 0 and program continues to read characters above. */

            fscanf(menu,"%f",&price);
            spaceFlag = 0;
        }
       
        
    }
    printf("\n");
    fclose(menu);
}

/*The getPrice function is created for getting price of the chosen product
    Function is getting chosenProduct as a parameter .
    When the counter equals to the chosen product (counter is actually line number)
    the price information is returned. This function is similar to the readAndShow function.
    The search algorithms are same in each function.
    price variable is used for all products price but dishPrice is used just chosen product from the user.*/ 

float getPrice(int chosenProduct)
{
    FILE *menu;

    char product;
    float price,dishPrice;
    int spaceFlag = 0, counter = 1;

    menu = fopen("menu.txt","r"); // The menu.txt file is opening with read mode.

    while(!feof(menu))
    {
        if(spaceFlag == 0)
        {
            fscanf(menu,"%c",&product);

            if(product == ' ')
            {
                spaceFlag = 1;
                continue;
            }
            if(product == '\n' )
                counter++;
        }
        else 
        {
            fscanf(menu,"%f",&price);
            if(counter == chosenProduct)
                dishPrice = price;
            spaceFlag = 0;
        }        
    }
    fclose(menu);

    return dishPrice;
}


void rockPaperScissors()
{
    int playerSelection,computerSelection;
    char newGame = 'Y';
 	   
	printf("----------------|PART-2|----------------\n");
    /* If newGame character equals y or Y the program will continue. */
    while (newGame == 'y' || newGame == 'Y')
    {
        printf("\nPlease make a choice:\n1-Rock 2-Paper 3-Scissors\n");
        scanf(" %d",&playerSelection);
        
        /* Computer generates number between 1 and 3 each time and checks who won the game*/

        srand(time(0));
        computerSelection = rand()%3 +1;

        switch (computerSelection)
        {
        case 1:
            if(playerSelection == 1)
                printf("You chose Rock. I chose Rock. It is a Tie!");
            else if(playerSelection == 2)
                printf("You chose Paper. I chose Rock. You Won!");
            else if(playerSelection == 3)
                printf("You chose Scissors. I chose Rock. I Won!");
            else    
                printf("Your selection is Invalid");
            break;
        case 2:
            if(playerSelection == 1)
                printf("You chose Rock. I chose Paper. I Won!");
            else if(playerSelection == 2)
                printf("You chose Paper. I chose Paper. It is a Tie!");
            else if(playerSelection == 3)
                printf("You chose Scissors. I chose Paper. You Won!");
            else    
                printf("Your selection is Invalid");
            break;
        case 3:
            if(playerSelection == 1)
                printf("You chose Rock. I chose Scissors. You Won!");
            else if(playerSelection == 2)
                printf("You chose Paper. I chose Scissors. I Won!");
            else if(playerSelection == 3)
                printf("You chose Scissors. I chose Scissors. It is a Tie!");
            else    
                printf("Your selection is Invalid");
            break;
        default:
            break;
        }
        /* The program asks if player want to play again after switch-case.*/
        printf("\nDo you want to play again(Y/N):");
        scanf(" %c",&newGame);

        /* The while loop checks entry is valid or not.*/
        while((newGame != 'y' && newGame != 'Y') && (newGame != 'N' && newGame != 'n'))
        {
            printf("\nDo you want to play again(Y/N):");
            scanf(" %c",&newGame);
        }
        
    }


}
