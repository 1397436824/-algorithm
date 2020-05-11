#include "mergesort.h"
#include <string.h>


void MSort(RcdType SR[],RcdType TR1[],int s,int t);


//将有序的SR[i..m]和SR[m+1..n]归并为有序的TR[i..n]
void Merge(RcdType SR[],RcdType TR[],int i,int m,int n)
{
	int j=0,k=0; 
	for(j=m+1,k=i;i<=m&&j<=n;k++)
	{
		if(SR[i]<SR[j])
			TR[k] = SR[i++];	
		else
			TR[k] = SR[j++];	
	}
	if(i<=m)
	{		
		for(;i<=m;i++)
		{	
			TR[k++] = SR[i]; 
		}				
	}	
	else if(j<=n) 
	{	
		for(;j<=n;j++)
		{	
			TR[k++] = SR[j]; 
		}
	}	
}	
	
//将SR[s..t]归并排序为TR1[s..t]
void MSort(RcdType SR[],RcdType TR1[],int s,int t)
{
	int m = 0;
	const int temp = t+1;
	RcdType TR2[temp];
	//memset(TR2,0x00,sizeof(RcdType)); 
	if(s==t) TR1[t] = SR[t];
	else
	{
		m = (s+t)/2;
		MSort(SR,TR2,s,m);	
		MSort(SR,TR2,m+1,t);
		Merge(TR2,TR1,s,m,t);	
	}
} 
 
//对顺序表L作归并排序
void MergeSort(RcdType L[],int length)
{
	MSort(L,L,0,length-1);
}








