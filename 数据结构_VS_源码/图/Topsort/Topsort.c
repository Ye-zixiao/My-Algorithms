#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"topsort.h"

bool topsort_stack(PLgragh pLG);
bool topsort_queue(PLgragh pLG);

int main(void)
{
	LGragh LG;
	create_AdjListGragh(&LG);
	//topsort_stack(&LG);
	topsort_queue(&LG);								//使用队列实现作为容器

	destroy_LGragh(&LG);
	return 0;
}

/*拓扑排序伪算法：（方法有点像树的层序遍历）
	void topsort(图的带入度邻接表)
	{
		for（图的每一个顶点）
			if（入度 为0）
				V加入容器；
		while（容器不为空）
		{
			V出容器；
			输出操作；
			for（V的每一个邻接点）
				if（--入度==0）
					V的邻接点加入容器；
		}

		if（输出的顶点数与图本身的顶点数相同）
			return 成功；
		else
			Error 表明该图不是有向无环图（DAG）；
	}
 */

bool topsort_stack(PLgragh pLG)
{
	int i;
	int count = 0;
	STACK S;

	init_Stack(&S);
	for (i = 0; i < pLG->num_ver; i++)
		if (pLG->adjlist[i].indegree == 0)
			push_Stack(&S, i);

	while (!is_emptystack(&S))
	{
		pop_Stack(&S, &i);
		printf("%d(%c) ", i,pLG->adjlist[i].data);
		count++;
		PEdgeNode p = pLG->adjlist[i].firstedge;
		while (p != NULL)
		{
			if ((--pLG->adjlist[p->adjvertex].indegree) == 0)
				push_Stack(&S, p->adjvertex);
			p = p->pNext;
		}
	}
	putchar('\n');
	destroy_Stack(&S);

	if (count == pLG->num_ver)
		return true;
	else
	{
		printf("It is not DAG.\n");
		return false;
	}
}

bool topsort_queue(PLgragh pLG)
{
	int i;
	int count = 0;
	L_QUEUE LQ;

	init_LinkQueue(&LQ);
	for (i = 0; i < pLG->num_ver; i++)
		if (pLG->adjlist[i].indegree == 0)
			en_queue(&LQ, i);

	while (!is_emptyqueue(&LQ))
	{
		de_queue(&LQ, &i);
		printf("%d(%c) ", i, pLG->adjlist[i].data);
		count++;
		PEdgeNode p = pLG->adjlist[i].firstedge;
		while (p != NULL)
		{
			if ((--pLG->adjlist[p->adjvertex].indegree) == 0)
				en_queue(&LQ, p->adjvertex);
			p = p->pNext;
		}
	}
	putchar('\n');
	destroy_queue(&LQ);

	if (count == pLG->num_ver)
		return true;
	else
	{
		printf("It is not DAG.\n");
		return false;
	}
}