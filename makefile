GCC = gcc -g

all: board.o set.o highscore.o setserver.o
	$(GCC) board.o set.o highscore.o setserver.o -o set.out

set.o: set.c board.c highscore.o
	$(GCC) -c set.c

board.o: board.c board.h
	$(GCC) -c board.c

highscore.o: highscore.c highscore.h
	$(GCC) -c highscore.c

setserver.o: setserver.c setserver.h
	$(GCC) -c setserver.c

clean:
	rm *.o *~ *.out

run: all
	./set.out
