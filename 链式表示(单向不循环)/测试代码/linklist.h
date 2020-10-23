#ifndef _LINKLIST_H_
#define _LINKLIST_H_

#define Status int		//函数返回状态定义为整型 

#define OVERFLOW -2   	//内存不足
#define ERROR -1	  
#define OK 0		  	
#define FALSE 1
#define TRUE OK

typedef struct{
	int i;					//这里根据情况修改
}ElemType;

typedef struct LNode{		//链表结点结构体
	ElemType data;
	struct LNode *next;
}Link,*Position;

typedef struct{				//链表头结点结构体
	Link *head,*tail;		//这里根据情况适当添加链表信息
	int len;				//结点元素个数,不包括表头
}LinkList;


Status InitList(LinkList **L);
	//构造一个空的线性链表L
	
Status DestroyList(LinkList **L);
	//销毁线性链表L,L不再存在
	
Status MakeNode(Link **p,ElemType e);
	//分配由p指向的值为e的结点,并返回OK;若分配失败,则返回ERROR
	
void FreeNode(Link **p);	
	//释放p所指结点	
	
Status ClearList(LinkList *L);
	//将线性表L重置为空表,并释放原链表的结点空间
	
Status Append(LinkList *L,Link *s);
	//将指针s所指(彼此以指针相链)的一串结点链接在线性表L的最后一个结点
	//之后,并改变链表L的尾指针指向新的尾结点	
	
Status Remove(LinkList *L,Link **q);
	//删除线性链表L中的尾结点并以*q返回,改变链表L的尾指针指向新的尾结点	
	
Status InsFirst(Link *h,Link *s);
	//已知h指向线性链表的头结点,将s所指结点插入在第一个结点之前,头结点h之后
	//该函数本身并不会改变表头结构体的len(链表元素个数),也无法确定是否需要修改 
	//尾指针,所以一般不允许单独使用
Status DelFirst(Link *h,Link **p);
	//已知h指向线性链表的头结点,删除链表中的第一个结点并以*p返回
	//该函数只是将结点从链表中移除,并没有释放结点空间
	//该函数本身并不会改变表头结构体的len(链表元素个数),也无法确定是否需要修改 
	//尾指针,所以一般不允许单独使用
	
Status InsFromHead(LinkList *L,Link *s);
	//将s所指结点插入在第一个结点之前,表头结点L之后
	
Status DelFromHead(LinkList *L,Link **p);
	//删除表头结点L之后第一个结点,并以*p返回
	//该函数只是将结点从链表中移除,并没有释放结点空间
		
Status LocatePos(LinkList *L,int i,Link **p);
	//返回*p指示线性链表L中的第i个结点的位置并返回OK,i值不合法时返回ERROR
		
Status ListEmpty(LinkList *L);
	//若线性表L为空表,则返回TRUE,否则放回FALSE	
	
Position PriorPos(LinkList *L,Link *p);
	//返回p指向线性链表L中的一个结点,返回p所指结点的直接前驱的位置,
	//若无前驱,或者参数输入有误则返回NULL
	
Position NextPos(LinkList *L,Link *p);	
	//返回p指向线性链表L中的一个结点,返回p所指结点的直接后继的位置,
	//若无后继,或者参数输入有误则返回NULL	
	
Status InsBefore(LinkList *L,Link **p,Link *s);
	//已知*p指向线性链表L中的一个结点,将s所指向结点插入在*p所指结点之前,
	//并修改指针*p指向新插入的结点
Status InsAfter(LinkList *L,Link **p,Link *s);
	//已知*p指向线性链表L中的一个结点,将s所指向结点插入在*p所指结点之后,
	//并修改指针*p指向新插入的结点
	
Status SetCurElem(Link *p,ElemType e);
	//已知p指向线性链表中的一个结点,用e更新p所指结点的值
	
ElemType GetCurElem(Link *p);
	//已知p指向线性链表中的一个结点,返回p所指结点中的数据元素的值
	
Status ListInsert_L(LinkList *L,int i,ElemType e);
	//在带头结点的单链线性表L的第i个元素之前插入元素e	
	
int ListLength(LinkList *L);
	//返回线性链表L中元素个数
	
Position GetHead(LinkList *L);	
	//返回线性链表L中头结点的位置
	
Position GetLast(LinkList *L);
	//返回线性链表中最后一个结点的位置
	
Position LocateElem(LinkList *L,ElemType e,Status (*compare)(ElemType,ElemType));
	//返回线性链表L中第1个与e满足函数compare()判定关系得到元素的位置,
	//若不存在这样的元素,则返回NULL
	
//Status ListTraverse(LinkList *L,Status (*visit)());
	//依次对L的每个元素调用函数visit().一旦visit()失败,则操作失败
	
LinkList* MergeList_L(LinkList **La,LinkList **Lb,int (*compare)(ElemType,ElemType));
 //已知单链线性表*La和*Lb的元素按值非递减排列
 //归并*La和*Lb得到新的单链线性表Lc,Lc的元素也按值非递减排列
 //归并成功返回LinkList(Lc)指针,否则返回NULL 
 //该函数会将*La、*Lb释放掉,并使其指向NULL 
	

#endif

