#include <stdio.h>

#include "binarysearch.h"



int main(void)
{
	int arr[] = {10,9,8,7,6,5,4,3,2,1};
	int arr1[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,458};
	int value = 7;

	int ret = binary_search(arr,sizeof(arr)/sizeof(arr[0]),value);
	printf("index = %d\n",ret);
	ret = binary_search(arr1,sizeof(arr1)/sizeof(arr1[0]),value);
	printf("index = %d\n",ret);
	return 0;
}
