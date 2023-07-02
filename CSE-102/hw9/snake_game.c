#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "util.h"


int main()
{
    block_t ***board;
    srand(time(NULL));
    board = init_board();
    play(board);
}


block_t *** init_board()
{
    block_t ***board;

    int bait_x,bait_y,obs_x,obs_y;

    // srand(time(NULL));

    // generating random coordinates for obstacle and bait.
    do{
        bait_x = rand()%(ROWS-1)+1;
        bait_y = rand()%(COLUMNS-1)+1;
        obs_x = rand()%(ROWS-1)+1;
        obs_y = rand()%(COLUMNS-1)+1;
    }while (bait_x == obs_x && bait_y == obs_y);
    

    // allocating memory for first dimension 
    board = (block_t***)malloc(sizeof(block_t **)*ROWS);
    
    if(board == NULL)
    {
        printf("There is an error while allocating the memory for x-axis.\n");
    }
    
    // allocatin memory for each rows.
    for(int k= 0; k<ROWS; k++)
    {
        board[k] = (block_t**)malloc(sizeof(block_t *)*COLUMNS);
        
        if(board[k] == NULL)
        {
            printf("There is an error while allocating the memory for y-axis.\n");
        }

        // allocating memory for each cell.
        for(int i=0; i<ROWS; i++)
        {
            board[k][i] = (block_t*)malloc(sizeof(block_t));
            board[k][i]->type = 'e';
            board[k][i]->value = 0;
        }
    }

    // Randomly generated bait and obstacle are placed on the board.
    board[bait_x][bait_y]->type = 'b';
    board[obs_x][obs_y]->type = 'o';


    board[obs_x][obs_y]->value = rand()%9+1; // the value of the obstacle is randomly generated and assigned here.
    board[obs_x][obs_y] = (block_t*)realloc(board[obs_x][obs_y], sizeof(block_t)*board[obs_x][obs_y]->value);
    return board;

}

void draw_board(block_t ***board, point_t *snake, int length)
{
    int is_snake;
    // for loops starts from -1 and ends with columns number (10) since there must be 2 more space for edges.
    for(int k= -1; k<ROWS+1; k++)
    {
        for(int i=-1; i<COLUMNS+1; i++)
        {
            /*If there is a part of snake's body, then that part will be printed if not space character will be printed*/
            is_snake = 0;
            if(k==-1 || k==ROWS)
            {
                printf("- ");
            }
            else{
                if(i==-1 || i == COLUMNS)
                {
                    printf("| ");
                }
                else{
                    if(board[k][i]->type == 'e')
                    {
                        for(int n=0; n<length; n++)
                        {
                            if(k==snake[n].row && i==snake[n].column)
                            {
                                if(n == 0) printf("O ");
                                else printf("X ");
                                is_snake=1;
                            }  
                        }
                        if(!is_snake)
                            printf("  ");

                    }
                    else if(board[k][i]->type == 'o')
                    {
                        if(board[k][i]->value<=9)
                            printf("%d ",board[k][i]->value);
                        else
                            printf("%d",board[k][i]->value);    
                    }
                    else if(board[k][i]->type == 'b')
                        printf(". ");
                }
            }
        }
        printf("\n");
    }
}

void play(block_t ***board)
{
    point_t *snake;

    char direction;
    int game_end = 0, length = 1, num_of_move = 0;

    snake = (point_t*)malloc(sizeof(point_t)*length); // snake variable is allocated here.
    
    if(snake == NULL)
    {
        printf("There is an error while allocating memory for the snake.\n");
    }
    
    // Initial position of the snake is at the top left.
    snake[0].column = 0;
    snake[0].row = 0;

    while(!game_end)
    {
        draw_board(board,snake,length);
        direction = move(snake,length);
        num_of_move++;
        if(check_status(snake,board,length))
            update(board, &snake, &length, num_of_move, direction);
        else
        {
            printf("GAME OVER!\nYour score:%d\n",length-1);
            game_end = 1;

            /* Deallocating memory for each dimension of board and snake.*/
            
            for(int n=0; n<ROWS; n++)
            {
                
                for(int l=0; l<COLUMNS; l++)
                {
                    free(board[n][l]);
                }
                free(board[n]);
            }
            free(board);
            free(snake);
        }
    }
}
char move(point_t *snake, int length)
{
    char move;
    int i,invalid_move;
    
    /* If lenght is one, then there is no limitation for moving.*/
    if(length == 1)
    {
        printf("Enter the move direction: (w,a,s,d)");
        scanf(" %c",&move);
        while(getchar() != '\n');
        
        switch (move)
        {
        case UP:snake[0].row--; break;
        case DOWN:snake[0].row++; break;
        case RIGHT:snake[0].column++; break;
        case LEFT:snake[0].column--; break;
        default:printf("Your move direction is invalid"); break;
        }

    }
    /* If the lenght of the snake larger than one then, each move back moving must be controlled and ignored.*/
    else{
        do{
            invalid_move = 0;
            printf("Enter the move direction: (w,a,s,d)");
            scanf(" %c",&move);

            switch (move)
            {
            case UP:
                if(((snake[0].row -1== snake[1].row) && (snake[0].column == snake[1].column)))
                    invalid_move=1;
                else
                    snake[0].row--;
                break;
            case DOWN:
                if(((snake[0].row +1 == snake[1].row) && (snake[0].column == snake[1].column)))
                    invalid_move=1; 
                else    
                    snake[0].row++;
                break;
            case RIGHT:
                if(((snake[0].row == snake[1].row) && (snake[0].column+1 == snake[1].column)))
                    invalid_move =1;
                else
                    snake[0].column++;
                break;
            case LEFT: 
                if(((snake[0].row == snake[1].row) && (snake[0].column-1 == snake[1].column)))
                    invalid_move =1;
                else    
                    snake[0].column--;   
                break;
            default:printf("Your move direction is invalid"); break;
            }
        }while (invalid_move);

    }
    return move;

}


int check_status(point_t *snake, block_t ***board, int length)
{
    int game_cont = 1; // Game continuety variable.

    /* Borders are checked in this if statement.*/
    if(snake[0].row>=ROWS || snake[0].column>=COLUMNS || snake[0].row <0 || snake[0].column<0)
    {
        game_cont = 0;
    }
    /* If obstacle has larger lenght than snake, the game will over.*/
    else if(board[snake[0].row][snake[0].column] ->type == 'o')
    {
        if(board[snake[0].row][snake[0].column]->value > length)
        {
            game_cont = 0;
        }
    }
    /* The situation whether the snake touches its body is controlled in these statements.*/
    int head_row= snake[0].row,head_column = snake[0].column;
    
    for(int m=1; m<length; m++)
    {
        if(head_column == snake[m].column && head_row == snake[m].row) game_cont =0;

    }

    return game_cont;
}

/* I need to return new location of the snake variable as there is a reallocating proccess on the snake.*/
void update(block_t ***board, point_t **snake, int *length, int num_of_move, char direction)
{
    int bait_x, bait_y, obs_x, obs_y, new_value, on_snake_body;


    /*
        If type of the block is bait then program will increase the length of the snake and generate new 
        location for the bait randomly.
    */
    if (board[(*snake)[0].row][(*snake)[0].column]->type == 'b') {
        
        board[(*snake)[0].row][(*snake)[0].column]->type = 'e';
        (*length)++;

        (*snake) = (point_t*)realloc((*snake), sizeof(point_t) * (*length));
        if ((*snake) == NULL) printf("There is an error while reallocating memory for the (*snake)!!\n");

        do {
            bait_x = rand() % ROWS;
            bait_y = rand() % COLUMNS;

            /* It is checked whether new bait location is on the snake's body.*/
            on_snake_body = 0;
            for (int k = 0; k < (*length); k++) {
                if ((*snake)[k].row == bait_x && (*snake)[k].column == bait_y) {
                    on_snake_body = 1;
                    break;
                }
            }
        } while (board[bait_x][bait_y]->type != 'e' || on_snake_body);
        board[bait_x][bait_y]->type = 'b';
        board[bait_x][bait_y]->value = 0;
    }

    /*
        If type of the block is obstacle then program will break the obstacle and generate new 
        location for the obstacle randomly.
    */

    else if (board[(*snake)[0].row][(*snake)[0].column]->type == 'o') {
        board[(*snake)[0].row][(*snake)[0].column]->type = 'e';
        board[(*snake)[0].row][(*snake)[0].column]->value = 0;
        board[(*snake)[0].row][(*snake)[0].column] = (block_t*)realloc(board[(*snake)[0].row][(*snake)[0].column],sizeof(block_t));
        
        for (int k = 0; k < ROWS; k++) {
            for (int m = 0; m < COLUMNS; m++) {
                if (board[k][m]->type == 'o') {
                    
                    new_value = rand() % 9 + board[k][m]->value;
                    
                    board[k][m]->value = new_value;
                    board[k][m] = (block_t*)realloc(board[k][m], sizeof(block_t) * new_value);
                }
            }
        }
    }
    /* After each 5 move the obstacles is replaced by news that can be one up to three.*/
    if (num_of_move % 5 == 0) {
        for (int k = 0; k < ROWS; k++) {
            for (int l = 0; l < COLUMNS; l++) {
                if (board[k][l]->type == 'o') {
                    board[k][l]->type = 'e';
                    board[k][l]->value = 0;
                    board[k][l] = (block_t*)realloc(board[k][l], sizeof(block_t));
                }
            }
        }
        for (int n = 0; n <= rand() % 3; n++) {
            do {
                obs_x = rand() % ROWS;
                obs_y = rand() % COLUMNS;

                on_snake_body = 0;
                for (int k = 0; k < (*length)-1; k++) {
                    if ((*snake)[k].row == obs_x && (*snake)[k].column == obs_y) {
                        on_snake_body = 1;
                        break;
                    }
                }
            } while (board[obs_x][obs_y]->type != 'e' || on_snake_body);

            board[obs_x][obs_y]->type = 'o';
            board[obs_x][obs_y]->value = rand() % 9 + 1;
            board[obs_x][obs_y] = (block_t*)realloc(board[obs_x][obs_y],sizeof(block_t) * board[obs_x][obs_y]->value );
        }
    }

    /* After each move the value of the obstacle blocks can be increase by between 1 and 5 amount that randomly generated..*/
    else{
        for (int k = 0; k < ROWS; k++) {
            for (int l = 0; l < COLUMNS; l++) {
                if (board[k][l]->type == 'o') {
                    board[k][l]->value++;
                    board[k][l] = (block_t*)realloc(board[k][l], sizeof(block_t));
                }
            }
        }
    }


    int head_row = (*snake)[0].row,
        head_column = (*snake)[0].column;

    /*
        I get the move from move function since I need to know where head of the snake has gone.
        Then I determine previous position of the snake's head so that the other parts of the snake can move.
    */
        
    switch (direction)
    {
    case UP:head_row++;break;
    case DOWN:head_row--;break;
    case RIGHT:head_column--;break;
    case LEFT:head_column++;break;
    default:break;
    }

    /* 
        The main algorithm of moving is here. Current row and column values are kept in x and y variables.
        The first part of the tail's location must be equal to old location of the head. Other part's location
        must be equal to the previos part's old location. After if else statements the locations of the
        previous part of the snake are kept in prev_x and prev_y variables. 
    */
    
    int i = 1, prev_x, prev_y, x, y;
    while (i < (*length)) {

        x = (*snake)[i].row;
        y = (*snake)[i].column;

        if (i == 1) {
            (*snake)[i].row = head_row;
            (*snake)[i].column = head_column;
        }
        else {
            (*snake)[i].row = prev_x;
            (*snake)[i].column = prev_y;
        }

        prev_x = x;
        prev_y = y;
        i++;
    }

}


