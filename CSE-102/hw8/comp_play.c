#include <stdio.h>
#include "util.h"
#include <stdlib.h>
#include <time.h>

/* My main algorithm to solve puzzle recursively is to move the '_' character not the numbers. So I just use random function once.
    Then program finds legal moves and save them to the array(legal_diractions), at the same time number of legal directions 
    is increasing. Program selects random move direction choosing those legal directions. */
void auto_finish(char* game_file, puzzle_t* puzzle, int initial_X, int initial_Y, int num_of_move)
{
    FILE* moves_file;
    int direction;
    int space_X, space_Y;
    char move_number;

    /* If the puzzle was solved, the program will terminated.*/
    if (is_solved(puzzle))
    {
        print_board(puzzle);
        printf("Computer finished the game.\nTotal moves: %d\n", num_of_move);
        return;
    }

    /* These loops find the place of '_' character.*/
    for (int k = 0; k < 3; k++)
    {
        for (int i = 0; i < 3; i++)
        {
            if (puzzle->board[k][i] == '_')
            {
                space_X = k;
                space_Y = i;
            }
        }
    }

    // Create an array to store legal directions
    int legal_directions[4] = { -1, -1, -1, -1 };
    int num_legal_directions = 0;

    // Check each direction and store legal directions in the array
    if (is_legal_move_space(puzzle, space_X - 1, space_Y) && (space_X - 1 != initial_X) && (space_Y != initial_Y))
    {
        legal_directions[num_legal_directions++] = 0; // UP
    }
    if (is_legal_move_space(puzzle, space_X + 1, space_Y) && (space_X + 1 != initial_X) && (space_Y != initial_Y))
    {
        legal_directions[num_legal_directions++] = 1; // DOWN
    }
    if (is_legal_move_space(puzzle, space_X, space_Y + 1) && (space_X != initial_X) && (space_Y + 1 != initial_Y))
    {
        legal_directions[num_legal_directions++] = 2; // RIGHT
    }
    if (is_legal_move_space(puzzle, space_X, space_Y - 1) && (space_X != initial_X) && (space_Y - 1 != initial_Y))
    {
        legal_directions[num_legal_directions++] = 3; // LEFT
    }

    // If there are no legal directions, return
    if (num_legal_directions == 0)
    {
        printf("No legal moves available.\n");
        return;
    }
    
    // Randomly select a legal direction from available options
    direction = legal_directions[rand() % num_legal_directions];

    // Perform the move in the selected direction
    switch (direction)
    {
        case 0: // UP
            move_number = puzzle->board[space_X - 1][space_Y];
            puzzle->board[space_X - 1][space_Y] = '_';
            puzzle->board[space_X][space_Y] = move_number;
            num_of_move++;
            break;
        case 1: // DOWN
            move_number = puzzle->board[space_X + 1][space_Y];
            puzzle->board[space_X + 1][space_Y] = '_';
            puzzle->board[space_X][space_Y] = move_number;
            num_of_move++;
            break;
        case 2: // RIGHT
            move_number = puzzle->board[space_X][space_Y + 1];
            puzzle->board[space_X][space_Y + 1] = '_';
            puzzle->board[space_X][space_Y] = move_number;
            num_of_move++;
            break;
        case 3: // LEFT
            move_number = puzzle->board[space_X][space_Y - 1];
            puzzle->board[space_X][space_Y - 1] = '_';
            puzzle->board[space_X][space_Y] = move_number;
            num_of_move++;
            break;
        default:
            printf("Something went wrong.\n");
            break;
    }

    initial_X = space_X;
    initial_Y = space_Y;


    // Open the moves file in append mode
    moves_file = fopen(game_file, "a");
    if (moves_file == NULL)
    {
        printf("Error opening game file.\n");
        return;
    }

    /* Print each move to the terminal and moves.txt according to the direction variable(0,1,2,3). Since '_' character is moving in my program,
     the directions of numbers are opposite of the move direction.*/
    switch (direction)
    {
    case 0:printf("Computer Move: %d-D\n",move_number-48);fprintf(moves_file, "Computer Move: %d-D\n",move_number-48);break;
    case 1:printf("Computer Move: %d-U\n",move_number-48);fprintf(moves_file, "Computer Move: %d-U\n",move_number-48);break;
    case 2:printf("Computer Move: %d-L\n",move_number-48);fprintf(moves_file, "Computer Move: %d-L\n",move_number-48);break;
    case 3:printf("Computer Move: %d-R\n",move_number-48);fprintf(moves_file, "Computer Move: %d-R\n",move_number-48);break;    
    default:break;
    }

    // Write the current board state to the moves file
    for (int k = 0; k < 3; k++)
    {
        for (int i = 0; i < 3; i++)
        {
            fprintf(moves_file, "%c ", puzzle->board[k][i]);
        }
        fprintf(moves_file, "\n");
    }

    fclose(moves_file);


    // Print the board after the move
    print_board(puzzle);

    
    // Recursively call auto_finish
    auto_finish(game_file, puzzle, initial_X, initial_Y,num_of_move++);
}

