#include<stdio.h>
#include"util.h"
#include<stdlib.h>
#include<time.h>

/* The time while creating a board can take few seconds. So, it can be neccessary to be patient. */

void play_game(char *game_file) {
    
    FILE *max_score_file;
    FILE *moves_file;

    char move_direction;
    
    // move_number variable is integer type since I do not want to encounter any problem when user enters number such as '1223'.
    int move_number,valid_num,number_X, number_Y, num_of_move = 0,score = 0;

    puzzle_t puzzle;

    do {
        unfill_board(&puzzle);
        random_fill_board(&puzzle);
    } while (!is_solvable(&puzzle));
    
    // Initial board is printed to the moves_file.
    moves_file = fopen(game_file,"w");
    for(int k=0; k<3; k++)
    {
        for(int i=0; i<3; i++)
        {
            fprintf(moves_file, "%c ",puzzle.board[k][i]);
        }
        fprintf(moves_file, "\n");
    }
    fclose(moves_file);

    while (!is_solved(&puzzle) && num_of_move < 100) {
        print_board(&puzzle); // Writing board to the terminal.
        

        valid_num = 0; 

        while (!valid_num) {
            printf("Enter the move (number-direction, e.g 2-R): ");
            scanf(" %d- %c", &move_number, &move_direction);
            valid_num = move_number > 0 && move_number < 9;

            if (!valid_num) {
                printf("Invalid move number. Try again.\n");
            }
        }

        // Finding number that equals to the user's number.
        for(int k = 0; k<3; k++)
        {
            for(int i = 0; i<3; i++)
            {
                // Since my board includes characters, I am adding 48 as a zero's representation in the ASCII table. 
                if(puzzle.board[k][i] == move_number + 48)
                {
                    number_X = k;
                    number_Y = i;
                }
            }
        }
        
        /* If entered direction is valid then program checks whether move is legal or not. After checking process, if move is 
            legal, the locations of number and '_' character are changed with each other.*/
        switch (move_direction) {
            case 'U':
                if(is_legal_move(&puzzle, number_X-1, number_Y))
                {
                    // Since our variable is an integer, we calculate the ascii equivalent to convert it to a character where 48 represents 0.
                    puzzle.board[number_X-1][number_Y] = move_number + 48; 
                    puzzle.board[number_X][number_Y] = '_';
                    num_of_move++;
                }
                else{
                    printf("%d-%c is an illegal move! Make a legal move!\n",move_number,move_direction);
                }
                break;
            case 'D':
                if(is_legal_move(&puzzle, number_X+1, number_Y))
                {
                    puzzle.board[number_X+1][number_Y] = move_number + 48;
                    puzzle.board[number_X][number_Y] = '_';                    
                    num_of_move++;

                }
                else{
                    printf("%d-%c is an illegal move! Make a legal move!\n",move_number,move_direction);
                }
                break;
            case 'R':
                if(is_legal_move(&puzzle, number_X, number_Y+1))
                {
                    puzzle.board[number_X][number_Y+1] = move_number + 48;
                    puzzle.board[number_X][number_Y] = '_';                    
                    num_of_move++;

                }
                else{
                    printf("%d-%c is an illegal move! Make a legal move!\n",move_number,move_direction);
                }
                break;
            case 'L':
                if(is_legal_move(&puzzle, number_X, number_Y-1))
                {
                    puzzle.board[number_X][number_Y-1] = move_number + 48;
                    puzzle.board[number_X][number_Y] = '_';                    
                    num_of_move++;

                }
                else{
                    printf("%d-%c is an illegal move! Make a legal move!\n",move_number,move_direction);
                }
                break;
            default:
                printf("%d-%c is an illegal move! Make a legal move!\n",move_number,move_direction);
                break;
        }
        
        // Program opens file as a append mode and close it since the written board can be printed to the file at end of the each loop. 
        moves_file = fopen(game_file,"a");
        fprintf(moves_file,"Player Move: %d-%c \n",move_number,move_direction);
        for(int k=0; k<3; k++)
        {
            for(int i=0; i<3; i++)
            {
                fprintf(moves_file, "%c ",puzzle.board[k][i]);
            }
            fprintf(moves_file, "\n");
        }
        score = 1000 - (10*num_of_move);
        fclose(moves_file);
    }



    if(!is_solved(&puzzle))
    {
        printf("\033[0;31m"); // For the red text color.
        printf("Try again!!\n");
        printf("\033[0m"); // Change color to default.
    }

    else{
        printf("\033[0;32m");// for the green color.
        printf("\nCongratulations !! You finished the game. \nNumber of move: %d \nYour score: %d\n\n",num_of_move,score);
        printf("\033[0m"); // Change color to default.
        
        max_score_file = fopen("max_score.txt","r+");
        
        int max_score; 
        
        max_score = fscanf(max_score_file,"%d",&max_score);
       
        if(score>max_score)
        {
            fseek(max_score_file,0,SEEK_SET);
            fprintf(max_score_file,"%d",score);
        }   
    }
    fclose(max_score_file);

}