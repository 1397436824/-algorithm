#include <stdio.h>
#include "Pop.h"



//冒泡排序
//seq:需要排列的数组
//length:需要排序数组的长度(元素个数)
//成功：返回0
//失败：返回-1
int PopSort(int *seq,int length)
{
	int i,j,temp;
	int len = length-2;
	if(seq == NULL) return -1;
	for(i = 0;i <= len;i++)
		for(j = 0;j <= len - i ;j++)
		{
			if(seq[j] > seq[j+1])
			{
				temp = seq[j];
				seq[j] = seq[j+1];
				seq[j+1] = temp;
			}
		}	
	return 0;
}
