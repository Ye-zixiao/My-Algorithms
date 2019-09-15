#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"topsort.h"

void init_LinkQueue(P_QUEUE pP)
{
	pP->rear = (PNODE)malloc(sizeof(NODE));
	if (pP->rear == NULL)
	{
		fprintf(stderr, "Can't create dynamic memory for node.\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		pP->front = pP->rear;											//初始化，使得队列的队尾和对头的指针都指向头结点
		pP->rear->pNext = NULL;
	}
}

void en_queue(P_QUEUE pP, int value)
{
	PNODE p = (PNODE)malloc(sizeof(NODE));
	if (!p)
	{
		fprintf(stderr, "Can't create dynamic memory for this node.\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		p->data = value;												//入队操作只再链表的末尾添加结点
		p->pNext = pP->rear->pNext;										//其实这一步可以写p->pNext=NULL;
		pP->rear->pNext = p;
		pP->rear = p;													//然后将新的结点的地址赋给队尾指针
	}
}

bool de_queue(P_QUEUE pP, int* pvalue)
{
	if (is_emptyqueue(pP))
		return false;
	else
	{
		PNODE q = pP->front->pNext;
		*pvalue = q->data;
		pP->front->pNext = q->pNext;

		if (pP->rear == q)												//在出队这一点上需要注意的是，特别的当队列中只有一个有效元素时，需要在出队后
			pP->rear = pP->front;										//特别的将队尾指针重新指向回头结点
		free(q);
		return true;
	}
}

bool is_emptyqueue(P_QUEUE pP)
{
	if (pP->front == pP->rear)
		return true;
	else
		return false;
}

void destroy_queue(P_QUEUE pP)												//这里的free_queue是将队列中的所有结点的内存全部释放
{
	PNODE p = pP->front;
	while (p != NULL)
	{
		PNODE q = p;
		p = p->pNext;
		free(q);
	}
}