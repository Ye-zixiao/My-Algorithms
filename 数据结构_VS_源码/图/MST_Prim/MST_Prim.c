//															Prim算法计算最小生成树MST
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define MAXVER 10
#define INF 65535

typedef struct mgragh {										//定义邻接矩阵的结构组成
	char vertex[MAXVER];									//顶点的信息
	int arc[MAXVER][MAXVER];								//边上的权
	int num_ver;											//顶点的数量
	int num_edge;											//边的数量
}MGragh, * PMGragh;

void init_mgragh(PMGragh pMG);								//初始化邻接矩阵
void clear_input(void);										//清除输入缓冲区的数据
void MST_Prim(PMGragh pMG);									//使用Prim算法计算出连通图的最小生成树

int main(void)
{
	MGragh MG;
	init_mgragh(&MG);
	printf("MST is following:\n");
	MST_Prim(&MG);

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

void MST_Prim(PMGragh pMG)
{
	int i, sum = 0;
	int join_mst_ver[MAXVER];																	/*接入顶点数组：记录了当前未连接到最小生成树的顶点（V-U集）接入到MST时最小代价边的
																								另一端的顶点（该顶点已经在生成树上，在U集中）的下标*/
	int join_mst_lowcost[MAXVER];																/*未接入到MST顶点接入到MST时所需要付出的最小代价（接入边的权重）*/
	for (i = 0; i < pMG->num_ver; i++)															//初始化
	{
		join_mst_ver[i] = 0;																	//一开始认为接入点从V0点开始
		join_mst_lowcost[i] = pMG->arc[0][i];													//这里假设是从V0开始加入到最小生成树的
	}
	join_mst_lowcost[0] = 0;																	//join_mst_lowcost置零表示这个顶点已经被接入到MST中

	for (i = 1; i < pMG->num_ver; i++)															//开始对除V0点的其他点中找接入到MST最小代价边
	{
		int min = INF;
		int j,k;
		for (j = 1; j < pMG->num_ver; j++)
		{
			if (join_mst_lowcost[j] != 0 && join_mst_lowcost[j] < min)
			{
				min = join_mst_lowcost[j];														//记录最小代价边的权重
				k = j;																			//记录最小代价边所代表的这个顶点（引入点，还未加入MST）的下标
			}
		}
		printf("%c->%c,weight: %d\n", pMG->vertex[join_mst_ver[k]], pMG->vertex[k], min);		//打印：引入点->接入点 （即这次加入到MST的最小代价边）和权重（最小代价）
		sum += min;
		join_mst_lowcost[k] = 0;																//置下标为k的这个引入点为已接入标志（即0）

		for (j = 1; j < pMG->num_ver; j++)														//更新引入点的邻接点这时接入到MST的数据
		{
			if (join_mst_lowcost[j] != 0 && pMG->arc[k][j] < join_mst_lowcost[j])				/*若引入点到引入点的邻接点的距离小于原来记录中引入点的邻接点接入到MST的最小代价，
																								那么此时修改这个邻接点的接入到MST的最小代价（join_mst_lowcost）和邻接点的接入点
																								（join_mst_ver）*/
			{
				join_mst_lowcost[j] = pMG->arc[k][j];
				join_mst_ver[j] = k;
			}
		}
	}
	printf("The weight of the MST is %d.\n", sum);
}