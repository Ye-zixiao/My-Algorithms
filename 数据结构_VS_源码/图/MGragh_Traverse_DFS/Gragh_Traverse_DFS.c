//																深度优先遍历邻接矩阵
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
}MGragh,*PMgragh;

void create_gragh(PMgragh G);									//创建数据数组和邻接矩阵
void DFS(PMgragh G, int i, bool* visited);						//对某一个点深度遍历，而对于连通分量而言，它将会引出其他点，使得递归能够访问它们/但是对于非连通图而言就需要遍历进行辅助
void DFS_Traverse(PMgragh G);									//深度遍历函数
void clear_inputIO(void);										//清空标准输入流中的缓冲数据

int main(void)
{
	MGragh G;
	create_gragh(&G);
	DFS_Traverse(&G);

	return 0;
}

void clear_inputIO(void)
{
	while (getchar() != '\n')
		continue;
}

void create_gragh(PMgragh G)
{
	int i,j,k;
	printf("Enter the numbers of the vertex and edge:\n");		//输入顶点数和边的数量
	scanf("%d %d", &G->num_vertex, &G->num_edge);
	clear_inputIO();
	printf("Enter the data of the vertexs:\n");					//利用循环输入顶点上的数据
	for (i = 0; i < G->num_vertex; i++)
	{
		scanf("%c", &G->data[i]);
		clear_inputIO();
	}

	for(i=0;i<G->num_vertex;i++)								//先初始化将邻接矩阵默认为全部边都没有进行相连
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
		if(k<G->num_edge)
			printf("Keep entering:");
	}
	putchar('\n');
}

void DFS(PMgragh G, int i,bool *visited)
{
	int j;
	visited[i] = true;											//将visited数组中当前的元素设置为true表示这个点已经被访问过了
	printf("%c", G->data[i]);									//访问打印
	//putchar('\n');
	for (j = 0; j < G->num_vertex; j++)							//for为的是找出当前顶点的所有邻接顶点
	{
		if (G->arc[i][j] != INF && !visited[j])					
			DFS(G, j, visited);									//递归访问它的邻接顶点
	}
}

void DFS_Traverse(PMgragh G)
{
	int i;
	bool visited[MAXVER];

	for (i = 0; i < MAXVER; i++)
		visited[i] = false;
	for (i = 0; i < G->num_vertex; i++)							//for循环遍历是为了防止图中存在非连通分量递归不能访问全部数据而准备的
	{
		if (!visited[i])										//遇到没由访问过的顶点就调用函数进行访问
			DFS(G, i, visited);
	}
	putchar('\n');
}