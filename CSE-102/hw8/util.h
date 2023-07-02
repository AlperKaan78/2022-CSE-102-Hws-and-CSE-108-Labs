#ifndef _UTIL_H_
#define _UTIL_H_

#define UP 'U'
#define DOWN 'D'
#define RIGHT 'R'
#define LEFT 'L'

typedef struct 
{
    char board[3][3];

}puzzle_t;


void play_game(char *);

void auto_finish(char *game_file, puzzle_t *, int initial_X, int initial_Y, int num_of_move);

void show_best_score(char *);

void random_fill_board(puzzle_t *);

int is_free(char (*board)[3], int, int);

int is_solvable(const puzzle_t *puzzle);

int is_solved(puzzle_t *);

void unfill_board(puzzle_t *puzzle);

void print_board(puzzle_t *puzzle);

int is_legal_move(puzzle_t *puzzle, int x, int y);

int is_legal_move_space(puzzle_t *puzzle, int x, int y);

#endif