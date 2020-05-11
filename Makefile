main:main.o mergesort.o
	gcc -Wall -o main main.o mergesort.o
main.o:
	gcc -c main.c
mergesort.o:
	gcc -c mergesort.c
