#include "tree.h"
#include <string.h>


extern int len;
extern char data[1024];

int main()
{
	int deep = 0;
	struct tree_node *p;
	printf("please input:");
	scanf("%s",data);
	printf("data = %s\n",data);
	len = strlen(data);
	printf("len = %d\n",len);
	p = build_enough(0);
//	bianli_zhongxu(p);
	deep = explore_deep(p);
	printf("deep = %d\n",deep);
	return 0;
}
