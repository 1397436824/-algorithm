#include <stdio.h>
#include <stdlib.h>
#include "Pop.h" 


int main(int argc, char *argv[]) {
	int seq[]={49,38,65,97,76,13,27,49,12,18,348,31864,61,843,8,648};
	int i;
	printf("排序前:");
	for(i=0;i<sizeof(seq)/sizeof(seq[0]);i++)
		printf("%d\t",seq[i]);
	PopSort(seq,sizeof(seq)/sizeof(seq[0]));
	printf("\n排序后:");
	for(i=0;i<sizeof(seq)/sizeof(seq[0]);i++)
	printf("%d\t",seq[i]);
	return 0;
}
