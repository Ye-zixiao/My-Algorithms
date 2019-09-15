//																广度优先遍历邻接矩阵
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define MAXVER 20
#define INF 65535												//INF表示两个顶点间没用边

typedef struct mgrgh {											//定义邻接矩阵的结构体变量组成
	char data[MAXVER];
	int arc[MAXVER][MAXVER];
	int num_vertex;
	int num_edge;
}MGragh, * PMgragh;

typedef struct node {											//定义链对的组成结构
	int data;
	struct node* pNext;
}QUEUENODE,*PQUEUENODE;

typedef struct queue {											//定义链对的头指针和尾指针
	PQUEUENODE front;
	PQUEUENODE rear;
}QUEUE,*PQUEUE;

void create_gragh(PMgragh G);						//生成邻接矩阵
void clear_inputIO(void);							//清空输入缓冲区的数据

void init_queue(PQUEUE Q);							//初始化链对
void enqueue(PQUEUE Q, int i);						//将顶点数组的下标入队
void dequeue(PQUEUE Q, int* i);						//将顶点数组的下标出队
bool is_emptyqueue(PQUEUE Q);						//判断连队是否为空
void destroy_queue(PQUEUE Q);						//销毁链对（释放动态内存）

void Mgragh_BFS_Traverse(PMgragh G);				//对由邻接矩阵组成的图进行广度优先遍历

int main(void)
{
	MGragh G;
	create_gragh(&G);
	Mgragh_BFS_Traverse(&G);

	return 0;
}

void clear_inputIO(void)
{
	while (getchar() != '\n')
		continue;
}

void create_gragh(PMgragh G)
{
	int i, j, k;
	printf("Enter the numbers of the vertex and edge:\n");		//输入顶点数和边的数量
	scanf("%d %d", &G->num_vertex, &G->num_edge);
	clear_inputIO();
	printf("Enter the data of the vertexs:\n");					//利用循环输入顶点上的数据
	for (i = 0; i < G->num_vertex; i++)
	{
		scanf("%c", &G->data[i]);
		clear_inputIO();
	}

	for (i = 0; i < G->num_vertex; i++)							//先初始化将邻接矩阵默认为全部边都没有进行相连
		for (j = 0; j < G->num_vertex; j++)
			G->arc[i][j] = INF;

	printf("Enter the edge and the its weight:\n");
	for (k = 0; k < G->num_edge; k++)							//循环输入边的数据，这里仅针对无向图
	{
		int weight;
		if (k == 0)
			printf("Enter the (Vi,Vj) and Weight:");
		scanf("%d %d %d", &i, &j, &weight);
		G->arc[i][j] = weight;
		G->arc[j][i] = weight;
		if (k < G->num_edge)
			printf("Keep entering:");
	}
	putchar('\n');
}

void init_queue(PQUEUE Q)
{
	Q->front = (PQUEUENODE)malloc(sizeof(QUEUENODE));
	if (Q->front == NULL)
		exit(-1);
	else
	{
		Q->rear = Q->front;										//初始化链对，使得头指针和尾指针都指向头结点
		Q->rear->pNext = NULL;
	}
}

void enqueue(PQUEUE Q, int i)
{
	PQUEUENODE pNew = (PQUEUENODE)malloc(sizeof(QUEUENODE));
	if (!pNew)
		exit(-1);
	else
	{															//这里要特别注意下，链对的指针方向是从头指针到尾指针；而链栈是自顶向下（ptop指向pbottom）
		pNew->data = i;
		pNew->pNext = Q->rear->pNext;							//常规的尾插操作
		Q->rear->pNext = pNew;
		Q->rear = pNew;
	}
}

bool is_emptyqueue(PQUEUE Q)
{
	if (Q->front == Q->rear)
		return true;
	else
		return false;
}

void dequeue(PQUEUE Q, int* i)
{
	if (is_emptyqueue(Q))
		return;
	else
	{
		PQUEUENODE ptemp = Q->front->pNext;
		*i = ptemp->data;
		Q->front->pNext = ptemp->pNext;

		if (ptemp == Q->rear)								//在出队是必须要注意下，当尾指针指向头指针下一个结点时，删除这个结点会导致尾指针指向不知名的地方
			Q->rear = Q->front;								//所以要用if语句去判断一下，使尾指针在队列为空时重新指向头结点
		free(ptemp);
	}
}

void destroy_queue(PQUEUE Q)
{
	if (!Q)
		return;
	else
	{
		PQUEUENODE p = Q->front;
		while (p)
		{
			PQUEUENODE q = p;
			p = p->pNext;
			free(q);
		}
	}
}

void Mgragh_BFS_Traverse(PMgragh G)
{
	int i,j;
	QUEUE Q;
	bool visited[MAXVER];

	init_queue(&Q);											//初始化队列和visited数组，为后面的遍历做准备
	for (i = 0; i < MAXVER; i++)
		visited[i] = false;

	for (i = 0; i < G->num_vertex; i++)						//for循环遍历是为了防止非连通图遍历时有一个点不能广度优先遍历全部顶点
	{
		if (!visited[i])
		{
			visited[i] = true;
			printf("%c ", G->data[i]);
			enqueue(&Q, i);									//先将第一个顶点入队

			while (!is_emptyqueue(&Q))						//若队列非空，就出队一个顶点在数组中的下标，由这个下标去找出它所有的邻接点
			{
				dequeue(&Q, &i);
				for (j = 0; j < G->num_vertex; j++)
				{
					if (!visited[j]&&G->arc[i][j]<INF)		//for循环是为了找出它的所有邻接点
					{
						visited[j] = true;
						printf("%c ", G->data[j]);			//找出后访问并将其入队
						dequeue(&Q, j);
					}
				}
			}
			/*
			伪算法：

					先入对一个；
					while（队列非空）
					{
						出对一个；
						for（找出这个顶点的所有邻接点）
						{
							将为访问的结点标记为已访问；
							访问这个邻接点；
							入队；
						}
					}

			*/

		}
	}
	putchar('\n');
	destroy_queue(&Q);
}