#include <stdio.h>
#include "SqList.h"
#include <stdlib.h>
#include <string.h>

//********************************************************************************************** 
//����:˳���ʾ�����Ա�						
//��������:C����														
//��Ҫ˵��:��ʼΪһ���СΪLIST_INIT_SIZE�Ľṹ������,��������������ı仯���Զ�����,
//		   ÿ����������ΪLISTINCREMENT,������������ΪLIST_INIT_SIZE_MAX,�����ܵ��洢
//		   ����С��Ӱ��,������ĺܶ�ռ�û����ʱ���ͷŵ�,ֻ�������ֿռ�,���Զ�������������
//�汾:��һ�� 
//ʱ��:2019.09.06 
//����:ŷ���� 
//ʹ����֪:����SqList���͵�ָ��֮������ȳ�ʼ��ΪNULL,��: SqList *Oy_List = NULL;
//		   �����Ӱ��ɿ���,���������ʱû�� =NULL,���������ǵ���InitList����
//		   ���ܻᵼ�³������,�������ʱ�� =NULL,��������InitList����Ҳ�������,
//		   ֻ�Ƕ����Ա�Ĳ�����Ч��.
//		   InitList�����Ǳ���Ҫ���õ�,������Լ��ǵõ���InitList����,�򲻱� =NULL; 
//		   ��Ҫ:һ���ǵ�Ҫ����InitList���������� 
//��л:��лʹ�����±�д�Ŀ�,�ļ������������������������,�緢�ִ���,����ָ��,��ϵQQ:1397436824. 
//********************************************************************************************** 


Status InitList(SqList **L)
{//����һ���յ����Ա�L 	
	if(*L) return ERROR;								//�����Ա��Ѿ�����ʼ������					
	(*L) = (SqList *)malloc(sizeof(SqList)); 
	if(!(*L))  return OVERFLOW;
	(*L)->elem = (ElemType *)malloc(LIST_INIT_SIZE*sizeof(ElemType)); 
	if(!(*L)->elem)  return OVERFLOW;
	(*L)->length = 0;
	(*L)->listsize = LIST_INIT_SIZE;
	return OK;
}

Status Destroylist_Sq(SqList **L)
{//�������Ա�*L.
	if(*L) 
	{
		free((*L)->elem);	//�ͷų�Ա�ռ�
		free(*L);			//�ͷ����Ա���Ϣ�ռ�
		*L = NULL;			//��*Lָ��NULL,�������ٵ�����ʹ��
	}
	return OK;
}

Status ClearList_Sq(SqList *L)
{//��L����Ϊ�ձ�
	if(L)	 											//���Ա�L���пռ�(���Ѿ�����ʼ��) 
	{
		//memset(L->elem,0x00,L->length*sizeof(ElemType));
		L->length = 0;
		if(L->listsize>LIST_INIT_SIZE)					//�ͷŴ���LIST_INIT_SIZE�Ŀռ� 
			free(L->elem+LIST_INIT_SIZE);
		L->listsize =LIST_INIT_SIZE;	
	}
	return OK;
}

Status ListEmpty_Sq(SqList *L)
{//���LΪ�ձ�,�򷵻�TRUE,���򷵻�FALSE.
	if(!L) return ERROR;					//L��δ������InitList��ʼ�� 
	if(L->length) return FALSE;					
	else return TRUE;
}

Status ListLength_Sq(SqList *L)
{//�������:����L������Ԫ�ظ���.
	if(!L) return ERROR;					//L��δ������InitList��ʼ�� 
	return L->length;
}

Status GetElem_Sq(SqList *L,int i,ElemType *e)
{//��e����L�е�i������Ԫ�ص�ֵ.
	if(!L->listsize) return ERROR;		//L��δ������InitList��ʼ�� 
	if(i<1||i>L->length) return ERROR;  //���ݲ����� 
	*e = L->elem[i-1];
	return OK;
}

Status PriorElem_Sq(SqList *L,ElemType cur_e,ElemType *pre_e)
{//�������:��cur_e��L������Ԫ��,�Ҳ��ǵ�һ��,����pre_e��������ǰ��,�������ʧ��,pre_e�޶���.
//����ֵ:����OK,���ҵ���ǰ��
//����FALSE,��û���ҵ�ǰ�� 
	unsigned int i=1;
	int ret = 0;
	if(!L) return ERROR;						//L��δ������InitList��ʼ�� 
	if(L->length<=1) 							//���Ա��ܳ���С�ڵ���1 
	{
		pre_e = NULL;
		ret = FALSE;
	}	
	else
	{
		while(compare_struct(&cur_e,&L->elem[i]) && i<=L->length)		//���β��ҵ���cur_e�ĳ�Ա 
			i++;
		if(i<=L->length)
		{
			if(NULL!=pre_e)							//��֤����Ŀɿ���
				*pre_e = L->elem[i-1];				//��pre_e����i��ǰ�� 
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

//����: 
//ͷ��:ListInsert_Sq(&Oy_List,1,e1); 
//β��:ListInsert_Sq(&Oy_List,Oy_List.length+1,e2); 
Status ListInsert_Sq(SqList *L,int i,ElemType e)
{//��L�е�i��λ��֮ǰ�����µ�����Ԫ��e,
 //i�ĺϷ�ֵΪ1<=i<=Listlength_Sq(L)+1
	ElemType *p,*q,*newbase;
	if(!L) return ERROR;									//L��δ����ʼ�� 
	if(i<1||i>L->length+1) return ERROR;					//iֵ���Ϸ�
	if(L->length >= L->listsize && L->listsize <= LIST_INIT_SIZE_MAX-LIST_INIT_SIZE)		//��ǰ�洢�ռ�����,���ӷ���
	{
		newbase = (ElemType *)realloc(L->elem,(L->listsize+LISTINCREMENT)*sizeof(ElemType));
		if(!newbase) return OVERFLOW;						//�洢����ʧ��
		L->elem = newbase;									//�����»�ַ
		L->listsize += LISTINCREMENT;						//���Ӵ洢����
	}
	q = &(L->elem[i-1]);
	for(p = &(L->elem[L->length-1]);p>=q;--p) *(p+1) = *p;//����λ�ü�֮���Ԫ������
	*q = e;
	++L->length;
	return OK;
}

Status ListDelete_Sq(SqList *L,int i,ElemType *e)
{  //ɾ��L�ĵ�i������Ԫ��,����e������ֵ,L�ĳ��ȼ�1.
   //i�ĺϷ�ֵΪ1<=i<=Listlength_Sq(L)
	ElemType *p=NULL,*q=NULL;
	if(!L) return ERROR;							//L��δ������InitList��ʼ�� 
	if(i<1||i>L->length) return ERROR;				//iֵ���� 
	p = &(L->elem[i-1]);							//pΪ��ɾ��Ԫ�ص�λ��
	if(e!=NULL)
		*e = *p;									//��ɾ��Ԫ�ص�ֵ����e
	q = L->elem+L->length-1;						//��βԪ�ص�λ��									
	for(++p;p<=q;++p) *(p-1) = *p;					//��ɾ��֮���Ԫ������
	--L->length;									//����1
	while(L->listsize-L->length>=LIST_INIT_SIZE 
		  && L->listsize>LIST_INIT_SIZE
	      && (L->listsize-L->length)%LIST_IDLE_MAX==0)				
	{//��ˮ,�ռ���Ҫ������ô��,��֤����LIST_INIT_SIZE��С�Ŀ��пռ�<=LIST_IDLE_MAX,�Ա���ռ��˷� 
		free(L->elem+L->listsize-LIST_IDLE_MAX); 				//�ͷŲ���Ҫ�Ŀռ�
		L->listsize -= LIST_IDLE_MAX; 							//�޸Ŀռ�ֵ 
	}
	return OK;
}

int compare_struct(void *com1,void *com2)
{//�Ƚ������ṹ���Ƿ����,
//��ȷ���OK,���ȷ���FALSE. 
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






