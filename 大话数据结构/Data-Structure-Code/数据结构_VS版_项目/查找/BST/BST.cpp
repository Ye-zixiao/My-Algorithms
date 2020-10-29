#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct BTnode {
	int data;
	struct BTnode* lchild;
	struct BTnode* rchild;
}BTNODE,*PBTNODE;

