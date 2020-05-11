#include "binarysearch.h"


//arr:需要查找的数组
//len:数组的长度
//value:需要在arr中查找的值
//使用前提:arr有序
//使用二分法查找value在数组arr中的位置
//查找到,返回value在数组中的索引
//未查找到,返回-1
//arr为NULL:返回-2
int binary_search(int *arr,int len,int value)
{
	unsigned char order = 0;   	//0,arr递增 1,arr递减
	int left,middle,right;

	if(!arr) 
	{
		printf("arr is NULL\n");
		return -2;
	}

	if(len == 1)
	{
		if(arr[0] == value) return 0;
       		else return -1;	
	}
	
	if(arr[0] > arr[1])		//逆序
		order = 1;
	left = 0;		
	right = len-1;
	
	if(order)			//如果是逆序
	{
		while(left <= right)
		{
			middle = (left +right)/2;
			if(arr[middle] > value)
			{
				left = middle + 1;
			}
			else if(arr[middle] < value) 
			{
				right = middle - 1;
			}
			else return middle;
		}
	}
	else
	{
		while(left <= right)
		{
			middle = (left +right)/2;
			if(arr[middle] > value)
			{
				right = middle - 1;
			}
			else if(arr[middle] < value) 
			{
				left = middle + 1;
			}
			else return middle;
		}
	}
	return -1;
}

