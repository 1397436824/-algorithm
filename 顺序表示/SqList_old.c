#include <stdio.h>
#include "SqList.h"
#include <stdlib.h>
#include <string.h>

//内容:顺序表示的线性表 
//版本:第一版 
//时间:2019.09.06 
//作者:欧阳康 
//使用须知:定义SqList类型的值之后最好先初始化为0,如: SqList Oy_List = {0};
//		   否则会影响可靠性,即如果定义时没有 ={0},后面又忘记调用InitList函数
//		   可能会导致程序崩溃,如果定义时有 ={0},则忘记用InitList函数也不会崩溃,
//		   只是对线性表的操作无效化.
//		   InitList函数是必须要调用的,且如果自己记得调用InitList函数,则不必 ={0}; 

status GetElem_Sq(SqList *L,int i,ElemType *e)
{//用e返回L中第i个数据元素的值.
	if(!L->listsize) return ERROR;		//L还未被函数InitList初始化 
	if(i<1||i>L->length) return ERROR;  //数据不存在 
	*e = L->elem[i-1];
	return OK;
}

status InitList(SqList *L)
{//构造一个空的线性表L 	
	if(L->listsize) return ERROR;								//该线性表已经被初始化过了					
	L->elem = (ElemType *)malloc(LIST_INIT_SIZE*sizeof(ElemType)); 
	if(!L->elem)  return OVERFLOW;
	L->length = 0;
	L->listsize = LIST_INIT_SIZE;
	return OK;
}

status Destroylist_Sq(SqList *L)
{//销毁线性表L.
	if(L->listsize) free(L->elem);
	L->length = 0;
	L->listsize = 0;
	return OK;
}
//例如: 
//头插:ListInsert_Sq(&Oy_List,1,e1); 
//尾插:ListInsert_Sq(&Oy_List,Oy_List.length+1,e2); 
status ListInsert_Sq(SqList *L,int i,ElemType e)
{//在L中第i个位置之前插入新的数据元素e,
 //i的合法值为1<=i<=Listlength_Sq(L)+1
	ElemType *p,*q,*newbase;
	if(!L->listsize) return ERROR;							//L还未被初始化 
	if(i<1||i>L->length+1) return ERROR;					//i值不合法
	if(L->length >= L->listsize && L->listsize <= LIST_INIT_SIZE_MAX-LIST_INIT_SIZE)		//当前存储空间已满,增加分配
	{
		newbase = (ElemType *)realloc(L->elem,(L->listsize+LISTINCREMENT)*sizeof(ElemType));
		if(!newbase) return OVERFLOW;						//存储分配失败
		L->elem = newbase;									//设置新基址
		L->listsize += LISTINCREMENT;						//增加存储容量
	}
	q = &(L->elem[i-1]);
	for(p = &(L->elem[L->length-1]);p>=q;--p) *(p+1) = *p;//插入位置及之后的元素右移
	*q = e;
	++L->length;
	return OK;
}

status ClearList_Sq(SqList *L)
{//将L重置为空表
	if(L->listsize)					//线性表L已有空间(即已经被初始化) 
	{
		memset(L->elem,0x00,L->length*sizeof(ElemType));
		L->length = 0;
	}
	return OK;
}


status ListEmpty_Sq(SqList *L)
{//如果L为空表,则返回TRUE,否则返回FALSE.
//注意:未被初始化的L也被认为是空表 
	if(L->length) return FALSE;					
	else return TRUE;
}

status ListLength_Sq(SqList *L)
{//操作结果:返回L中数据元素个数.
	if(!L->listsize) return ERROR;					//L还未被函数InitList初始化 
	return L->length;
}

status ListDelete_Sq(SqList *L,int i,ElemType *e)
{  //删除L的第i个数据元素,并用e返回其值,L的长度减1.
   //i的合法值为1<=i<=Listlength_Sq(L)
	ElemType *p=NULL,*q=NULL;
	if(!L->listsize) return ERROR;					//L还未被函数InitList初始化 
	if(i<1||i>L->length) return ERROR;				//i值错误 
	p = &(L->elem[i-1]);							//p为被删除元素的位置
	if(e!=NULL)
		*e = *p;									//被删除元素的值赋给e
	q = L->elem+L->length-1;						//表尾元素的位置									
	for(++p;p<=q;++p) *(p-1) = *p;					//被删除之后的元素左移
	--L->length;									//表长减1
	return OK;
}

int compare_struct(void *com1,void *com2)
{//比较两个结构体是否相等,
//相等返回OK,不等返回FALSE. 
	char *one_s,*two_s;
	int i = 0;
	one_s = (char *)com1;
	two_s = (char *)com2;
	for(i=0;i<sizeof(*com1);i++)
	{
		if(one_s[i]!=two_s[i]) break;
	}
	if(sizeof(*com1)==i) return OK;
	else return FALSE;
}

status PriorElem_Sq(SqList *L,ElemType cur_e,ElemType *pre_e)
{//操作结果:若cur_e是L的数据元素,且不是第一个,则用pre_e返回它的前驱,否则操作失败,pre_e无定义.
//返回值:返回OK，则找到了前驱
//返回FALSE,则没有找到前驱 
	unsigned int i=1;
	int ret = 0;
	if(!L->listsize) return ERROR;					//L还未被函数InitList初始化 
	if(L->length<=1) 								//线性表总长度小于等于1 
	{
		pre_e = NULL;
		ret = FALSE;
	}	
	else
	{
		while(compare_struct(&cur_e,&L->elem[i]) && i<=L->length)		//依次查找等于cur_e的成员 
			i++;
		if(i<=L->length)
		{
			*pre_e = L->elem[i-1];				//用pre_e返回i的前驱 
			ret = OK;
		}	
		else 
		{
			pre_e = NULL;
			ret = FALSE;
		}
	}
	return ret;		
}



