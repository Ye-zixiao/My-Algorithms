//									汉诺塔游戏
#include<stdio.h>

void tower_of_hanoi(int n, char A, char B, char C);

int main(void)
{
	int n;
	printf("请输入A柱上放的盘子数: ");
	scanf("%d", &n);

	tower_of_hanoi(n, 'A', 'B', 'C');

	return 0;
}

void tower_of_hanoi(int n, char A, char B, char C)
{
	/*
	如果A柱子上只有一个盘子n
		就将数字n从A直接放到C；
	否则
		先将n-1个盘子从A借助C放到B中
		然后将A中的盘子直接放到C中
		最后将B中的n-1个盘子借助A放到C中
	*/
	if (1 == n)
		printf("将数字%d从柱子%c放到柱子%c\n", n, A, C);
	else
	{
		tower_of_hanoi(n - 1, A, C, B);
		printf("将数字%d从柱子%c放到柱子%c\n", n, A, C);
		tower_of_hanoi(n - 1, B, A, C);
	}
}

/*
原理：
将A柱子中的n个盘子借助C柱子移到B柱子中的原理和本质和
把A柱子中的n-1个盘子借助C柱子移动到B柱子中的原理和本质四一致的，
		但问题的规模却是在不断减小的。
*/
