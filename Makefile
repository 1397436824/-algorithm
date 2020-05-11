binarysearch_test:binarysearch.o binarysearch_test.o
	gcc -Wall -o binarysearch_test binarysearch.o binarysearch_test.o
binarysearch.o:
	gcc -c binarysearch.c
binarysearch_test.o:
	gcc -c binarysearch_test.c 
clean:
	rm *.o
