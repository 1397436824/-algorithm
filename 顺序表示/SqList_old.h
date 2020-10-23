#ifndef _SQLIST_H_
#define _SQLIST_H_

#define OVERFLOW -2   //内存不足
#define ERROR -1	  
#define OK 0		  	
#define FALSE 1
#define TRUE OK

typedef int status;			//函数返回状态定义为整型 

#define LIST_INIT_SIZE 100	//线性表存储空间的初始分配量
#define LISTINCREMENT 10	//线性表存储空间的分配增量
#define LIST_INIT_SIZE_MAX (((unsigned int)(-1)-1)/2)

typedef struct {
	int i;					//这里根据情况修改
}ElemType;

typedef struct{
	ElemType *elem;			//存储空间基址
	int length;				//当前长度
	int listsize;			//当前分配的存储容量(以sizeof(ElemType)为单位)
}SqList;

/*函数声明部分*/
status InitList_Sq(SqList *L);		
	//操作结果:构造一个空的线性表L.
status Destroylist_Sq(SqList *L);	
	//初始条件:线性表L已存在.
	//操作结果:销毁线性表L.
status ClearList_Sq(SqList *L);
	//初始条件:线性表L已存在.
	//操作结果:将L重置为空表.
status ListEmpty_Sq(SqList *L);	
	//初始条件:线性表L已存在.
	//操作结果:如果L为空表,则返回TRUE,否则返回FALSE.
status ListLength_Sq(SqList *L);
	//初始条件:线性表L已存在.
	//操作结果:返回L中数据元素个数.
status GetElem_Sq(SqList *L,int i,ElemType *e);
	//初始条件:线性表L已存在,1<=i<=ListLength(L).
	//操作结果:用e返回L中第i个数据元素的值.
//LocateElem_Sq(SqList *L,e,cpmpare());
	//初始条件:线性表L已存在,compare()是数据元素判定函数.
	//操作结果:返回L中第1个与e满足关系compare()的数据元素的位序.如果这样的数据元素不存在,则返回值为0.
status PriorElem_Sq(SqList *L,ElemType cur_e,ElemType *pre_e);
	//初始条件:线性表L已存在.
	//操作结果:若cur_e是L的数据元素,且不是第一个,则用pre_e返回它的前驱,否则操作失败,pre_e无定义.
//NextElem_Sq(SqList *L,cur_e,*next_e);
	//初始条件:线性表L已存在.
	//操作结果:若cur_e是L的数据元素,且不是最后一个,则用next_e返回它的后继,否则操作失败,next_e无定义.	
status ListInsert_Sq(SqList *L,int i,ElemType e);
	//初始条件:线性表L已存在,1<=i<=ListLength(L)+1.
	//操作结果:在L中第i个位置之前插入新的数据元素e,L的长度加1.
status ListDelete_Sq(SqList *L,int i,ElemType *e);
	//初始条件:线性表L已存在且非空,1<=i<=ListLength(L).
	//操作结果:删除L的第i个数据元素,并用e返回其值,L的长度减1.
//ListTraverse_Sq(SqList *L,visit());
	//初始条件:线性表L已存在.
	//操作结果:依次对L的每个数据元素调用函数visit.一旦visit()失败,则操作失败.	



#endif



