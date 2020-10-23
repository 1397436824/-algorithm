#ifndef _LINKLIST_H_
#define _LINKLIST_H_

#define Status int		//��������״̬����Ϊ���� 

#define OVERFLOW -2   	//�ڴ治��
#define ERROR -1	  
#define OK 0		  	
#define FALSE 1
#define TRUE OK

typedef struct{
	int i;					//�����������޸�
}ElemType;

typedef struct LNode{		//������ṹ��
	ElemType data;
	struct LNode *next;
}Link,*Position;

typedef struct{				//����ͷ���ṹ��
	Link *head,*tail;		//�����������ʵ����������Ϣ
	int len;				//���Ԫ�ظ���,��������ͷ
}LinkList;


Status InitList(LinkList **L);
	//����һ���յ���������L
	
Status DestroyList(LinkList **L);
	//������������L,L���ٴ���
	
Status MakeNode(Link **p,ElemType e);
	//������pָ���ֵΪe�Ľ��,������OK;������ʧ��,�򷵻�ERROR
	
void FreeNode(Link **p);	
	//�ͷ�p��ָ���	
	
Status ClearList(LinkList *L);
	//�����Ա�L����Ϊ�ձ�,���ͷ�ԭ����Ľ��ռ�
	
Status Append(LinkList *L,Link *s);
	//��ָ��s��ָ(�˴���ָ������)��һ��������������Ա�L�����һ�����
	//֮��,���ı�����L��βָ��ָ���µ�β���	
	
Status Remove(LinkList *L,Link **q);
	//ɾ����������L�е�β��㲢��*q����,�ı�����L��βָ��ָ���µ�β���	
	
Status InsFirst(Link *h,Link *s);
	//��֪hָ�����������ͷ���,��s��ָ�������ڵ�һ�����֮ǰ,ͷ���h֮��
	//�ú�����������ı��ͷ�ṹ���len(����Ԫ�ظ���),Ҳ�޷�ȷ���Ƿ���Ҫ�޸� 
	//βָ��,����һ�㲻������ʹ��
Status DelFirst(Link *h,Link **p);
	//��֪hָ�����������ͷ���,ɾ�������еĵ�һ����㲢��*p����
	//�ú���ֻ�ǽ������������Ƴ�,��û���ͷŽ��ռ�
	//�ú�����������ı��ͷ�ṹ���len(����Ԫ�ظ���),Ҳ�޷�ȷ���Ƿ���Ҫ�޸� 
	//βָ��,����һ�㲻������ʹ��
	
Status InsFromHead(LinkList *L,Link *s);
	//��s��ָ�������ڵ�һ�����֮ǰ,��ͷ���L֮��
	
Status DelFromHead(LinkList *L,Link **p);
	//ɾ����ͷ���L֮���һ�����,����*p����
	//�ú���ֻ�ǽ������������Ƴ�,��û���ͷŽ��ռ�
		
Status LocatePos(LinkList *L,int i,Link **p);
	//����*pָʾ��������L�еĵ�i������λ�ò�����OK,iֵ���Ϸ�ʱ����ERROR
		
Status ListEmpty(LinkList *L);
	//�����Ա�LΪ�ձ�,�򷵻�TRUE,����Ż�FALSE	
	
Position PriorPos(LinkList *L,Link *p);
	//����pָ����������L�е�һ�����,����p��ָ����ֱ��ǰ����λ��,
	//����ǰ��,���߲������������򷵻�NULL
	
Position NextPos(LinkList *L,Link *p);	
	//����pָ����������L�е�һ�����,����p��ָ����ֱ�Ӻ�̵�λ��,
	//���޺��,���߲������������򷵻�NULL	
	
Status InsBefore(LinkList *L,Link **p,Link *s);
	//��֪*pָ����������L�е�һ�����,��s��ָ���������*p��ָ���֮ǰ,
	//���޸�ָ��*pָ���²���Ľ��
Status InsAfter(LinkList *L,Link **p,Link *s);
	//��֪*pָ����������L�е�һ�����,��s��ָ���������*p��ָ���֮��,
	//���޸�ָ��*pָ���²���Ľ��
	
Status SetCurElem(Link *p,ElemType e);
	//��֪pָ�����������е�һ�����,��e����p��ָ����ֵ
	
ElemType GetCurElem(Link *p);
	//��֪pָ�����������е�һ�����,����p��ָ����е�����Ԫ�ص�ֵ
	
Status ListInsert_L(LinkList *L,int i,ElemType e);
	//�ڴ�ͷ���ĵ������Ա�L�ĵ�i��Ԫ��֮ǰ����Ԫ��e	
	
int ListLength(LinkList *L);
	//������������L��Ԫ�ظ���
	
Position GetHead(LinkList *L);	
	//������������L��ͷ����λ��
	
Position GetLast(LinkList *L);
	//�����������������һ������λ��
	
Position LocateElem(LinkList *L,ElemType e,Status (*compare)(ElemType,ElemType));
	//������������L�е�1����e���㺯��compare()�ж���ϵ�õ�Ԫ�ص�λ��,
	//��������������Ԫ��,�򷵻�NULL
	
//Status ListTraverse(LinkList *L,Status (*visit)());
	//���ζ�L��ÿ��Ԫ�ص��ú���visit().һ��visit()ʧ��,�����ʧ��
	
LinkList* MergeList_L(LinkList **La,LinkList **Lb,int (*compare)(ElemType,ElemType));
 //��֪�������Ա�*La��*Lb��Ԫ�ذ�ֵ�ǵݼ�����
 //�鲢*La��*Lb�õ��µĵ������Ա�Lc,Lc��Ԫ��Ҳ��ֵ�ǵݼ�����
 //�鲢�ɹ�����LinkList(Lc)ָ��,���򷵻�NULL 
 //�ú����Ὣ*La��*Lb�ͷŵ�,��ʹ��ָ��NULL 
	

#endif

