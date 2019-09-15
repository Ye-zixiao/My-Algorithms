//														深度遍历邻接表
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define MAXVER 10

typedef struct edgenode {									//边表结点结构
	int adjvertex;											//携带邻接点在数组当中的下标
	int weight;												//边的权重
	struct edgenode* pNext;
}EdgeNode,*PEdgeNode;

typedef struct vertexnode {									//顶点数组结构
	char data;
	PEdgeNode firstedge;									//指向头一个临界点的下标
}VerNode[MAXVER];

typedef struct lgragh {										//图的结构
	VerNode adjlist;										//创建一个顶点带头指针的数组
	int num_ver;											//顶点数量
	int num_edge;											//边的数量
}LGragh,*PLgragh;

void create_AdjListGragh(PLgragh LG);						//创建创建一个邻接表
void DFS(PLgragh LG, int i, bool* visited);					//对一个点进行深度遍历，对于连通图而言用一个点就可以遍历整个图，但是对于非连通图就不一样了
void AdjList_Traverse_DFS(PLgragh LG);						//对图进行深度遍历
void clear_input(void);										//清除输入缓冲区中的数据
void destroy_LGragh(PLgragh LG);							//释放邻接表中的邻接链表中的结点的动态内存

int main(void)
{
	LGragh LG;
	create_AdjListGragh(&LG);
	AdjList_Traverse_DFS(&LG);

	destroy_LGragh(&LG);
	return 0;
}

void clear_input(void)
{
	while (getchar() != '\n')
		continue;
}

void create_AdjListGragh(PLgragh LG)
{
	int i,j,k;
	printf("Enter the numbers of vertex and edge:\n");
	scanf("%d %d", &LG->num_ver, &LG->num_edge);						//输入顶点个数和边的数量
	printf("Enter the data for the vertexes:\n");
	clear_input();
	for (i = 0; i < LG->num_ver; i++)									//初始化一个无边只具有顶点的图
	{
		if (i == 0)
			printf("Enter the first data: ");
		LG->adjlist[i].data = getchar();
		clear_input();
		LG->adjlist[i].firstedge = NULL;
		if (i < LG->num_ver-1)
			printf("Enter the next: ");
	}

	for (k = 0; k < LG->num_edge; k++)									//输入num_edge条边的数据
	{																	
		int weight;
		printf("Enter the data of the edge in the form:");
		printf("Edge (Vi,Vj) and weight\n");
		scanf("%d %d %d", &i, &j, &weight);

		PEdgeNode pnew = (PEdgeNode)malloc(sizeof(EdgeNode));			//注意由于无向图每一条边涉及到两个顶点，所以需要将边的信息分别两次给两个邻接链表结点
		if (!pnew)
			exit(-1);
		pnew->weight = weight;
		pnew->adjvertex = j;
		pnew->pNext = LG->adjlist[i].firstedge;
		LG->adjlist[i].firstedge = pnew;

		pnew = (PEdgeNode)malloc(sizeof(EdgeNode));
		if (!pnew)
			exit(-1);
		pnew->adjvertex = i;
		pnew->weight = weight;
		pnew->pNext = LG->adjlist[j].firstedge;
		LG->adjlist[j].firstedge = pnew;
	}
}

void DFS(PLgragh LG, int i, bool* visited)
{
	visited[i] = true;													//访问完后标记该顶点已经被访问过了
	printf("%c", LG->adjlist[i].data);
	PEdgeNode p = LG->adjlist[i].firstedge;
	while (p)															//找出当前顶点的所有邻接点进行访问，若已被访问就访问下一个顶点
	{
		if (!visited[p->adjvertex])
			DFS(LG, p->adjvertex, visited);								//递归调用访问邻接点
		p = p->pNext;
	}
}

void AdjList_Traverse_DFS(PLgragh LG)
{
	int i;
	bool visited[MAXVER];
	for (i = 0; i < MAXVER; i++)
		visited[i] = false;

	for (i = 0; i < LG->num_ver; i++)									//为了避免非连通图递归不全，所以需要循环遍历
	{
		if (!visited[i])
			DFS(LG, i, visited);
	}
	putchar('\n');
}

void destroy_LGragh(PLgragh LG)
{
	int i;
	for(i=0;i<LG->num_ver;i++)
	{
		PEdgeNode p = LG->adjlist[i].firstedge;							//依次循环所有的顶点数组，释放点所有的动态内存
		while (p)
		{
			PEdgeNode q = p;
			p = p->pNext;
			free(q);
		}
	}
}