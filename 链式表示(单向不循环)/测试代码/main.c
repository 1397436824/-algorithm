#include <stdio.h>
#include <stdlib.h>
#include "linklist.h" 
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int compare(ElemType e1,ElemType e2)
{
	if(e1.i<e2.i) return -1;
	else if(e1.i>e2.i) return 1;
	else return 0;
}

void print(LinkList *OYK)
{
	Link *pa = OYK->head;
	printf("OYK->len = %2d: ",OYK->len);
	while(pa)
	{
		printf("%d\t",pa->data.i);
		pa = pa->next;
	}
	printf("\n"); 
}

int main(int argc, char *argv[]){
	int ret = 0,i = 0;
	LinkList *OYK = NULL;
	LinkList *oyk = NULL,*JIEGUO = NULL;
	ElemType data[10];
	Link *s = NULL;
//	int *a = NULL;
//	int **b = &a;
//	printf("if(*b==NULL) = %d\n",*b);
	ret = InitList(&OYK);
	if(ret) 
		return ret;
	ret = InitList(&oyk);
	if(ret) 
		return ret;
		
	for(i = 0;i<10;i++){
		data[i].i = i+5;
		MakeNode(&s,data[i]);
		Append(OYK,s);
	}
	print(OYK);
	
	for(i = 0;i<10;i++){
		data[i].i = i+3;
		MakeNode(&s,data[i]);
		Append(oyk,s);
	}
	print(oyk);
	
	DelFromHead(OYK,&s);
	FreeNode(&s);
	print(OYK);
	
	MakeNode(&s,data[5]);
	Append(OYK,s);
	print(OYK);

	JIEGUO = MergeList_L(&oyk,&OYK,compare);
	print(JIEGUO);
	
	
	
	
	DestroyList(&OYK);
	DestroyList(&oyk);
	DestroyList(&JIEGUO);
	
	printf("Hello World!\n");
	return 0;
}



