#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define MAXSIZE 10

typedef struct Queue {												//循环队列
	int* parr;
	int front;														//对头
	int rear;														//队尾
}QUEUE, * PQUEUE;

void init_Queue(PQUEUE pQ);											//初始化队列
bool is_empty(PQUEUE pQ);											//判断队列是否为空
bool is_full(PQUEUE pQ);											//判断队列是否已满
bool en_Queue(PQUEUE pQ, int value);								//入队
bool de_Queue(PQUEUE pQ, int* pvalue);								//出队
void traverse_Queue(PQUEUE pQ);										//遍历
int length_Queue(PQUEUE pQ);										//计算队列长度

int main(void)
{
	QUEUE Q;
	int value;

	init_Queue(&Q);
	en_Queue(&Q, 1);
	en_Queue(&Q, 2);
	en_Queue(&Q, 3);
	en_Queue(&Q, 4);
	en_Queue(&Q, 5);
	en_Queue(&Q, 6);
	en_Queue(&Q, 7);
	en_Queue(&Q, 8);
	en_Queue(&Q, 9);
	en_Queue(&Q, 10);
	en_Queue(&Q, 11);
	traverse_Queue(&Q);

	if (de_Queue(&Q, &value))
		printf("You dequeue the number %d.\n", value);
	else
		printf("Dequeue failed.\n");
	traverse_Queue(&Q);

	printf("Now the length of queue is %d.\n", length_Queue(&Q));

	free(Q.parr);															//释放数组的动态内存

	return 0;
}

void init_Queue(PQUEUE pQ)
{
	pQ->parr = (int*)malloc(sizeof(int) * MAXSIZE);
	if (pQ->parr == NULL)
	{
		fprintf(stderr, "Error in creating dynamic memory for array.\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		pQ->front = 0;													//将对头和队尾都初始化为0，同时也在表示队伍为空
		pQ->rear = 0;
	}
}

bool is_empty(PQUEUE pQ)
{
	if (pQ->front == pQ->rear)											//当对头等于队尾时，表示队列为空
		return true;
	else
		return false;
}

bool is_full(PQUEUE pQ)
{
	if ((pQ->rear + 1) % MAXSIZE == pQ->front)							//队尾指向最后一个有效元素的下一个元素，而且这个元素是不能存放数据的，所以长度为maxsize
		return true;													//的数组只能使用maxsize-1个元素。所以在循环列表中当队尾加上1取数组长度的模等于对头时表示已满
	else
		return false;
}

bool en_Queue(PQUEUE pQ, int value)
{
	if (is_full(pQ))												//检错模块
		return false;
	else
	{
		pQ->parr[pQ->rear] = value;
		pQ->rear = (pQ->rear + 1) % MAXSIZE;						//队尾+1再取数组长度的模赋给新的队尾
		return true;
	}
}

bool de_Queue(PQUEUE pQ, int* pvalue)
{
	if (is_empty(pQ))												//检错模块
		return false;
	else
	{
		*pvalue = pQ->parr[pQ->front];
		pQ->front = (pQ->front + 1) % MAXSIZE;						//队头+1再取数组长度的模赋给新的队头
		return true;
	}
}

void traverse_Queue(PQUEUE pQ)
{
	int p = pQ->front;
	while (p != pQ->rear)											//当位置指示器指向到队尾时表示遍历完成
	{
		printf("%d ", pQ->parr[p]);
		p = (p + 1) % MAXSIZE;
	}
	putchar('\n');
}

int length_Queue(PQUEUE pQ)
{
	int len = 0;
	int q = pQ->front;
	while (q != pQ->rear)											//方法与遍历的方法相同
	{
		len++;
		q = (q + 1) % MAXSIZE;
	}
	return len;
}
