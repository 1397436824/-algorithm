#include "kmp.h"

//求next函数值,KMP算法是在next函数值的基础上进行的 
void get_nextval(char *T,int nextval[])
{
	int i = 1;
	int j = 0;
	int len = strlen(T);
	T = T - 1;
	nextval[1] = 0;	
	while(i < len){
		if(j == 0 || T[i] == T[j])
		{
			++i;
			++j;			
			if(T[i] != T[j]) nextval[i] = j;
			else nextval[i] = nextval[j];		
		}
		else j = nextval[j];
	}
}


//求模板字符串在原字符串中的位置
//S:原字符串
//T:模板字符串
//没找到则返回-1
//找到返回模板字符串在原字符串中的位置
//return: 0 ~ SrcLength-1;
int Index_KMP(char *S,char *T,int pos)
{
	int i = pos+1;
	int j = 1;
	int Slen = 0;
	int Tlen = 0;
	int *nextval;
	Slen = strlen(S);
	Tlen = strlen(T);

	nextval = (int *)malloc((Tlen+1)*sizeof(int));

	get_nextval(T,nextval);
	
	S = S - 1; 
	T = T - 1;
	while(i <= Slen && j <= Tlen){
		if(j == 0 || S[i] == T[j])
		{
			++i; 
			++j;	
		}
		else j = nextval[j];		
	}
	free(nextval);
	if(j > Tlen) return i-Tlen-1;
	else return -1; 
}

























