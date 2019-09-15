//															Cruskal算法计算最小生成树MST
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define MAXVER 10
#define MAXDEGE 20
#define INF 65535

typedef struct mgragh {										//定义邻接矩阵的结构组成
	char vertex[MAXVER];									//顶点的信息
	int arc[MAXVER][MAXVER];								//边上的权
	int num_ver;											//顶点的数量
	int num_edge;											//边的数量
}MGragh, * PMGragh;

typedef struct edge {
	int start;
	int end;
	int weight;
}EDGE;

void init_mgragh(PMGragh pMG);								//初始化邻接矩阵
void clear_input(void);										//清除输入缓冲区的数据
void MST_Cruskal(PMGragh pMG);								//利用Cruskal法计算最小生成树
int find_endver(int i,int *end_vertex);						//获得当前顶点在生成树上的终点

int main(void)
{
	MGragh MG;
	init_mgragh(&MG);
	MST_Cruskal(&MG);

	return 0;
}

void clear_input(void)
{
	while (getchar() != '\n')
		continue;
}

void init_mgragh(PMGragh pMG)
{
	int i, j, k;
	printf("Enter the numbers of the vertexes and the edges: ");							//输入边的数量和顶点数量
	scanf("%d %d", &pMG->num_ver, &pMG->num_edge);
	clear_input();
	for (i = 0; i < pMG->num_ver; i++)														//构造无边的顶点表
	{
		if (i == 0)
			printf("Enter the first data for vertex: ");
		else if (i == pMG->num_ver - 1)
			printf("Enter the last one: ");
		else
			printf("Enter the next data: ");
		pMG->vertex[i] = getchar();
		clear_input();
	}

	for (i = 0; i < pMG->num_ver; i++)
		for (j = 0; j < pMG->num_ver; j++)
			pMG->arc[i][j] = INF;

	for (k = 0; k < pMG->num_edge; k++)														//完善边的信息
	{
		int weight;
		printf("Enter the data of the edge(in the form: (Vi,Vj) and weight): ");
		scanf("%d %d %d", &i, &j, &weight);
		pMG->arc[i][j] = weight;
		pMG->arc[j][i] = weight;
	}
}

void MST_Cruskal(PMGragh pMG)
{
	EDGE edges[MAXDEGE];													/*边表：记录边的数据，每一条边都是由编号较小的顶点指向编号较大的顶点，在这个数组当中，
																			数组的元素数据表示该下标所代表的顶点所指向的下个一顶点的位置，仿佛这个无向边，变成由于
																			编号导致了变成了有向边*/
	int end_vertex[MAXVER];													/*记录生成树上顶点的终点的数组*/
	int i, j;
	int k = 0;
	int sum_weight = 0;

	for (i = 0; i < pMG->num_ver; i++)
		for (j = 0; j < pMG->num_ver; j++)
			if (i < j && pMG->arc[i][j] < INF)								/*特别地，i<j将邻接矩阵的上三角部分中有效数据赋值给边表数组，而且要求无向图也要
																				中的边在编号上也是需要由大小顺序的，任何一条边在编号上都是从（编号较小者顶点
																				start指向编号较大者的顶点end）*/
			{
				edges[k].start = i;		//i<j所以i给了start
				edges[k].end = j;
				edges[k].weight = pMG->arc[i][j];							//载入边的权重数据
				k++;
			}
	for(i=0;i<pMG->num_edge-1;i++)											//选择排序将边集数组按权重从小到大排序
		for(j=i+1;j<pMG->num_edge;j++)
			if (edges[i].weight > edges[j].weight)
			{
				EDGE temp = edges[i];
				edges[i] = edges[j];
				edges[j] = temp;
			}
	/*两个有序：
		1、顶点有序：任何一条边在描述时都是由编号更小的start指向编号更大的end，比如V0->V3能够起到描述边表中的边的功能，但是这条边不能用V3->V0在边表中描述；
		2、边有序：在边表中需要将边按照由小到大的顺序排序*/

/*	printf("The result of the sorting:\n");
	for (k = 0; k < pMG->num_edge; k++)
		printf("%d: %d->%d,weight=%d\n", k, edges[k].start, edges[k].end, edges[k].weight);*/

	for (i = 0; i < pMG->num_ver; i++)										//初始化时，数组下标所代表的顶点（若有边与之相连）的默认指向终点的下标为0
		end_vertex[i] = 0;

	printf("The path of MST:\n");
	for (i = 0; i < pMG->num_edge; i++)
	{
		int n = find_endver(edges[i].start, end_vertex);					//找出当前的边的起始顶点的终点
		int m = find_endver(edges[i].end, end_vertex);						//找出当前的边的末尾顶点的终点
		if (n != m)															//若两者的终点是同一个，那么说明当前边若加入到MST会导致形成环路
		{
			end_vertex[n] = m;												//若不同，那么将起始点的终点设置为m下标代表的顶点
			printf("%c->%c ,weight=%d\n", pMG->vertex[edges[i].start], pMG->vertex[edges[i].end], edges[i].weight);		//打印出这条加入MST的边
			sum_weight += edges[i].weight;
		}
	}
	printf("The weight of the MST is %d.\n", sum_weight);
}

int find_endver(int i, int* end_vertex)										//不断地找出当前点的下一个指定点，不断地找下一个指定点就会找到终点，返回终点的下标
{
	while (end_vertex[i] > 0)		//若end_vertex等于0，表示当前下标的顶点的终点就是自身，即它只不过是一颗孤零零的顶点
		i = end_vertex[i];
	return i;
}