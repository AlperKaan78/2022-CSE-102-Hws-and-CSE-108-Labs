#include<stdio.h>
#include"util.h"

int main()
{
    FILE *moves_file;
    char *game_file = "moves.txt";
    char *best_score_file = "max_score.txt";
    
    puzzle_t auto_puzzle;
    
    //This variables are used in auto_finish function.
    int initial_X =0, initial_Y = 0;

    // I use selection as a char variable because integer variable may cause infinite loops when user enter character.
    char selection;
    
    printf("Welcome to the 8-Puzzle Game!\n");
    while(selection != '4')
    {
        printf("Please select an option:\n1. Play game as a user.\n2. Finish the game with PC.\n3. Show the best score.\n4. Exit.\n");
        scanf(" %c",&selection);
        switch (selection)
        {
        case '1':play_game(game_file);break;
        case '2':
            // This opening and closing operations delete all boards in txt file.
            moves_file = fopen(game_file,"w");
            fclose(moves_file);
            
            //Firstly, program filled with '_' characters. Then filled with numbers between 1-8.
            do {
                unfill_board(&auto_puzzle);
                random_fill_board(&auto_puzzle);
            } while (!is_solvable(&auto_puzzle));

            auto_finish(game_file,&auto_puzzle, initial_X, initial_Y,1);
            break;
        case '3':show_best_score(best_score_file);break;
        case '4':printf("GOODBYE!\n");break;
        default:printf("Your selection is invalid! Select Again.\n");break;
        }
    }
}