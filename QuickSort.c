#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "QuickSort.h"


//********************************************************************************************** 
//内容:二次改进之后的快速排序算法 
//所用语言:C语言																		
//简要说明:该算法在快速排序的基础上添加了对中枢的选取采用了折中,排列过程中加入了冒泡排序
//		   提高了算法的平均性能
//版本:第一版 
//时间:2019.09.05 
//作者:欧阳康 
//使用须知:这个是一个大致的模板,对于数组可以直接使用,对于结构体按关键字排序,需修改部分代码
//鸣谢:感谢使用在下编写的库,文件制作过程中难免会有所错误,如发现错误,请您指正,联系QQ:1397436824.
//********************************************************************************************** 
 
int portion(int *seq,int low,int high,bool *LB,bool *HB)
{
	int mid = seq[low];  		//默认第一个值为中枢值 
	int change;
	int low0=low,high0=high;	//这个初始位置很重要,防止在冒泡中越界 
	if(NULL==seq)return ERROR;
	//判断中枢值是否需要修改,是则修改之,将中枢值与seq[low]交换 
	if(seq[(low+high)/2]>seq[high] && seq[(low+high)/2]<seq[low]||
	   seq[(low+high)/2]>seq[low] && seq[(low+high)/2]<seq[high])
	{
		seq[low] = seq[(low+high)/2];
		seq[(low+high)/2] = mid;
		mid = seq[low];
	}else 
	if(seq[high]>seq[low] && seq[high]<seq[(low+high)/2]|| 
	   seq[high]>seq[(low+high)/2] &&seq[high] <seq[low])
	{
		seq[low] = seq[high];
		seq[high] = mid;
		mid = seq[low];
	}
	while(high>low)
	{
		while(high>low&&seq[high]>=mid) 
		{
			if(high<high0)				//如果不越界则比较 
			if(seq[high]>seq[high+1])	//判断是否需要冒泡 
			{
				*HB = true;
				change = seq[high];
				seq[high] = seq[high+1];
				seq[high+1] = change;
			}	
			high--;	
		} 											
		seq[low] = seq[high];
		while(high>low&&seq[low]<=mid) 
		{
			if(low>low0)				//如果不越界则比较 
			if(seq[low-1]>seq[low])		//判断是否需要冒泡
			{
				*LB = true;				//标记冒泡过 
				change = seq[low];
				seq[low] = seq[low-1];
				seq[low-1] = change;
			}	
			low++;		
		}
		seq[high] = seq[low];
	}
	seq[low] = mid;
	return low;
} 
//seq:需要排序的数组
//low:需要排序数组的最小下标 
//high:需要排序数组的最大下标
void Qsort(int *seq,int low,int high)
{
	int mid;
	int i;
	bool LB=false,HB=false;
	if(NULL==seq) return;
	if(low<high)
	{
		mid =  portion(seq,low,high,&LB,&HB);
		if(LB)								//如果低序列部分冒泡过,则需要对低端子表进行排序 
		{
			Qsort(seq,low,mid-1);
		}
		if(HB)								//如果高序列部分冒泡过,则需要对高端子表进行排序
		{
			Qsort(seq,mid+1,high);
		}
	}
}
//seq:需要排序的数组 
//length:数组长度
//注意:QuickSort函数使用的seq数组下标默认从0到length-1进行排序 
void QuickSort(int *seq,int length)
{
	if(seq!=NULL&&length>1)
		Qsort(seq,0,length-1);	
}
