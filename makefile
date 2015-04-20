all:
	gcc -o cpu $(wildcard *.c) -lpthread

try:
	gcc -o cpu $(wildcard *.c) -lpthread
	./cpu

wall:
	gcc -o cpu -Wall -pedantic $(wildcard *.c) -std=c99 -lpthread -fdiagnostics-show-option

clear:
	rm *.gch *.o -f cpu

run:
	./cpu