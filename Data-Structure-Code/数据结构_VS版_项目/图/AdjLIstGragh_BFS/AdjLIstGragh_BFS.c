//												对邻接表进行广度优先遍历
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define MAXVER 10

typedef struct edgenode {						//对边表结点的结构进行定义
	int adjver;
	int weight;
	struct edgenode* pNext;
}EDGENODE,*PEDGENODE;

typedef struct vernode {						//对顶点表的结构进行定义
	char data;
	PEDGENODE firstedge;
}VERNODE[MAXVER];

typedef struct adjlist {						//构造一个邻接表：表明它具有一个顶点表数组和顶点数量、边的数量
	VERNODE AdjList;
	int num_ver;
	int num_edge;
}ADJLIST,*PADJLIST;

typedef struct node {							//对链对的结构组成进行定义
	int i;
	struct node* pNext;
}QUEUENODE,*PQUEUENODE;

typedef struct queue {							//声明一个结构：其中包含头指针和尾指针
	PQUEUENODE front;
	PQUEUENODE rear;
}QUEUE,*PQUEUE;

void init_AdjList(PADJLIST pLG);				//初始化邻接表
void clear_input(void);							//清除标准输入缓冲区中的数据
void LGragh_Traverse_BFS(PADJLIST pLG);			//对邻接表进行广度优先遍历

void init_queue(PQUEUE pQ);						//初始化链对为空对列
void enqueue(PQUEUE pQ, int i);					//入队
void dequeue(PQUEUE pQ, int* i);				//出队
bool is_emptyqueue(PQUEUE pQ);					//判断链对是否为空
void destroy_queue(PQUEUE pQ);					//销毁链对（释放动态内存）
void destroy_AdjList(PADJLIST pLG);				//销毁邻接表

int main(void)
{
	ADJLIST LG;
	init_AdjList(&LG);
	LGragh_Traverse_BFS(&LG);
	destroy_AdjList(&LG);

	return 0;
}

void clear_input(void)
{
	while (getchar() != '\n')
		continue;
}

void init_AdjList(PADJLIST pLG)	
{
	int i,j,k;
	printf("Enter the numbers of the vertex and edge: ");				//要求输入图的顶点数和边的数量
	scanf("%d %d", &pLG->num_ver, &pLG->num_edge);
	clear_input();
	for (i = 0; i < pLG->num_ver; i++)									//初始化一个无边但具有顶点的图的，只对顶点表
	{
		if (i == 0)
			printf("Enter the first data of the vertex: ");
		else if (i == pLG->num_ver - 1)
			printf("Enter the last one: ");
		else
			printf("Enter the next one: ");
		scanf("%c", &pLG->AdjList[i].data);
		clear_input();
		pLG->AdjList[i].firstedge = NULL;
	}

	for (k = 0; k < pLG->num_edge; k++)									//对于无向图要求按照要求输入边的信息，
	{																	//而且每一条边会创建两个边表结点，因为它涉及到两个顶点
		int weight;
		printf("Enter the data of the edge in");
		printf("the form: (Vi,Vj) and weight: ");
		scanf("%d %d %d", &i, &j, &weight);
		PEDGENODE p = (PEDGENODE)malloc(sizeof(EDGENODE));
		if (!p)
			exit(-1);
		p->adjver = j;
		p->weight = weight;
		p->pNext = pLG->AdjList[i].firstedge;
		pLG->AdjList[i].firstedge = p;

		p = (PEDGENODE)malloc(sizeof(EDGENODE));
		if (!p)
			exit(-1);
		p->adjver = i;
		p->weight = weight;
		p->pNext = pLG->AdjList[j].firstedge;
		pLG->AdjList[j].firstedge = p;
	}
}

void init_queue(PQUEUE pQ)
{
	pQ->front = (PEDGENODE)malloc(sizeof(EDGENODE));
	if (!pQ->front)
		exit(-1);
	else
	{
		pQ->rear = pQ->front;
		pQ->rear->pNext = NULL;
	}
}

bool is_emptyqueue(PQUEUE pQ)
{
	if (pQ->front == pQ->rear)
		return true;
	else
		return false;
}

void enqueue(PQUEUE pQ, int i)
{
	PQUEUENODE pNew = (PQUEUENODE)malloc(sizeof(QUEUENODE));
	if (!pNew)
		exit(-1);
	else
	{
		pNew->i = i;											//注意链对是在链表的末尾插入，而展示在自底向上堆放
		pNew->pNext = pQ->rear->pNext;
		pQ->rear->pNext = pNew;
		pQ->rear = pNew;
	}
}

void dequeue(PQUEUE pQ, int* i)
{
	if (is_emptyqueue(pQ))
		return;
	else
	{
		PQUEUENODE ptemp = pQ->front->pNext;
		*i = ptemp->i;
		pQ->front->pNext = ptemp->pNext;
		if (ptemp == pQ->rear)									//出队时要特别小心头头指针所指向的头结点的下一个结点就是尾指针的位置的这种特殊情况
			pQ->rear = pQ->front;
		free(ptemp);
	}
}

void destroy_queue(PQUEUE pQ)
{
	if (!pQ)
		return;
	else
	{
		PQUEUENODE p = pQ->front;
		while (p)
		{
			PQUEUENODE q = p;
			p = p->pNext;
			free(q);
		}
	}
}

void LGragh_Traverse_BFS(PADJLIST pLG)
{
	QUEUE Q;
	int i;
	PEDGENODE p;
	bool visited[MAXVER];

	init_queue(&Q);
	for (i = 0; i < MAXVER; i++)
		visited[i] = false;

	for (i = 0; i < pLG->num_ver; i++)
	{
		if (!visited[i])
		{
			visited[i] = true;
			printf("%c ", pLG->AdjList[i].data);
			enqueue(&Q, i);
			while (!is_emptyqueue(&Q))
			{
				dequeue(&Q, &i);
				p = pLG->AdjList[i].firstedge;
				while (p)
				{
					if (!visited[p->adjver])
					{
						visited[p->adjver] = true;
						printf("%c ", pLG->AdjList[p->adjver].data);
						enqueue(&Q, p->adjver);
					}
					p = p->pNext;
				}
			}
			/*
			广度优先遍历算法的核心思想：
					先访问一个顶点；
					将该顶点在顶点表的下标入队；
					while（链对非空）
					{
						出队一个顶点的下标；
						得到该出队顶点的指向边的指针；
						while（对于它的所有邻接点）						//知道它的所有邻接点都访问完毕才退出循环
						{
							访问它未访问过的邻接点；
							入队；
							指向它的下一个邻接点；
						}
					}
			*/
		}
	}
	putchar('\n');
	destroy_queue(&Q);
}

void destroy_AdjList(PADJLIST pLG)
{
	int i;
	for (i = 0; i < pLG->num_ver; i++)
	{
		PEDGENODE p = pLG->AdjList[i].firstedge;
		while (p)
		{
			PEDGENODE q = p;
			p = p->pNext;
			free(q);
		}
	}
}