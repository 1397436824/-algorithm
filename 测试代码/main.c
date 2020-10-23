#include <stdio.h>
#include <stdlib.h>
#include "QuickSort.h" 

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	int seq[]={49,38,65,97,76,13,27,49};
	int i;
	printf("≈≈–Ú«∞:");
	for(i=0;i<sizeof(seq)/sizeof(seq[0]);i++)
	printf("%d\t",seq[i]);
	QuickSort(seq,sizeof(seq)/sizeof(seq[0]));
	printf("\n≈≈–Ú∫Û:");
	for(i=0;i<sizeof(seq)/sizeof(seq[0]);i++)
	printf("%d\t",seq[i]);
	return 0;
}
