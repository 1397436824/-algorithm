#ifndef _MERGESORT_H_
#define _MERGESORT_H_



typedef int RcdType;

//将有序的SR[i..m]和SR[m+1..n]归并为有序的TR[i..n]
void Merge(RcdType SR[],RcdType TR[],int i,int m,int n);

//将SR[s..t]归并排序为TR1[s..t]
void MSort(RcdType SR[],RcdType TR1[],int s,int t);

//对顺序表L作归并排序
void MergeSort(RcdType L[],int length);
                      



















#endif

