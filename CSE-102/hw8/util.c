#include<stdio.h>
#include"util.h"
#include<stdlib.h>
#include<time.h>

/* Boards are filled with character type numbers with using for loop.*/
void random_fill_board(puzzle_t *puzzle) {
    
    int row, column;
    
    srand(time(0)); // This is for creating different boards.
    
    for (int i = 1; i <= 8; i++) {
        do {
            row = random() % 3;
            column = random() % 3;
        } while (!is_free(puzzle->board, row, column));
        puzzle->board[row][column] = i+48; // Integer numbers converted to a character forms by adding 48 (means 0 as an integer).
    }
}

/* Checks if desired move direction is free or not. */
int is_free(char (*board)[3], int row, int column) {
    if (board[row][column] == '_')
        return 1;
    else
        return 0;
}

// Each space is filled with '_' character.
void unfill_board(puzzle_t *puzzle)
{
    for(int k = 0; k<3; k++)
    {
        for(int i= 0; i<3; i++)
        {
            puzzle->board[k][i] = '_';
        }
    }
}

void print_board(puzzle_t *puzzle)
{
    for(int k=0; k<3; k++)
    {
        for(int i=0; i<3; i++)
        {
            printf("%c ",puzzle->board[k][i]);
        }
        printf("\n");
    }
}

/* This is used in user play_game function to check the given number can move or not.*/
int is_legal_move(puzzle_t *puzzle, int x, int y)
{
    if(x>=0 && x<=2 && y>=0 && y<=2 && (puzzle->board[x][y] == '_'))
    {
        return 1;
    }
    return 0;
}

/* This function is used in auto_finish function to check the '_' character can move desired move directions. */
int is_legal_move_space(puzzle_t *puzzle, int x, int y)
{
    if(x>=0 && x<=2 && y>=0 && y<=2)
    {
        return 1;
    }
    return 0;  
}


/* Some puzzles can not be solved. This function checks solvability of the puzzle.*/
int is_solvable(const puzzle_t *puzzle) {
    int inversions = 0;
    char flat[9];
    int i, j, k;

    // Flatten the puzzle board
    k = 0;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            flat[k++] = puzzle->board[i][j];
        }
    }

    // Count inversions
    for (i = 0; i < 9; i++) {
        for (j = i + 1; j < 9; j++) {
            if (flat[i] > flat[j] && flat[i] != '_' && flat[j] != '_') {
                inversions++;
            }
        }
    }

    return (inversions % 2 == 0);
}

/* This function checks the puzzle is solved or not. */
int is_solved(puzzle_t *puzzle)
{
    int flat[9];
    int k,j;

    k = 0;
    
    /* The items in puzzle are assigned to the another array caled flat. */
    for (int i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            flat[k++] = puzzle->board[i][j];
        }
    }

    /* This expression checks if the numbers have the correct order. */
    for(k=1; k<9; k++)
    {
        if(flat[k-1] != 48 + k)
        {
            return 0;
        }
    }
    return 1;
}
