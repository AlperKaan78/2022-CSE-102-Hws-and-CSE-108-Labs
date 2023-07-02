all: clean compile run

compile:
	@gcc -o test main.c util.c comp_play.c play_game.c max_score.c

run:
	@./test

clean:
	@rm -f *.o
	@rm -f test
