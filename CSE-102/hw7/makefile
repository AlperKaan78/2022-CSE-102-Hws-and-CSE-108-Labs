all: clean compile run

compile:
	@gcc -o test main.c util.c other_functs.c -lm

run:
	@./test

clean:
	@rm -f test
	@rm -f *.o