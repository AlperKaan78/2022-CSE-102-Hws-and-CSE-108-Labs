#ifndef UTIL_H
#define UTIL_H


#define UP 'w'
#define DOWN 's'
#define RIGHT 'd'
#define LEFT 'a'

#define ROWS 10
#define COLUMNS 10


typedef struct 
{
    char type;
    int value;

}block_t;

typedef struct{
    
    int row,column;

}point_t;


block_t ***init_board();

void draw_board(block_t ***board, point_t *snake, int length);

/* Game Play functions */
void play(block_t ***board);

char move(point_t *snake, int length);

int check_status(point_t *snake, block_t ***board,int length);

void update(block_t ***board,point_t **snake, int *length, int num_of_move,char move);


#endif