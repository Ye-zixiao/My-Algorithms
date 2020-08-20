#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"topsort.h"

void init_Stack(PSTACK pS)
{
	pS->pTop = (PNODE)malloc(sizeof(NODE));              //创建一个头结点，将初始化的头结点的地址给栈顶指针和栈底指针
	if (pS->pTop == NULL)
	{
		fprintf(stderr, "Can't create stack.\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		pS->pBottom = pS->pTop;
		pS->pTop->pNext = NULL;                          //并设置头结点的指针域为空指针
	}
}

void push_Stack(PSTACK pS, int value)
{
	PNODE pNew = (PNODE)malloc(sizeof(NODE));
	if (pNew == NULL)
	{
		fprintf(stderr, "Can't create a new node.\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		pNew->data = value;
		pNew->pNext = pS->pTop;                          //压栈，将新建的结点的指针域指向原来的栈顶结点
		pS->pTop = pNew;                                 //使新加的结点成为新一个栈顶结点
	}
}

bool is_emptystack(PSTACK pS)
{
	if (pS->pTop == pS->pBottom)                         //当栈顶指针和栈底指针都指向同一个头结点时，表示是空栈
		return true;
	else
		return false;
}

bool pop_Stack(PSTACK pS, int* value)
{
	if (is_emptystack(pS))                                    //检错模块
		return false;
	else
	{
		PNODE q = pS->pTop;                              //将原来的栈顶结点的地址暂放给另一个指向结点的指针，然后调节栈顶指针，并释放这个原来的栈顶结点的内存
		*value = q->data;
		pS->pTop = q->pNext;
		free(q);
		return true;
	}
}

void destroy_Stack(PSTACK pS)
{
	PNODE p = pS->pTop;
	while (p != NULL)                             //释放除头结点以外的所有结点的动态内存
	{
		PNODE q = p;
		p = p->pNext;
		free(q);
	}
}
