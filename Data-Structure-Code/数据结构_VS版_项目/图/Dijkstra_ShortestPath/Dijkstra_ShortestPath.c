//															Dijkstra算法计算最短路径
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
}MGragh,*PMGragh;

void init_mgragh(PMGragh pMG);														//初始化邻接矩阵
void clear_input(void);																//清除输入缓冲区的数据
void Dijkstra_ShortestPath(PMGragh pMG, int s,int *pre_vertex,int *shortest_path);	//使用迪杰斯特拉算法算出起点到其他顶点的最短路径和各终点的前驱
void show_path(int i, int* pre_vertex,PMGragh pMG);									//打印前驱递归函数
void show_finalpath(int i, int* pre_vertex, PMGragh pMG);							//通过递归调用上面的函数打印固定起点到自定义终点的完整路径

int main(void)
{
	int pre_vertex[MAXVER];
	int shortest_path[MAXVER];
	MGragh MG;
	int i, j;

	init_mgragh(&MG);
	Dijkstra_ShortestPath(&MG, 0, pre_vertex, shortest_path);

	printf("The path the first one to the last one is: ");
	show_finalpath(8, pre_vertex, &MG);											//这个终点自定义，若顶点数量多了就要去修改下maxver这个明示常量
	printf("The shortest path is %d.\n", shortest_path[8]);

	return 0;
}

void clear_input(void)
{
	while (getchar() != '\n')
		continue;
}

void init_mgragh(PMGragh pMG)
{
	int i,j,k;
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

void Dijkstra_ShortestPath(PMGragh pMG, int s, int* pre_vertex, int* shortest_path)			//这个函数的缺点就是有可能对于输入的前驱数组和最短路径数组产生溢出，需要人为注意下上限
{
	bool find[MAXVER];															//S集中的一部分：当find数组中的值置为true时表示该顶点已被计算出最短路径
	int i,j,k;

	for (i = 0; i < pMG->num_ver; i++)											//初始化S集和U集：使得只有起点表示为被计算出最短路径
	{																			//前驱都初始化为0，从起点到各顶点最短路径默认为矩阵第一行
		find[i] = false;								//计算完毕标志数组
		pre_vertex[i] = 0;								//前驱顶点数组
		shortest_path[i] = pMG->arc[s][i];				//最短路径数组
	}
	find[s] = true;
	shortest_path[s] = 0;

	for (i = 1; i < pMG->num_ver; i++)											//遍历除起点外的所有顶点。注意：这个s顶点若被初始化时找出了最短路径，那么在这个循环中就不要遍历他了
	{
		int min = INF;
		for (j = 0; j < pMG->num_ver; j++)										//在当前最短路径数组中找出（未被计算出最短路径的顶点）从起点到其他顶点的最短路径
		{
			if (!find[j] && shortest_path[j] < min)								//可以断定这个找出的顶点必然是已计算出最短路径的顶点的邻接点
			{
				min = shortest_path[j];
				k = j;
			}
		}
		find[k] = true;															//标志找出顶点已被计算出最短路径
		
		for (j = 0; j < pMG->num_ver; j++)
		{
			if (!find[j] && (pMG->arc[k][j] + min) < shortest_path[j])			//修正这个找出点的邻接点到起点的最短路径
			{																	/*比较的是： 找出点最短路径+该点到邻接点的权（pMG->arc[k][j]） 与 当前最短路径数组中起点到该临界点的路径
																					即： （Vs->Vk->Vj的路径长度） 若小于 （当前最短路径数组中 Vs->Vj 的路径长度）就更新数组（即U集）*/
				shortest_path[j] = min + pMG->arc[k][j];						//若前者更小，修改邻接点的最短路径数组数据和前驱数组
				pre_vertex[j] = k;
			}
		}
	}
	/*
	算法思路：
			1、初始化S集和U集；
			2、找出U集当中的到起点s的最短路径顶点，纳入到S集中
			3、用这个顶点min+到邻接点的权与最短路径数组比较，更新U集
			4、重复2、3两步
	*/
}

void show_path(int i, int* pre_vertex, PMGragh pMG)
{
	if (i == 0)
		printf("%d(%c)->",i,pMG->vertex[i]);
	else
	{
		show_path(pre_vertex[i], pre_vertex,pMG);								//利用递归逆向输出路径，其实用的就是堆栈的知识：先进后出
		printf("%d(%c)->", i,pMG->vertex[i]);
	}
}

void show_finalpath(int i, int* pre_vertex, PMGragh pMG)
{
	show_path(pre_vertex[i], pre_vertex, pMG);
	printf("%d(%c).\n", i, pMG->vertex[i]);
}