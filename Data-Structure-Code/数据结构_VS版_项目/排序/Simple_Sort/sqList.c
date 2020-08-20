//关于对顺序表的建立以及相关的输出函数部分
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"sort.h"

void Create_SqList(pSqList psl)
{
	printf("Enter the length of the array: ");
	scanf("%d", &psl->length);
	psl->parr = (int*)malloc(psl->length * sizeof(int));
	if (!psl->parr)
		exit(-1);
	for (int i = 0; i < psl->length; i++)
	{
		if (!i)
			printf("Enter the first data: ");
		else if (i == psl->length - 1)
			printf("Enter the last one: ");
		else
			printf("Enter the next one: ");
		scanf("%d", &psl->parr[i]);
	}
}

void swap(int* arr, int i, int j)
{
	int temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

void show_data(pSqList psl)
{
	for (int i = 0; i < psl->length; i++)
		printf("%d ", psl->parr[i]);
	putchar('\n');
}
