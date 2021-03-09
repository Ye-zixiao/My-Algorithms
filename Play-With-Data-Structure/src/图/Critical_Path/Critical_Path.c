#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"critical.h"
int* etv;													//创建一个指向事件最早发生时间数组的指针，用于存放各顶点（事件）的最早发生时间
STACK S_top;												//拓扑栈：用于存放图的拓扑序列

bool topsort(PLgragh pLG);									//对图进行拓扑排序，将拓扑排序的顶点下标先进后出放入拓扑栈中，并输出事件最早发生时间数组
void critical_path(PLgragh pLG);							//求图的关键路径

int main(void)
{
	LGragh LG;
	create_AdjListGragh(&LG);
	printf("The critical path is following:\n");
	critical_path(&LG);
	destroy_LGragh(&LG);

	return 0;
}

bool topsort(PLgragh pLG)
{
	int i;
	int count = 0;
	STACK temp_stack;										//创建一个临时容器
	etv = (int*)malloc(pLG->num_ver * sizeof(int));			//给事件最早发生时间数组分配动态内存
	if (!etv)
		exit(-1);

	init_Stack(&temp_stack);
	for (i = 0; i < pLG->num_ver; i++)
		if (pLG->adjlist[i].indegree == 0)
			push_Stack(&temp_stack, i);						//将顶点表入度为0的顶点下标压栈
	for (i = 0; i < pLG->num_ver; i++)						//初始化时间最早发生时间数组
		etv[i] = 0;

	while (!is_emptystack(&temp_stack))						//若临时栈不为空
	{
		pop_Stack(&temp_stack, &i);							//弹栈顶点下标
		push_Stack(&S_top, i);								//将这个下标压入拓扑栈
		count++;

		PEdgeNode p = pLG->adjlist[i].firstedge;			//获得该顶点的边表指针，指向其邻接点的下标
		while (p != NULL)
		{
			int k = p->adjvertex;							//获得其邻接点的下标
			if ((--pLG->adjlist[k].indegree) == 0)			//若入度自减一，则将邻接点的下标压栈
				push_Stack(&temp_stack, k);
			if (etv[i] + p->weight > etv[k])				/*若目前该点的邻接点的时间最早发生时间etv[k]<该点的时间最早发生时间etv[i]+两个顶点之间边的权重，
															那么就更新这个邻接点的最早发生时间etv*/
				etv[k] = etv[i] + p->weight;
			p = p->pNext;									//指向下一个邻接点
		}
	}
	destroy_Stack(&temp_stack);

	if (count == pLG->num_ver)
		return true;
	else
	{
		printf("It is not a DAG.\n");						//若该图不是有向无环图，那么返回错误报告
		return false;
	}
}

void critical_path(PLgragh pLG)
{
	int* ltv;												//创建指向事件最晚发生时间数组的指针
	int i;

	ltv = (int*)malloc(pLG->num_ver * sizeof(int));
	if (!ltv)
		exit(-1);
	topsort(pLG);											//调用拓扑排序函数，得到拓扑栈（或者是其他容器用来存放拓扑序列）和时间最早发生时间数组
	for (i = 0; i < pLG->num_ver; i++)
		ltv[i] = etv[pLG->num_ver - 1];						//初始化事件最晚发生时间数组ltv，使其为最大值（即终点的时间最早发生时间，因为终点的事件最早和最晚是相同的）

	while (!is_emptystack(&S_top))							//使用拓扑栈生成事件最晚发生时间数组
	{
		pop_Stack(&S_top, &i);
		PEdgeNode p = pLG->adjlist[i].firstedge;
		while (p)
		{
			int k = p->adjvertex;
			if (ltv[i] > ltv[k] - p->weight)				/*若当前顶点的最晚发生时间>其邻接点的最晚发生时间ltv[k]-连接的边的权重，说明该顶点若按照目前数组中的最晚发生时间，
															必然会导致其邻接点事件发生延迟，所以要更新这个顶点的最晚发生时间（其实就是提前这个ltv）*/
				ltv[i] = ltv[k] - p->weight;
			p = p->pNext;
		}
	}

	for (i = 0; i < pLG->num_ver; i++)						//遍历所有顶点！
	{
		PEdgeNode p = pLG->adjlist[i].firstedge;
		while (p)
		{
			int k = p->adjvertex;
			int ete = etv[i];								//活动的最早开工时间=弧尾顶点的最早发生时间
			int lte = ltv[k] - p->weight;					//活动的最晚发生时间=弧头顶点的最晚发生时间-该弧的权重
			if (ete == lte)									//如该顶点的到其邻接点的弧的活动最早、最晚开工时间相同就将该弧加入关键路径并打印
				printf("V%d(%c)->V%d(%c) and weight=%d.\n", i, pLG->adjlist[i].data,
					k, pLG->adjlist[k].data, p->weight);
			p = p->pNext;
		}
	}
	
	destroy_Stack(&S_top);
	free(etv);
	free(ltv);
}