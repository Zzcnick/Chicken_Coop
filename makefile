board.o: board.c board.h
	gcc -c board.c

highscore.o: highscore.c highscore.h
	gcc -c highscore.c

set.o: set.c set.h
	gcc -c set.c

board: board.o
	gcc -o board board.o

clean:
	rm *.o
	rm *~

run: board
	./board
