#include <stdio.h>
#include "SelectionSort.h"



//选择排序,从小到大
//seq:需要排列的数组
//length:需要排序数组的长度(元素个数)
//成功：返回0
//失败：返回-1
int SelectionSort(int *seq,int length)
{
	int i,j;
	int len0 = length -1;
	int min;
	if(!seq) return -1;
	if(len0 <= 0) return 0;
	for(j = 0;j < len0 ;j++)
	{
		min = seq[j];
		for(i = j+1;i < length;i++)
		{
			if(seq[i] < min)
			{
				seq[j] = seq[i];
				seq[i] = min;
				min = seq[j];
			}	
		}
	}
	return 0;
}
