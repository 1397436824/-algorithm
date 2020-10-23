#include <stdio.h>
#include <stdlib.h>
#include "linklist.h"

//*******************************************************************************************
//����:����ѭ������
//��������:C����																		
//��Ҫ˵��:
//�汾:��һ�� 
//ʱ��:2019.09.10 
//����:ŷ���� 
//ʹ����֪:
//��л:�ļ������������������������,�緢�ִ���,����ָ��,��ϵQQ:1397436824. 
//*******************************************************************************************

Status InitList(LinkList **L)
{//����һ���յ���������L
	if(*L) return ERROR;						//�����Ա��Ѿ�����ʼ������		
	(*L) = (LinkList *)malloc(sizeof(LinkList));
	if(!(*L))  return OVERFLOW;					//�洢�ռ����ʧ��
	(*L)->len = 0;	
	(*L)->head = NULL;
	(*L)->tail = NULL;
	return OK;
}

Status DestroyList(LinkList **L)
{//������������*L,*L���ٴ���
	Link *pa = NULL;
	if(!(*L)) return ERROR;						//��������
	pa = (*L)->head;							//����ָ��
	while(pa!=NULL)								//����ͷ�������
	{
		(*L)->head = (*L)->head->next;	
		free(pa);
		pa = (*L)->head;
	}
	free((*L));									//�ͷ�ͷ���
	(*L) = NULL;								//��*Lָ��NULL,�������ٵ�����ʹ��
	return OK;
}

Status MakeNode(Link **p,ElemType e)
{//������pָ���ֵΪe�Ľ��,������OK;������ʧ��,�򷵻�ERROR
	(*p) = (Link *)malloc(sizeof(Link));
	if(!(*p)) return OVERFLOW;						//�洢�ռ����ʧ��
	(*p)->data = e;
	(*p)->next = NULL;
	return OK;	
}

void FreeNode(Link **p)
{//�ͷ�p��ָ���	
	if(!(*p)) 
	{
		free(*p);
		(*p) = NULL;							//��*pָ��NULL,���ⱻ�ͷŵĽ���ٴ�ʹ��
	}
}

Status ClearList(LinkList *L)
{//�����Ա�L����Ϊ�ձ�,���ͷ�ԭ����Ľ��ռ�
	Link *Head = NULL,*Next = NULL;				//���帨��ָ��
	if(!L) return ERROR;						//��������
	Head = L->head;			
	while(Head!=NULL)							//����ͷ�������
	{
		Next = Head->next;	
		free(Head);
		Head = Next;
	}
	L->head = NULL;								//�޸�ͷ���headָ��ָ��NULL
	L->tail = NULL;								//�޸�ͷ���tailָ��ָ��NULL
	L->len = 0;									//����������
	return OK;
	
}

Status Append(LinkList *L,Link *s)
{//��ָ��s��ָ(�˴���ָ������)��һ��������������Ա�L�����һ�����
 //֮��,���ı�����L��βָ��ָ���µ�β���	
 	int i = 1;
	if(!L) return ERROR;						//L��������
	if(!s) return OK;							//sΪ��,ʲôҲ����
	if(!L->tail)								//LΪ�ձ� 
		L->head = s;							//�����һ��λ�� 
	else	
		L->tail->next = s;						//��s���ӵ�L��
	while(s->next) 								//��sָ��s�����һ�����
	{
		s = s->next;							
		i++;
	}
	L->tail = s;								//�޸ı�ͷ���tailָ��ָ��s�����һ�����(�µ�β���)
	L->len += i;								//����+i
	return OK;
}

Status Remove(LinkList *L,Link **q)
{//ɾ����������L�е�β��㲢��*q����,�ı�����L��βָ��ָ���µ�β���
 //�ú���ֻ�ǽ�β�����������Ƴ�,��û���ͷ�β���ռ�
	int ret = 0;
	Link *pa = NULL;							//����ָ��
	if(!L) return ERROR;						//L��������
	ret = LocatePos(L,L->len-1,&pa);			//paָ������β����ǰ��
	if(ret)
		return ret;								//LocatePos������������										 	
	*q =  pa->next;								//β�����*q����
	
 	pa->next = NULL;							//ɾ��β���
 	L->tail = pa; 								//�޸�βָ�� 
 	L->len--; 									//����-1
	return 	OK;	
}

Status InsFirst(Link *h,Link *s)
{//��֪hָ�����������ͷ���,��s��ָ�������ڵ�һ�����֮ǰ,ͷ���h֮��
 //�ú�����������ı��ͷ�ṹ���len(����Ԫ�ظ���),Ҳ�޷�ȷ���Ƿ���Ҫ�޸� 
  //βָ��,����һ�㲻������ʹ��
	Link *pa = NULL;
	if(!h||!s) return ERROR;					//hΪNULL��sΪNULL
	pa = h->next;
	h->next = s;
	s->next = pa;
	return OK;
}

Status DelFirst(Link *h,Link **p)
{//��֪hָ�����������ͷ���,ɾ�������еĵ�һ����㲢��*p����
 //�ú���ֻ�ǽ������������Ƴ�,��û���ͷŽ��ռ�
 //�ú�����������ı��ͷ�ṹ���len(����Ԫ�ظ���),Ҳ�޷�ȷ���Ƿ���Ҫ�޸� 
 //βָ��,����һ�㲻������ʹ�� 
	if(!h) return ERROR;						//hΪ��
	if(!h->next)	 							//h֮��û�н��,ֱ�ӷ���
	{
		(*p) = NULL;
		return OK;						
	}
	(*p) = h->next;	
	h->next = h->next->next;	
	(*p)->next = NULL;							//ʹ�ý��������� 
	return OK;
}

Status InsFromHead(LinkList *L,Link *s)
{//��s��ָ�������ڵ�һ�����֮ǰ,��ͷ���L֮��
	if(!L||!s) 	return ERROR;
	s->next = L->head;
	L->head = s;
	if(!L->len)						//ԭ������Ϊ0,��Ҫ�޸�βָ�� 
	 L->tail = s; 
	L->len++;						//����+1 
	return OK;
}

Status DelFromHead(LinkList *L,Link **p)
{//ɾ����ͷ���L֮���һ�����,����*p����
 //�ú���ֻ�ǽ������������Ƴ�,��û���ͷŽ��ռ�
	if(!L) return ERROR;
	(*p) = L->head;	
	if(*p)							//*p->next������ָ(����NULL) 
		L->head = L->head->next;
	else							
		L->head = NULL;				
	(*p)->next = NULL; 				//ʹ�ý���������
	L->len--;						//���ȼ�ȥ1 
	if(!L->len)						//ɾ��֮�󳤶�Ϊ0,��Ҫ�޸�βָ��ָ��NULL 
		L->tail = NULL; 
	return OK;
} 

Status LocatePos(LinkList *L,int i,Link **p)
{//����*pָʾ��������L�еĵ�i������λ�ò�����OK,iֵ���Ϸ�ʱ����ERROR
	int count = 1;
	if(!L||i<0||i>L->len||!(*p)) return ERROR;	//LΪ�ջ�iֵ���Ϸ�����*pΪNULL
	*p = L->head;
	while(count < i)							//whileѭ��ʹpָ���i�����
	{
		*p = (*p)->next;
		count++;
	}
	return OK;
}

Status ListEmpty(LinkList *L)
{//�����Ա�LΪ�ձ�,�򷵻�TRUE,����Ż�FALSE
	if(!L) return ERROR;						//L��������
	if(0==L->len) return TRUE;
	else return FALSE;
}

Position PriorPos(LinkList *L,Link *p)
{//����pָ����������L�е�һ�����,����p��ָ����ֱ��ǰ����λ��,
 //����ǰ�����߲�����������,�򷵻�NULL
	Position ret = NULL;
	if(!L||!p||L->len<=1) return NULL;			//��LΪ��,*pΪ��,p��ָ���û��ǰ������򷵻�NULL
	ret = L->head;						
	while(ret->next!=p && ret->next!=NULL)
		ret = ret->next;				
	if(ret != NULL) 							//ret->next == p
		return ret;								//����ǰ����λ��
	else return NULL;							//δ�ҵ�,����NULL
}

Position NextPos(LinkList *L,Link *p)
{//����pָ����������L�е�һ�����,����p��ָ����ֱ�Ӻ�̵�λ��,
 //���޺�̻��߲�����������,�򷵻�NULL
	Position ret = NULL;
	if(!L||!p||L->len<=1) return NULL;			//��LΪ��,*pΪ��,p��ָ���û�к�̽���򷵻�NULL
	ret = L->head;
	while(ret->next!=p && ret->next!=NULL)
		ret = ret->next;	
	if(ret != NULL) 							//ret->next == p
		return ret->next->next;					//����ǰ����λ��
	else return NULL;							//δ�ҵ�,����NULL
}

Status InsBefore(LinkList *L,Link **p,Link *s)
{//��֪*pָ����������L�е�һ�����,��s��ָ���������*p��ָ���֮ǰ,
 //���޸�ָ��*pָ���²���Ľ��	
	Position pa = NULL;							//����ָ��
	int ret = 0;								//����ֵ
	if(!L||!(*p)||!s||!L->len) return ERROR;	//LΪ��,*pΪ��,sΪ��,Lû�н��.
	pa = PriorPos(L,*p);
	if(!pa) return ERROR;						//��ǰ��,���߲�����������
	*p = s;										//ָ��*pָ���²���Ľ��
	ret = InsFirst(pa,s);						//����s��ָ��㵽*p(ret->next)��ָ���֮��
	if(!ret)									//����ɹ�
	{ 
		if(!L->len)								//ԭ������Ϊ0,��Ҫ�޸�βָ�� 
	 		L->tail = s; 
		L->len++;								//����ɹ�,���ȼ�1 
	}
	return ret;	
}

Status InsAfter(LinkList *L,Link **p,Link *s)
{//��֪*pָ����������L�е�һ�����,��s��ָ���������*p��ָ���֮��,
 //���޸�ָ��*pָ���²���Ľ��			
	Position pa = NULL;							//����ָ��
	int ret = 0;								//����ֵ 
	if(!L||!(*p)||!s||!L->len) return ERROR;	//LΪ��,*pΪ��,sΪ��,Lû�н��
	pa = PriorPos(L,*p);
	if(!pa) return ERROR;						//��ǰ��,���߲�����������
	*p = s;
	ret=InsFirst(pa->next,s);					//����s��ָ��㵽*p(ret->next)��ָ���֮��
	if(!ret)									//����ɹ�		
	{ 
		if(!L->len)								//ԭ������Ϊ0,��Ҫ�޸�βָ�� 
	 		L->tail = s; 
		L->len++;								//����ɹ�,���ȼ�1
	}
	return ret;	
}

Status SetCurElem(Link *p,ElemType e)
{//��֪pָ�����������е�һ�����,��e����p��ָ����ֵ
	if(!p) return ERROR;						//pΪNULL
	p->data = e;								//����
	return OK;
}

ElemType GetCurElem(Link *p)
{//��֪pָ�����������е�һ�����,����p��ָ����е�����Ԫ�ص�ֵ
	ElemType e = {0};
	if(!p) return e;							//pΪNULL
	return p->data;								//ֱ�ӷ���
}

Status ListInsert_L(LinkList *L,int i,ElemType e)
{//�ڴ�ͷ���ĵ������Ա�L�ĵ�i��Ԫ��֮ǰ����Ԫ��e
	Link *h = NULL,*s= NULL;
	int ret = 0;
	if(LocatePos(L,i-1,&h)) return ERROR; 		//iֵ���Ϸ�
	if(MakeNode(&s,e)) return ERROR;			//���洢����ʧ��
	ret = InsFirst(h,s);						//���ڴӵ�i����㿪ʼ������,��i-1�����������ͷ���
	if(!ret)									//����ɹ�			
	{ 
		if(!L->len)								//ԭ������Ϊ0,��Ҫ�޸�βָ�� 
	 		L->tail = s; 
		L->len++;								//����ɹ�,���ȼ�1
	}
	return ret;
}

int ListLength(LinkList *L)
{//������������L��Ԫ�ظ���
	if(!L)	return ERROR;						//L������
	return L->len;								//���ؽ��Ԫ�ظ���
}

Position GetHead(LinkList *L)
{//������������L�е�һ������λ��
	if(!L||!L->len) return NULL;				//LΪNULL����L��û��Ԫ�ؽ��
	return L->head;
}

Position GetLast(LinkList *L)
{//�����������������һ������λ��
	if(!L||!L->len) return NULL;				//LΪNULL����L��û��Ԫ�ؽ��
	return L->tail;
}

Position LocateElem(LinkList *L,ElemType e,Status (*compare)(ElemType,ElemType))
{//������������L�е�1����e���㺯��compare()�ж���ϵ�õ�Ԫ�ص�λ��,
	//��������������Ԫ��,�򷵻�NULL
	Position pa = NULL;	 						//����ָ��
	if(!L||!compare||!L->len) return NULL;		//L�����ڻ�compareΪ�ջ�L��û�н��Ԫ��
	pa = L->head;
	while(compare(e,pa->data) && pa->next!=NULL)
		pa = pa->next;					
	if(!compare(e,pa->data))	
		return pa;								//compare(e,pa->data) == OK
	else 
		return NULL;							//pa->next == NULL
}


LinkList* MergeList_L(LinkList **La,LinkList **Lb,int (*compare)(ElemType,ElemType))
{//��֪�������Ա�*La��*Lb��Ԫ�ذ�ֵ�ǵݼ�����
 //�鲢*La��*Lb�õ��µĵ������Ա�Lc,Lc��Ԫ��Ҳ��ֵ�ǵݼ�����
 //�鲢�ɹ�����LinkList(Lc)ָ��,���򷵻�NULL 
 //�ú����Ὣ*La��*Lb�ͷŵ�,��ʹ��ָ��NULL
	Link *q = NULL,*pa = NULL,*pb = NULL;
	int res = 0;
	ElemType a = {0},b = {0};
	LinkList *Lc = NULL;
	if(InitList(&Lc))	return NULL;		//�洢�ռ����ʧ��
	pa = GetHead((*La));  pb = GetHead((*Lb));		//ha��hb�ֱ�ָ��La��Lb�ĵ�һ��Ԫ�ؽ��
	while(pa&&pb)
	{
		a = GetCurElem(pa); b =GetCurElem(pb);	//a��bΪ�����е�ǰ�Ƚ�Ԫ��
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
		(*La)->head = NULL;					//����ͷ�����Ԫ�ؽ��Ͽ� 
		(*La)->tail = NULL;
		res = Append(Lc,pa);				//����La��ʣ����
		if(res) 
			return NULL;
	}		
	else if(pb)
	{
		(*Lb)->head = NULL;					//����ͷ�����Ԫ�ؽ��Ͽ�
		(*Lb)->tail = NULL;
		res = Append(Lc,pb);				//����Lb��ʣ����
		if(res) 
			return NULL;
	}
	DestroyList(&(*La));					//�ͷ�Laͷ���
	(*La) = NULL;
	DestroyList(&(*Lb));						//�ͷ�Lbͷ���
	(*Lb) = NULL;
	return Lc;  
}



