all:
	gcc -o cpu -Wall -pedantic $(wildcard *.c)

clear:
	rm *.gch *.o -f cpu

run:
	./cpu