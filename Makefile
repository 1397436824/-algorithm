main:main.o kmp.o
	gcc -Wall -o main main.o kmp.o
kmp.o:
	gcc -c kmp.c
main.o:
	gcc -c main.c		
clean:
	rm *.o main
