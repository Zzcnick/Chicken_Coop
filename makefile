GCC = gcc -g

all: board.o set.o highscore.o
	$(GCC) board.o set.o highscore.o -o stest

board.o: board.c board.h
	$(GCC) -c board.c

set.o: set.c board.c highscore.c
	$(GCC) -c set.c

highscore.o: highscore.c highscore.h
	$(GCC) -c highscore.c

setserver: setserver.c setserver.h
	$(GCC) setserver.c -o server.out

clean:
	rm *.o *~

run: all
	./stest
