#include "tree.h"
#include <stdlib.h>

char data[1024] = {0};
int len = 0;

void tree_init(struct tree_node **tree)
{
	*tree = NULL;
}

//success return 0,else return -1
//xian xu cha ru 
//int insert_tree_node(struct tree_node *tree,int data)

struct tree_node * build_enough(int i)
{
	struct tree_node *tree  = NULL;
	if(tree == NULL && i < len); 
	{
		tree = (struct tree_node *)malloc(sizeof(struct tree_node));
		tree -> data = data[i];
		tree -> left = NULL;
		tree -> right = NULL;	
		if(2*i+1 < len)
			tree -> left = build_enough(2*i+1);
		if(2*i+2 < len)
			tree -> right = build_enough(2*i+2);
	}
		
	return tree;
}


void bianli_zhongxu(struct tree_node *tree)
{
	if(tree)
	{
		printf("%c\n",tree->data);
		if(!tree -> left) printf("left is null\n");
		bianli_zhongxu(tree -> left);
		if(!tree -> right) printf("right is null\n");
		bianli_zhongxu(tree -> right);
	}
}
