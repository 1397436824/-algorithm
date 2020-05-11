#ifndef _KMP_H_
#define _KMP_H_

#include <string.h>
#include <stdlib.h>


void get_nextval(char *T,int nextval[]);


//求模板字符串在原字符串中的位置
//S:原字符串
//T:模板字符串
//没找到则返回-1
//找到返回模板字符串在原字符串中的位置
//return: 0 ~ SrcLength-1;
int Index_KMP(char *S,char * T,int pos);











#endif

