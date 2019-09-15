#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"critical.h"

void clear_input(void)
{
	while (getchar() != '\n')
		continue;
}

void create_AdjListGragh(PLgragh LG)
{
	int i, j, k;
	printf("Enter the numbers of vertex and edge:\n");
	scanf("%d %d", &LG->num_ver, &LG->num_edge);						//输入顶点个数和边的数量
	printf("Enter the data for the vertexes:\n");
	clear_input();
	for (i = 0; i < LG->num_ver; i++)									//初始化一个无边只具有顶点的图
	{
		if (i == 0)
			printf("Enter the first indegree and data: ");
		else if (i == LG->num_ver - 1)
			printf("Enter the last indegree and data: ");
		else
			printf("Enter the next: ");
		scanf("%d", &LG->adjlist[i].indegree);
		clear_input();
		LG->adjlist[i].data = getchar();
		clear_input();
		LG->adjlist[i].firstedge = NULL;
	}

	for (k = 0; k < LG->num_edge; k++)									//输入num_edge条边的数据
	{
		int weight;
		printf("Enter the data of the edge in the form:");
		printf("Edge (Vi,Vj) and weight: ");
		scanf("%d %d %d", &i, &j, &weight);

		PEdgeNode pnew = (PEdgeNode)malloc(sizeof(EdgeNode));			//注意由于无向图每一条边涉及到两个顶点，所以需要将边的信息分别两次给两个邻接链表结点
		if (!pnew)
			exit(-1);
		pnew->weight = weight;
		pnew->adjvertex = j;
		pnew->pNext = LG->adjlist[i].firstedge;
		LG->adjlist[i].firstedge = pnew;
	}
}

void destroy_LGragh(PLgragh LG)
{
	int i;
	for (i = 0; i < LG->num_ver; i++)
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