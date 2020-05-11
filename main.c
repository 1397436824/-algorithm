#include <stdio.h>
#include <stdlib.h>
#include "mergesort.h"




/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	int a[11] = {10,9,8,7,6,5,4,3,2,1,0};
	int i = 0;
	for(i=0;i<11;i++)
	{	
		printf("%d\t",a[i]);
	}	
	printf("\n");
	MergeSort(a,sizeof(a)/sizeof(a[0]));
	for(i=0;i<11;i++)
	{	
		printf("%d\t",a[i]);
	}	
	printf("\n");
	return 0;
}
