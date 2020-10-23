#include <stdio.h>
#include "SqList.h"
#include <stdlib.h>
#include <string.h>

//********************************************************************************************** 
//内容:顺序表示的线性表						
//所用语言:C语言														
//简要说明:初始为一组大小为LIST_INIT_SIZE的结构体数组,数组会随着容量的变化而自动增长,
//		   每次增长幅度为LISTINCREMENT,数组的最大容量为LIST_INIT_SIZE_MAX,并且受到存储
//		   器大小的影响,当数组的很多空间没在用时会释放掉,只保留部分空间,即自动增长和收缩。
//版本:第一版 
//时间:2019.09.06 
//作者:欧阳康 
//使用须知:定义SqList类型的指针之后最好先初始化为NULL,如: SqList *Oy_List = NULL;
//		   否则会影响可靠性,即如果定义时没有 =NULL,后面又忘记调用InitList函数
//		   可能会导致程序崩溃,如果定义时有 =NULL,则忘记用InitList函数也不会崩溃,
//		   只是对线性表的操作无效化.
//		   InitList函数是必须要调用的,且如果自己记得调用InitList函数,则不必 =NULL; 
//		   重要:一定记得要调用InitList函数！！！ 
//鸣谢:感谢使用在下编写的库,文件制作过程中难免会有所错误,如发现错误,请您指正,联系QQ:1397436824. 
//********************************************************************************************** 


Status InitList(SqList **L)
{//构造一个空的线性表L 	
	if(*L) return ERROR;								//该线性表已经被初始化过了					
	(*L) = (SqList *)malloc(sizeof(SqList)); 
	if(!(*L))  return OVERFLOW;
	(*L)->elem = (ElemType *)malloc(LIST_INIT_SIZE*sizeof(ElemType)); 
	if(!(*L)->elem)  return OVERFLOW;
	(*L)->length = 0;
	(*L)->listsize = LIST_INIT_SIZE;
	return OK;
}

Status Destroylist_Sq(SqList **L)
{//销毁线性表*L.
	if(*L) 
	{
		free((*L)->elem);	//释放成员空间
		free(*L);			//释放线性表信息空间
		*L = NULL;			//将*L指向NULL,避免销毁的链表被使用
	}
	return OK;
}

Status ClearList_Sq(SqList *L)
{//将L重置为空表
	if(L)	 											//线性表L已有空间(即已经被初始化) 
	{
		//memset(L->elem,0x00,L->length*sizeof(ElemType));
		L->length = 0;
		if(L->listsize>LIST_INIT_SIZE)					//释放大于LIST_INIT_SIZE的空间 
			free(L->elem+LIST_INIT_SIZE);
		L->listsize =LIST_INIT_SIZE;	
	}
	return OK;
}

Status ListEmpty_Sq(SqList *L)
{//如果L为空表,则返回TRUE,否则返回FALSE.
	if(!L) return ERROR;					//L还未被函数InitList初始化 
	if(L->length) return FALSE;					
	else return TRUE;
}

Status ListLength_Sq(SqList *L)
{//操作结果:返回L中数据元素个数.
	if(!L) return ERROR;					//L还未被函数InitList初始化 
	return L->length;
}

Status GetElem_Sq(SqList *L,int i,ElemType *e)
{//用e返回L中第i个数据元素的值.
	if(!L->listsize) return ERROR;		//L还未被函数InitList初始化 
	if(i<1||i>L->length) return ERROR;  //数据不存在 
	*e = L->elem[i-1];
	return OK;
}

Status PriorElem_Sq(SqList *L,ElemType cur_e,ElemType *pre_e)
{//操作结果:若cur_e是L的数据元素,且不是第一个,则用pre_e返回它的前驱,否则操作失败,pre_e无定义.
//返回值:返回OK,则找到了前驱
//返回FALSE,则没有找到前驱 
	unsigned int i=1;
	int ret = 0;
	if(!L) return ERROR;						//L还未被函数InitList初始化 
	if(L->length<=1) 							//线性表总长度小于等于1 
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
			if(NULL!=pre_e)							//保证程序的可靠性
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

//例如: 
//头插:ListInsert_Sq(&Oy_List,1,e1); 
//尾插:ListInsert_Sq(&Oy_List,Oy_List.length+1,e2); 
Status ListInsert_Sq(SqList *L,int i,ElemType e)
{//在L中第i个位置之前插入新的数据元素e,
 //i的合法值为1<=i<=Listlength_Sq(L)+1
	ElemType *p,*q,*newbase;
	if(!L) return ERROR;									//L还未被初始化 
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

Status ListDelete_Sq(SqList *L,int i,ElemType *e)
{  //删除L的第i个数据元素,并用e返回其值,L的长度减1.
   //i的合法值为1<=i<=Listlength_Sq(L)
	ElemType *p=NULL,*q=NULL;
	if(!L) return ERROR;							//L还未被函数InitList初始化 
	if(i<1||i>L->length) return ERROR;				//i值错误 
	p = &(L->elem[i-1]);							//p为被删除元素的位置
	if(e!=NULL)
		*e = *p;									//被删除元素的值赋给e
	q = L->elem+L->length-1;						//表尾元素的位置									
	for(++p;p<=q;++p) *(p-1) = *p;					//被删除之后的元素左移
	--L->length;									//表长减1
	while(L->listsize-L->length>=LIST_INIT_SIZE 
		  && L->listsize>LIST_INIT_SIZE
	      && (L->listsize-L->length)%LIST_IDLE_MAX==0)				
	{//缩水,空间需要不在那么大,保证超过LIST_INIT_SIZE大小的空闲空间<=LIST_IDLE_MAX,以避免空间浪费 
		free(L->elem+L->listsize-LIST_IDLE_MAX); 				//释放不需要的空间
		L->listsize -= LIST_IDLE_MAX; 							//修改空间值 
	}
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






