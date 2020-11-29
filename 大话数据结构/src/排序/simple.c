//简单排序函数部分
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"sort.h"

/*=========================简单交换排序==============================*/
void Swap_Sort(pSqList psl)
{
	int i, j;
	for (i = 0; i < psl->length - 1; i++)					//最笨的方法
		for (j = i + 1; j < psl->length; j++)
			if (psl->parr[i] > psl->parr[j])
				swap(psl->parr, i, j);
}


/*========================冒泡排序=======================================*/
void Bubble_Sort(pSqList psl)
{															/*冒泡排序算法：
																从下到上两两比较将两者的较小值依次放到上面，每一个j循环可将最小值找出放到本次比较范围的最上面*/
	int i, j;
	for (i = 0; i < psl->length; i++)
		for (j = psl->length - 1; j > i; j--)
			if (psl->parr[j - 1] > psl->parr[j])			//前者大于后者就交换数据
				swap(psl->parr, j - 1, j);

}

void Bubble_Sort_Improved(pSqList psl)
{
	int i, j;
	bool flag = true;

	for (i = 0; flag && i < psl->length; i++)					//当遍历一轮后标志位仍然是false说明已经排序好了
	{
		flag = false;										//设置一个标志位，如果一个循环遍历过程中有交换数据的过程说明至少在结束这轮之前还没有排好序
		for (j = psl->length - 1; j > i; j--)
			if (psl->parr[j - 1] > psl->parr[j])
			{
				swap(psl->parr, j - 1, j);
				flag = true;
			}
	}
}


/*================================选择排序====================================*/
void Selection_Sort(pSqList psl)
{															/*选择排序算法思路：
																从数组low到high之间找出最小值（若不是low下标本身那个数），那么将这个最小值与
																low下标的元素交换数据，然后low自加1缩小比较排序范围*/
	int i, j;
	for (i = 0; i < psl->length; i++)
	{
		int min = Find_Min(psl->parr, i, psl->length - 1);
		if (i != min)
			swap(psl->parr, i, min);
	}
}

int Find_Min(int* arr, int low, int high)					//从数组low到high范围中找出最小值并返回它的下标
{
	int i;
	int min = low;
	for (i = low + 1; i <= high; i++)
		if (arr[i] < arr[min])
			min = i;
	return min;
}


/*================================直接插入排序=====================================*/
void Insertion_Sort(pSqList psl)
{																		/*直接插入排序核心思想：
																			对于一个数组从第二个元素开始，第一个元素认为已经有序，对前二个元素排序等价于
																		将第二个元素插入到前一个元素的某一个位置（前或后），使之保持有序；对前三个元素排序等价于
																		将第三个元素插入到前2个元素的某一个位置，使之保持有序；。。。。*/
	int i;
	int temp;

	for (i = 1; i < psl->length; i++)
	{
		if (psl->parr[i - 1] > psl->parr[i])							/*该判断句的目的就是：避免当前n个元素已经有序时，插入第n+1个元素且这个元素大于前一个数（即前面所有的数）
																			时进入语句块进行无意义的操作。如：1、2、3后要插入4*/
		{
			temp = psl->parr[i];
			int pos;

			for (pos = i; pos >=1 && psl->parr[pos - 1] > temp; pos--)	//如果第n个数小于前面的数，就将前面大于它的数一次向后移位
				psl->parr[pos] = psl->parr[pos - 1];
			psl->parr[pos] = temp;										//然后将这个数插入到直到小于它的数后面
		}
	}
}
