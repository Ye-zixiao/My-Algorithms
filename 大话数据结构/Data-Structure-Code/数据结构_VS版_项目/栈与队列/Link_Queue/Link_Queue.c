#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct node {
	int data;
	struct node* pNext;
}NODE, * PNODE;

typedef struct Linkqueue {														//链式队列
	PNODE front, rear;
}L_QUEUE, * P_QUEUE;

void init_LinkQueue(P_QUEUE pP);												//初始化队列
void en_queue(P_QUEUE pP, int value);											//入队
bool de_queue(P_QUEUE pP, int* pvalue);											//出队
bool is_empty(P_QUEUE pP);														//检查队列是否为空
int length_queue(P_QUEUE pP);													//计算队列的长度
void free_queue(P_QUEUE pP);													//释放队列的所有动态内存
void traverse_queue(P_QUEUE pP);												//遍历

int main(void)
{
	L_QUEUE Link_queue;
	int value;

	init_LinkQueue(&Link_queue);
	en_queue(&Link_queue, 1);
	en_queue(&Link_queue, 2);
	en_queue(&Link_queue, 3);
	en_queue(&Link_queue, 4);
	en_queue(&Link_queue, 5);
	en_queue(&Link_queue, 6);
	en_queue(&Link_queue, 7);
	en_queue(&Link_queue, 8);
	traverse_queue(&Link_queue);

	if (de_queue(&Link_queue, &value))
		printf("Dequeue success and dequeue the data %d.\n", value);
	else
		printf("Dequeue failed.\n");
	de_queue(&Link_queue, &value);
	de_queue(&Link_queue, &value);

	printf("After the dequeue:\n");
	traverse_queue(&Link_queue);
	printf("The length of the queue is %d\n", length_queue(&Link_queue));

	free_queue(&Link_queue);
	return 0;
}

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
	if (is_empty(pP))
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

bool is_empty(P_QUEUE pP)
{
	if (pP->front == pP->rear)
		return true;
	else
		return false;
}

int length_queue(P_QUEUE pP)
{
	PNODE p = pP->front->pNext;
	int len = 0;

	while (p != NULL)													//计算队列的长度的原理基本上和遍历一致
	{
		len++;
		p = p->pNext;
	}
	return len;
}

void traverse_queue(P_QUEUE pP)
{
	PNODE p = pP->front->pNext;
	while (p != NULL)
	{
		printf("%d ", p->data);
		p = p->pNext;
	}
	putchar('\n');
}

void free_queue(P_QUEUE pP)												//这里的free_queue是将队列中的所有结点的内存全部释放
{
	PNODE p = pP->front;
	while (p != NULL)
	{
		PNODE q = p;
		p = p->pNext;
		free(q);
	}
}