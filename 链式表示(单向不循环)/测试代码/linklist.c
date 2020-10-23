#include <stdio.h>
#include <stdlib.h>
#include "linklist.h"

//*******************************************************************************************
//内容:单向不循环链表
//所用语言:C语言																		
//简要说明:
//版本:第一版 
//时间:2019.09.10 
//作者:欧阳康 
//使用须知:
//鸣谢:文件制作过程中难免会有所错误,如发现错误,请您指正,联系QQ:1397436824. 
//*******************************************************************************************

Status InitList(LinkList **L)
{//构造一个空的线性链表L
	if(*L) return ERROR;						//该线性表已经被初始化过了		
	(*L) = (LinkList *)malloc(sizeof(LinkList));
	if(!(*L))  return OVERFLOW;					//存储空间分配失败
	(*L)->len = 0;	
	(*L)->head = NULL;
	(*L)->tail = NULL;
	return OK;
}

Status DestroyList(LinkList **L)
{//销毁线性链表*L,*L不再存在
	Link *pa = NULL;
	if(!(*L)) return ERROR;						//链表不存在
	pa = (*L)->head;							//辅助指针
	while(pa!=NULL)								//逐个释放链表结点
	{
		(*L)->head = (*L)->head->next;	
		free(pa);
		pa = (*L)->head;
	}
	free((*L));									//释放头结点
	(*L) = NULL;								//将*L指向NULL,避免销毁的链表被使用
	return OK;
}

Status MakeNode(Link **p,ElemType e)
{//分配由p指向的值为e的结点,并返回OK;若分配失败,则返回ERROR
	(*p) = (Link *)malloc(sizeof(Link));
	if(!(*p)) return OVERFLOW;						//存储空间分配失败
	(*p)->data = e;
	(*p)->next = NULL;
	return OK;	
}

void FreeNode(Link **p)
{//释放p所指结点	
	if(!(*p)) 
	{
		free(*p);
		(*p) = NULL;							//将*p指向NULL,避免被释放的结点再次使用
	}
}

Status ClearList(LinkList *L)
{//将线性表L重置为空表,并释放原链表的结点空间
	Link *Head = NULL,*Next = NULL;				//定义辅助指针
	if(!L) return ERROR;						//链表不存在
	Head = L->head;			
	while(Head!=NULL)							//逐个释放链表结点
	{
		Next = Head->next;	
		free(Head);
		Head = Next;
	}
	L->head = NULL;								//修改头结点head指针指向NULL
	L->tail = NULL;								//修改头结点tail指针指向NULL
	L->len = 0;									//链表长度清零
	return OK;
	
}

Status Append(LinkList *L,Link *s)
{//将指针s所指(彼此以指针相链)的一串结点链接在线性表L的最后一个结点
 //之后,并改变链表L的尾指针指向新的尾结点	
 	int i = 1;
	if(!L) return ERROR;						//L链表不存在
	if(!s) return OK;							//s为空,什么也不做
	if(!L->tail)								//L为空表 
		L->head = s;							//插入第一个位置 
	else	
		L->tail->next = s;						//将s链接到L中
	while(s->next) 								//将s指向s的最后一个结点
	{
		s = s->next;							
		i++;
	}
	L->tail = s;								//修改表头结点tail指针指向s的最后一个结点(新的尾结点)
	L->len += i;								//长度+i
	return OK;
}

Status Remove(LinkList *L,Link **q)
{//删除线性链表L中的尾结点并以*q返回,改变链表L的尾指针指向新的尾结点
 //该函数只是将尾结点从链表中移除,并没有释放尾结点空间
	int ret = 0;
	Link *pa = NULL;							//辅助指针
	if(!L) return ERROR;						//L链表不存在
	ret = LocatePos(L,L->len-1,&pa);			//pa指向链表尾结点的前驱
	if(ret)
		return ret;								//LocatePos函数参数有误										 	
	*q =  pa->next;								//尾结点以*q返回
	
 	pa->next = NULL;							//删除尾结点
 	L->tail = pa; 								//修改尾指针 
 	L->len--; 									//长度-1
	return 	OK;	
}

Status InsFirst(Link *h,Link *s)
{//已知h指向线性链表的头结点,将s所指结点插入在第一个结点之前,头结点h之后
 //该函数本身并不会改变表头结构体的len(链表元素个数),也无法确定是否需要修改 
  //尾指针,所以一般不允许单独使用
	Link *pa = NULL;
	if(!h||!s) return ERROR;					//h为NULL或s为NULL
	pa = h->next;
	h->next = s;
	s->next = pa;
	return OK;
}

Status DelFirst(Link *h,Link **p)
{//已知h指向线性链表的头结点,删除链表中的第一个结点并以*p返回
 //该函数只是将结点从链表中移除,并没有释放结点空间
 //该函数本身并不会改变表头结构体的len(链表元素个数),也无法确定是否需要修改 
 //尾指针,所以一般不允许单独使用 
	if(!h) return ERROR;						//h为空
	if(!h->next)	 							//h之后没有结点,直接返回
	{
		(*p) = NULL;
		return OK;						
	}
	(*p) = h->next;	
	h->next = h->next->next;	
	(*p)->next = NULL;							//使该结点独立出来 
	return OK;
}

Status InsFromHead(LinkList *L,Link *s)
{//将s所指结点插入在第一个结点之前,表头结点L之后
	if(!L||!s) 	return ERROR;
	s->next = L->head;
	L->head = s;
	if(!L->len)						//原来长度为0,需要修改尾指针 
	 L->tail = s; 
	L->len++;						//长度+1 
	return OK;
}

Status DelFromHead(LinkList *L,Link **p)
{//删除表头结点L之后第一个结点,并以*p返回
 //该函数只是将结点从链表中移除,并没有释放结点空间
	if(!L) return ERROR;
	(*p) = L->head;	
	if(*p)							//*p->next还有所指(包括NULL) 
		L->head = L->head->next;
	else							
		L->head = NULL;				
	(*p)->next = NULL; 				//使该结点独立出来
	L->len--;						//长度减去1 
	if(!L->len)						//删除之后长度为0,需要修改尾指针指向NULL 
		L->tail = NULL; 
	return OK;
} 

Status LocatePos(LinkList *L,int i,Link **p)
{//返回*p指示线性链表L中的第i个结点的位置并返回OK,i值不合法时返回ERROR
	int count = 1;
	if(!L||i<0||i>L->len||!(*p)) return ERROR;	//L为空或i值不合法或者*p为NULL
	*p = L->head;
	while(count < i)							//while循环使p指向第i个结点
	{
		*p = (*p)->next;
		count++;
	}
	return OK;
}

Status ListEmpty(LinkList *L)
{//若线性表L为空表,则返回TRUE,否则放回FALSE
	if(!L) return ERROR;						//L链表不存在
	if(0==L->len) return TRUE;
	else return FALSE;
}

Position PriorPos(LinkList *L,Link *p)
{//返回p指向线性链表L中的一个结点,返回p所指结点的直接前驱的位置,
 //若无前驱或者参数输入有误,则返回NULL
	Position ret = NULL;
	if(!L||!p||L->len<=1) return NULL;			//若L为空,*p为空,p所指结点没有前驱结点则返回NULL
	ret = L->head;						
	while(ret->next!=p && ret->next!=NULL)
		ret = ret->next;				
	if(ret != NULL) 							//ret->next == p
		return ret;								//返回前驱的位置
	else return NULL;							//未找到,返回NULL
}

Position NextPos(LinkList *L,Link *p)
{//返回p指向线性链表L中的一个结点,返回p所指结点的直接后继的位置,
 //若无后继或者参数输入有误,则返回NULL
	Position ret = NULL;
	if(!L||!p||L->len<=1) return NULL;			//若L为空,*p为空,p所指结点没有后继结点则返回NULL
	ret = L->head;
	while(ret->next!=p && ret->next!=NULL)
		ret = ret->next;	
	if(ret != NULL) 							//ret->next == p
		return ret->next->next;					//返回前驱的位置
	else return NULL;							//未找到,返回NULL
}

Status InsBefore(LinkList *L,Link **p,Link *s)
{//已知*p指向线性链表L中的一个结点,将s所指向结点插入在*p所指结点之前,
 //并修改指针*p指向新插入的结点	
	Position pa = NULL;							//辅助指针
	int ret = 0;								//返回值
	if(!L||!(*p)||!s||!L->len) return ERROR;	//L为空,*p为空,s为空,L没有结点.
	pa = PriorPos(L,*p);
	if(!pa) return ERROR;						//无前驱,或者参数输入有误
	*p = s;										//指针*p指向新插入的结点
	ret = InsFirst(pa,s);						//插入s所指结点到*p(ret->next)所指结点之后
	if(!ret)									//插入成功
	{ 
		if(!L->len)								//原来长度为0,需要修改尾指针 
	 		L->tail = s; 
		L->len++;								//插入成功,长度加1 
	}
	return ret;	
}

Status InsAfter(LinkList *L,Link **p,Link *s)
{//已知*p指向线性链表L中的一个结点,将s所指向结点插入在*p所指结点之后,
 //并修改指针*p指向新插入的结点			
	Position pa = NULL;							//辅助指针
	int ret = 0;								//返回值 
	if(!L||!(*p)||!s||!L->len) return ERROR;	//L为空,*p为空,s为空,L没有结点
	pa = PriorPos(L,*p);
	if(!pa) return ERROR;						//无前驱,或者参数输入有误
	*p = s;
	ret=InsFirst(pa->next,s);					//插入s所指结点到*p(ret->next)所指结点之后
	if(!ret)									//插入成功		
	{ 
		if(!L->len)								//原来长度为0,需要修改尾指针 
	 		L->tail = s; 
		L->len++;								//插入成功,长度加1
	}
	return ret;	
}

Status SetCurElem(Link *p,ElemType e)
{//已知p指向线性链表中的一个结点,用e更新p所指结点的值
	if(!p) return ERROR;						//p为NULL
	p->data = e;								//更新
	return OK;
}

ElemType GetCurElem(Link *p)
{//已知p指向线性链表中的一个结点,返回p所指结点中的数据元素的值
	ElemType e = {0};
	if(!p) return e;							//p为NULL
	return p->data;								//直接返回
}

Status ListInsert_L(LinkList *L,int i,ElemType e)
{//在带头结点的单链线性表L的第i个元素之前插入元素e
	Link *h = NULL,*s= NULL;
	int ret = 0;
	if(LocatePos(L,i-1,&h)) return ERROR; 		//i值不合法
	if(MakeNode(&s,e)) return ERROR;			//结点存储分配失败
	ret = InsFirst(h,s);						//对于从第i个结点开始的链表,第i-1个结点是它的头结点
	if(!ret)									//插入成功			
	{ 
		if(!L->len)								//原来长度为0,需要修改尾指针 
	 		L->tail = s; 
		L->len++;								//插入成功,长度加1
	}
	return ret;
}

int ListLength(LinkList *L)
{//返回线性链表L中元素个数
	if(!L)	return ERROR;						//L不存在
	return L->len;								//返回结点元素个数
}

Position GetHead(LinkList *L)
{//返回线性链表L中第一个结点的位置
	if(!L||!L->len) return NULL;				//L为NULL或者L链没有元素结点
	return L->head;
}

Position GetLast(LinkList *L)
{//返回线性链表中最后一个结点的位置
	if(!L||!L->len) return NULL;				//L为NULL或者L链没有元素结点
	return L->tail;
}

Position LocateElem(LinkList *L,ElemType e,Status (*compare)(ElemType,ElemType))
{//返回线性链表L中第1个与e满足函数compare()判定关系得到元素的位置,
	//若不存在这样的元素,则返回NULL
	Position pa = NULL;	 						//辅助指针
	if(!L||!compare||!L->len) return NULL;		//L不存在或compare为空或L中没有结点元素
	pa = L->head;
	while(compare(e,pa->data) && pa->next!=NULL)
		pa = pa->next;					
	if(!compare(e,pa->data))	
		return pa;								//compare(e,pa->data) == OK
	else 
		return NULL;							//pa->next == NULL
}


LinkList* MergeList_L(LinkList **La,LinkList **Lb,int (*compare)(ElemType,ElemType))
{//已知单链线性表*La和*Lb的元素按值非递减排列
 //归并*La和*Lb得到新的单链线性表Lc,Lc的元素也按值非递减排列
 //归并成功返回LinkList(Lc)指针,否则返回NULL 
 //该函数会将*La、*Lb释放掉,并使其指向NULL
	Link *q = NULL,*pa = NULL,*pb = NULL;
	int res = 0;
	ElemType a = {0},b = {0};
	LinkList *Lc = NULL;
	if(InitList(&Lc))	return NULL;		//存储空间分配失败
	pa = GetHead((*La));  pb = GetHead((*Lb));		//ha和hb分别指向La和Lb的第一个元素结点
	while(pa&&pb)
	{
		a = GetCurElem(pa); b =GetCurElem(pb);	//a和b为两表中当前比较元素
		if((*compare)(a,b) <= 0)
		{
			if(res = DelFromHead((*La),&q))
				return NULL;
			if(res = Append(Lc,q))
				return NULL;
			pa = GetHead((*La));
		}
		else 
		{
			if(res = DelFromHead((*Lb),&q))
				return NULL;
			if(res = Append(Lc,q))
				return NULL;
			pb = GetHead((*Lb));
		}
	}
	if(pa) 
	{
		(*La)->head = NULL;					//将表头结点与元素结点断开 
		(*La)->tail = NULL;
		res = Append(Lc,pa);				//链接La中剩余结点
		if(res) 
			return NULL;
	}		
	else if(pb)
	{
		(*Lb)->head = NULL;					//将表头结点与元素结点断开
		(*Lb)->tail = NULL;
		res = Append(Lc,pb);				//链接Lb中剩余结点
		if(res) 
			return NULL;
	}
	DestroyList(&(*La));					//释放La头结点
	(*La) = NULL;
	DestroyList(&(*Lb));						//释放Lb头结点
	(*Lb) = NULL;
	return Lc;  
}



