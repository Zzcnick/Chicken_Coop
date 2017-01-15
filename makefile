GCC = gcc -g

all: board.o set.o
	$(GCC) board.o set.o -o stest

board.o: board.c board.h
	$(GCC) -c board.c

set.o: set.c board.c
	$(GCC) -c set.c

clean:
	rm *.o
	rm *~

run: all
	./stest
