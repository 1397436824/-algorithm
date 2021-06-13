#ifndef _TREE_H_
#define _TREE_H_

#include <stdio.h>







struct tree_node
{
	struct tree_node *left;
	struct tree_node *right;
	int data;
};


void tree_init(struct tree_node **tree);

//struct tree_node * build_enough(struct tree_node *tree, int i);
struct tree_node * build_enough(int i);

void bianli_zhongxu(struct tree_node *tree);
#endif
