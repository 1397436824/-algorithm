#ifndef _SQLIST_H_
#define _SQLIST_H_

#define OVERFLOW -2   //�ڴ治��
#define ERROR -1	  
#define OK 0		  	
#define FALSE 1
#define TRUE OK

#define Status int			//��������״̬����Ϊ���� 

#define LIST_INIT_SIZE 100	//���Ա�洢�ռ�ĳ�ʼ������
#define LISTINCREMENT 10	//���Ա�洢�ռ�ķ�������
#define LIST_INIT_SIZE_MAX (((unsigned int)(-1)-1)/2)  //�б���󳤶� 
#define LIST_IDLE_MAX 50 	//�������ռ�LIST_INIT_SIZE���������������С 

typedef struct {
	int i;					//�����������޸�
}ElemType;

typedef struct{
	ElemType *elem;			//�洢�ռ��ַ
	int length;				//��ǰ����
	int listsize;			//��ǰ����Ĵ洢����(��sizeof(ElemType)Ϊ��λ)
}SqList;

/*������������*/
Status InitList_Sq(SqList *L);		
	//�������:����һ���յ����Ա�L.
Status Destroylist_Sq(SqList **L);	
	//��ʼ����:���Ա�*L�Ѵ���.
	//�������:�������Ա�*L.
Status ClearList_Sq(SqList *L);
	//��ʼ����:���Ա�L�Ѵ���.
	//�������:��L����Ϊ�ձ�.
Status ListEmpty_Sq(SqList *L);	
	//��ʼ����:���Ա�L�Ѵ���.
	//�������:���LΪ�ձ�,�򷵻�TRUE,���򷵻�FALSE.
Status ListLength_Sq(SqList *L);
	//��ʼ����:���Ա�L�Ѵ���.
	//�������:����L������Ԫ�ظ���.
Status GetElem_Sq(SqList *L,int i,ElemType *e);
	//��ʼ����:���Ա�L�Ѵ���,1<=i<=ListLength(L).
	//�������:��e����L�е�i������Ԫ�ص�ֵ.
//LocateElem_Sq(SqList *L,e,cpmpare());
	//��ʼ����:���Ա�L�Ѵ���,compare()������Ԫ���ж�����.
	//�������:����L�е�1����e�����ϵcompare()������Ԫ�ص�λ��.�������������Ԫ�ز�����,�򷵻�ֵΪ0.
Status PriorElem_Sq(SqList *L,ElemType cur_e,ElemType *pre_e);
	//��ʼ����:���Ա�L�Ѵ���.
	//�������:��cur_e��L������Ԫ��,�Ҳ��ǵ�һ��,����pre_e��������ǰ��,�������ʧ��,pre_e�޶���.
//NextElem_Sq(SqList *L,cur_e,*next_e);
	//��ʼ����:���Ա�L�Ѵ���.
	//�������:��cur_e��L������Ԫ��,�Ҳ������һ��,����next_e�������ĺ��,�������ʧ��,next_e�޶���.	
Status ListInsert_Sq(SqList *L,int i,ElemType e);
	//��ʼ����:���Ա�L�Ѵ���,1<=i<=ListLength(L)+1.
	//�������:��L�е�i��λ��֮ǰ�����µ�����Ԫ��e,L�ĳ��ȼ�1.
Status ListDelete_Sq(SqList *L,int i,ElemType *e);
	//��ʼ����:���Ա�L�Ѵ����ҷǿ�,1<=i<=ListLength(L).
	//�������:ɾ��L�ĵ�i������Ԫ��,����e������ֵ,L�ĳ��ȼ�1.
//ListTraverse_Sq(SqList *L,visit());
	//��ʼ����:���Ա�L�Ѵ���.
	//�������:���ζ�L��ÿ������Ԫ�ص��ú���visit.һ��visit()ʧ��,�����ʧ��.	



#endif




