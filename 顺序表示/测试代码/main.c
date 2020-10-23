#include <stdio.h>
#include <stdlib.h>
#include "SqList.h"


/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	SqList *Oy_List = NULL;
	int num = 0;
	ElemType e1 = {10},e2={50};
	ElemType pre_e = {0};

	InitList(&Oy_List);
	
	num = ListLength_Sq(Oy_List);
	printf("插入数据前个数为:%d\n",num);

	ListInsert_Sq(Oy_List,1,e1);
	num = ListLength_Sq(Oy_List);
	printf("插入数据后个数为:%d\n",num);
	ListInsert_Sq(Oy_List,Oy_List->length+1,e2);
	num = ListLength_Sq(Oy_List);
	printf("插入数据后个数为:%d\n",num);
	
	num = PriorElem_Sq(Oy_List,e1,&pre_e);
	if(num==OK) printf("pre_e = %d\n",pre_e.i); 
	
	ListDelete_Sq(Oy_List,1,NULL);
	num = ListLength_Sq(Oy_List);
	printf("删除数据后个数为:%d\n",num);
	
	ClearList_Sq(Oy_List);
	num = ListLength_Sq(Oy_List);
	printf("清空数据后个数为:%d\n",num);
	Destroylist_Sq(&Oy_List); 
	printf("Oy_List = %d\n",!Oy_List);
	
	return 0;
}
