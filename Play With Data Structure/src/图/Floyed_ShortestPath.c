//															Floyed算法计算最短路径
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

void init_mgragh(PMGragh pMG);																		//初始化邻接矩阵
void clear_input(void);																				//清除输入缓冲区的数据
void Floyed_ShortestPath(PMGragh pMG, int(*latter_vertex)[MAXVER], int(*shortest_path)[MAXVER]);		//对图进行弗洛伊德算法，计算出各个点到其他点的最短路径长度和前驱
void show_path(int i,int j, PMGragh pMG, int(*latter_vertex)[MAXVER], int(*shortest_path)[MAXVER]);	//显示出Vi到Vj的路径和最短路径长度

int main(void)
{
	int latter_vertex[MAXVER][MAXVER];										//中介顶点矩阵，每一个元素表示Vi到Vj获得最短路径时Vi的后继结点是什么，比如latter_vertex[i][j]表示的就是Vi的后继结点的下标
	int shortest_path[MAXVER][MAXVER];										//最短路径矩阵
	MGragh MG;
	init_mgragh(&MG);
	Floyed_ShortestPath(&MG, latter_vertex, shortest_path);
	show_path(0, 7, &MG, latter_vertex, shortest_path);

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

	for (k = 0; k < pMG->num_edge; k++)															//完善边的信息
	{
		int weight;
		printf("Enter the data of the edge(in the form: (Vi,Vj) and weight): ");
		scanf("%d %d %d", &i, &j, &weight);
		pMG->arc[i][j] = weight;
		pMG->arc[j][i] = weight;
	}
}

void Floyed_ShortestPath(PMGragh pMG, int(*latter_vertex)[MAXVER], int(*shortest_path)[MAXVER])
{
	int i, j, k;
	for(i=0;i<pMG->num_ver;i++)
		for (j = 0; j < pMG->num_ver; j++)
		{
			shortest_path[i][j] = pMG->arc[i][j];												//初始化时直接将邻接矩阵赋值给最短路径长度矩阵
			latter_vertex[i][j] = j;															//初始化时，让后继矩阵表示Vi->Vj是经过各自的Vj的，即Vi的直接后继结点是Vj
		}

	for(k=0;k<pMG->num_ver;k++)																	//遍历每一个顶点，让他们轮流当一次中介点
		for(i=0;i<pMG->num_ver;i++)
			for (j = 0; j < pMG->num_ver; j++)
			{
				if (i!=j&&shortest_path[i][j] > shortest_path[i][k] + shortest_path[k][j])		/*在这个程序当中为什么我要加入i！=j这个判断语句？
																									因为在书本中的邻接矩阵中将自己连自己顶点的情况中，把该路径设为了0而不是INF，
					当存在中介点Vk使得Vi->Vk->Vj的路径比原来最短路径矩阵中的数值更小，				所以shortest_path[i][j] > shortest_path[i][k] + shortest_path[k][j]该判断语句
					则更新最短路径矩阵和后继矩阵													并不会将最短路径修改，但是我将自己连接自己的情况设置成INF就有可能会使得这个路径长度
																									（U集）得到修改，因为INF永远大于其他值。所以加入这个判断语句，当然一般情况下也不会出现异常，只有
																									在输入起点和终点是一样时才会异常，比如输入（V1->V1）就会打印A->B->A这种奇怪的情况
																								*/
				{
					shortest_path[i][j] = shortest_path[i][k] + shortest_path[k][j];			//修正最短路径长度数组中的元素数据
					latter_vertex[i][j] = latter_vertex[i][k];									/*在这里将路径结点数组表示为pre_vertex有点误导人，事实上它更应该被表示为path或者latter_path，
																									这样更能把latter_path[i][k]表示为它是使Vi到Vj获得最短路径的中介点下标，
																									即获得最短路径时是Vi的后继顶点！！！！					*/

				}
			}
}

void show_path(int i, int j, PMGragh pMG, int(*latter_vertex)[MAXVER], int(*shortest_path)[MAXVER])
{
	printf("The path of (V%d to V%d) is: ", i, j);
	int temp = latter_vertex[i][j];													//获得Vi的后继结点下标给temp
	printf("%d(%c)->", i, pMG->vertex[i]);
	while (temp != j)																//当Vtemp的后继结点不是终点Vj时继续打印输出
	{
		printf("%d(%c)->", temp, pMG->vertex[temp]);
		temp = latter_vertex[temp][j];												//再次得到Vtemp的后继结点下标
	}
	printf("%d(%c)\n", temp, pMG->vertex[temp]);									//当得到的后继结点是终点时退出独立打印
	printf("And the shortest path of this way is %d.\n", shortest_path[i][j]);

	/*printf("check:\n");
	for (i = 0; i < pMG->num_ver; i++)
	{		for (j = 0; j < pMG->num_ver; j++)
		{
			printf("%d ", latter_vertex[i][j]);
		}
	putchar('\n');
	}*/
}