#pragma once
#ifndef SORT_H_
#define SORT_H_

typedef struct sqlist {										//创建使用结构（一个普通的顺序表）
	int* parr;
	int length;
}SqList, * pSqList;

void Create_SqList(pSqList psl);							//为结构中的数组输入数据
void swap(int* arr, int i, int j);							//交换两个数组元素的数据
void show_data(pSqList psl);

void Swap_Sort(pSqList psl);								//普通交换排序
void Bubble_Sort(pSqList psl);								//冒泡排序
void Bubble_Sort_Improved(pSqList psl);						//优化后的冒泡排序算法:避免对已经排好序的序列重复比较排序
int Find_Min(int* arr, int low, int high);					//返回数组下限low到上限high之间的最小值下标
void Selection_Sort(pSqList psl);							//简单选择排序
void Insertion_Sort(pSqList psl);							//直接插入排序（也有优化代码）

void Quick_Sort(pSqList psl);								//封装好的快速排序
void Qsort(int* arr, int low, int high);					//真正对快速排序有作用的函数：用于递归使用
int Partition(int* arr, int low, int high);					//返回枢轴下标，同时也会起到排序的作用
int Mid_of_Three(int* arr, int low, int high);				//三数取中函数

void Shell_Sort(pSqList psl);								//希尔排序
void Heap_Sort(pSqList psl);								//堆排序
void Max_Heap_Adjust(int* arr, int i,int length);			//最大堆调整

void Merge_Sort(pSqList psl);									//归并排序（递归）
void Msort(int* arr, int *temp_arr, int low, int high);			//专门用于递归使用的归并排序函数
void Merge(int* temp_arr, int* arr, int low, int mid, int high);//将两个子列归并，归并完后原数组和临时数组都有序

void Merge_Sort_nonrecursion(pSqList psl);										//归并排序（非递归）
void k_length_Seqmerge(int* source_arr,int *target_arr,int k, int length);		//对长度为k的子序列两两归并到目标数组当中
void Merge2(int* source_arr, int* target_arr, int low, int mid, int high);		//对low到mid和mid+1到high的两个子序列归并，放到目标数组当中（原数组不会改动，这点与递归时的函数不同）

#endif