#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"sort.h"

int main(void)
{
	SqList sql;

	Create_SqList(&sql);
	//Swap_Sort(&sql);
	//Bubble_Sort(&sql);
	//Selection_Sort(&sql);
	//Bubble_Sort_Improved(&sql);
	//Insertion_Sort(&sql);
	//Quick_Sort(&sql);
	//Shell_Sort(&sql);
	//Heap_Sort(&sql);
	//Merge_Sort(&sql);
	Merge_Sort_nonrecursion(&sql);
	show_data(&sql);

	free(sql.parr);
	return 0;
}