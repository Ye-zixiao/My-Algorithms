//较复杂的排序函数部分
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"sort.h"


/*=====================快速排序================================*/
void Quick_Sort(pSqList psl)								//封装下样子
{
	Qsort(psl->parr, 0, psl->length - 1);
}

/*快速排序使用的就是分而治之的思想：采用递归按枢轴将左右两边分开，分别再次递归使用快速排序。*/
void Qsort(int* arr, int low, int high)
{
	int pivot;												//枢轴：在数组中，枢轴的左边的元素数据都小于枢轴元素的数据，在枢轴的右边元素的数据都大于枢轴的数据
	if (low < high)
	{
		pivot = Partition(arr, low, high);					//计算出枢轴下标
		Qsort(arr, low, pivot - 1);							//递归左部分
		//Qsort(arr, pivot + 1, high);						//递归右部分
		low = pivot + 1;									//这一步代码对快速排序进行了优化，这样的好处就是减少了递归深度，提高了系统性能
															//这样的话当前面的递归将枢轴左半部分快速排序完成后low = pivot + 1;可以使得再次进入循环完成右半部分的快排
	}
}

int Partition(int* arr, int low, int high)
{
	//int temp = arr[low];									//假设枢轴是该范围段的首元素
	int pos = Mid_of_Three(arr, low, high);
	int temp = arr[pos];									//三数取中法，确保枢轴数有更大的概率取到中间数
	while (low < high)
	{
		while (low < high && arr[high] >= temp)				//当high的数据小于枢轴，就将该数据赋给下标为low的元素，然后high自减
			high--;											//注意：是小于等于号，这样避免了当数据为1、1、1、1、1、4、3这种数据枢轴过于偏左或者偏右，枢轴最合理就是位于中间
		arr[low] = arr[high];
		while (low < high && arr[low] <= temp)				//当low的数据大于枢轴，就将该数据赋给下标为high的元素，然后low自增
			low++;
		arr[high] = arr[low];
															/*显然当low=high必然会退出循环体，此时将枢轴元素数据放到该low（或者high）位，
															使得枢轴左部分的数据都小于枢轴，有部分的数据都大于枢轴*/
	}
	arr[low] = temp;
	return low;
}

int Mid_of_Three(int* arr, int low, int high)
{
	int mid = low + (high - low) / 2;
	if (arr[low] > arr[high])						//将low和high位置上较大的数放到high位置上
		swap(arr, low, high);
	if (arr[mid] > arr[high])						//将mid和high中较大的数放到high位置上，此时high位置上放的必然是三个数中间最大的数
		swap(arr, mid, high);
	if (arr[low] < arr[mid])						//将low和mid中较大的数放到low位置上，这样low位置上必然是三个数中的中间值
		swap(arr, mid, low);
	return low;
}


/*==================================希尔排序===============================*/
void Shell_Sort(pSqList psl)
{
	int temp;
	int increment;
	for (increment = psl->length / 3 + 1; increment > 1; increment = increment / 3 + 1)					//计算希尔序列D（k）=D（k+1）/3+1；
	{
		int i;
		for (i = increment; i < psl->length; i++)														//对每隔D（k）的元素进行排序
		{
			temp = psl->parr[i];
			int pos;
			for (pos = i; pos >= increment && psl->parr[pos - increment] > temp; pos -= increment)		//至少要保证pos大于increment，这样就能使pos - increment下标的元素与temp比
				psl->parr[pos] = psl->parr[pos - increment];											//对于大于tmep的元素，依次向后移动一个增量位
			psl->parr[pos] = temp;																		//将temp放到小于它的位置后面
		}
	}
	/*直接插入排序的时间复杂度是其数据规模和序列逆序对个数的函数T(N)=O(N+I)。
		希尔排序就是直接插入排序的优化版，由于直接插入排序每一次排序都是基于前后元素两两比较，每一次数据交换都只会减少一个逆序对；
	所以需要提高算法效率，就不得不考虑如何在一次数据交换中就能够减少大于一个的逆序对！
		由于每一次直接插入排序是基于两两比较的，那么我可不可以先每一次交换相隔较远的元素，使每一次交换相隔较远的元素就能消除大于一个的逆序对
	，然后相应的减少这个相邻的间隔。使得元素序列在每一个交换中有序度提高，在最后一次之前达到基本有序，最后当这个间距减少到1，就变成了直接插入排序。此时做直接插入
	排序，由于逆序对大幅度减少，所以排序效率也大幅度提高。
	希尔排序的思想：
		1、对每相隔一定增量的原始序列进行直接插入排序。比如：9、8、7、6、5、4、3、2、1，此时最初的增量是4，
			那么先对9、6插入排序，然后对6、9、3插入排序，但注意每次不是对9、6、3这样的序列直接排序完，而是同其他序列一同排序。
			这里要特别理解下for (i = increment; i < psl->length; i++)为什么是i++而不是+=increment。
		2、然后将这个增量减小，重复1、的步骤；
		3、当增量减少到1时，即变成了直接插入排序，完成这一轮后就是结束了排序。
	*/
}


/*========================================堆排序===================================*/
void Heap_Sort(pSqList psl)
{
	int i;
	for (i = psl->length / 2 - 1; i >= 0; i--)						//将原始数组调整成最大堆的形式
		Max_Heap_Adjust(psl->parr, i, psl->length);

	for (i = psl->length - 1; i >= 0; i--)
	{
		swap(psl->parr, 0, i);										//将最大堆中的首元素的数据和当前长度为i+1的最后一个元素（下标为i）的元素进行交换
		Max_Heap_Adjust(psl->parr, 0, i);							//交换后将最大堆的元素长度自减一，对最大堆首元素进行调整
	}
}

/*堆排序正是利用了完全二叉树的性质，使得其在描述上是使用了二叉树的形式去描述，但是在组织
存储形式上还是使用了数组的形式去完成。
		算法形式：
			1、将数组构建成最大堆的形式；
			2、for（每一个结点）
				{
					将当前最大堆的堆顶元素与堆的最后一个元素进行交换；
					将堆的长度-1；
					重新对最大堆的堆顶元素进行调整；
				}
			*/

void Max_Heap_Adjust(int* arr, int i, int length)
{
	int j=i;
	int temp = arr[i];											//假设最大堆首元素下标为i，并将首元素的数据进行暂存

	for (j = 2 * i + 1; j <= length - 1; j = 2 * j + 1)			//得到该首元素的左孩子的下标
	{
		if (j<length - 1 && arr[j + 1]>arr[j])					//若该左孩子有右兄弟，比较两者，若右兄弟大，就将下标换成右兄弟的下标
			j++;
		if (temp > arr[j])										//若当前结点的两个孩子都比它小，就退出循环，什么也不做
			break;
		arr[i] = arr[j];										//否则就是孩子中有一个最大数大于它的双亲结点，就将这个最大值赋给双亲结点
		i = j;													//然后重新设置这个孩子结点为当前循环需要判断的结点
	}
	arr[i] = temp;												//最后将原来的首元素的数据插入到双亲结点大于它，孩子节点小于它的位置
}


/*====================================归并排序（递归方法）====================================*/
void Merge_Sort(pSqList psl)
{
	int* ptemp= (int*)malloc(sizeof(int) * psl->length);		//创建一个临时数组用以存放中间的有序子列结果
	if (!ptemp)
		exit(-1);
	Msort(psl->parr, ptemp, 0, psl->length - 1);				//调用Msort函数对psl->parr数组进行排序，排序范围从0到psl->length - 1，tmep_arr存放中间结果
	free(ptemp);
}

void Msort(int* arr, int* temp_arr, int low, int high)
{
	int mid;
	if (low == high)
		temp_arr[low] = arr[low];								//当数组拆到只剩下单个元素时，就将该元素存到临时数组当中
	else
	{
		mid = (low + high) / 2;									//计算中间数
		Msort(arr, temp_arr, low, mid);							//递归调用处理左半部分，使得临时数组和目标数组中的数据（同时）有序
		Msort(arr, temp_arr, mid + 1, high);					//递归调用处理右半部分
		Merge(temp_arr, arr, low, mid, high);					//将临时数组中左右各自有序的子列的数据排序进目标数组，使得整个low到high的范围内有序。
	}															//注意：临时数组在这个范围内也会变得有序
}

void Merge(int* temp_arr, int* arr, int low, int mid, int high)
{
	int i, j;
	int k;
	for (i = low, j = mid + 1, k=low; i <= mid && j <= high;k++)
	{															/*左右两个子序每一次循环中，取其中最小的数放到目标数组中，然后取得那组数组
																的下标位自增。显然最后剩下的数据一定会比已经放进去的数据大。			*/
		if (temp_arr[i] < temp_arr[j])
			arr[k] = temp_arr[i++];
		else
			arr[k] = temp_arr[j++];
	}

	while (i <= mid)											//若经过上面的循环后有一组数组还有数据没有存放进目标数组（另一组必然已经全部放进去了），那么将剩下的放进目标数组
	{
		arr[k] = temp_arr[i++];
		k++;
	}
	while (j <= high)
	{
		arr[k] = temp_arr[j++];
		k++;
	}

	for (k = low; k <= high; k++)								//当目标数组有序后，将该数组的数据复制给临时数组，目的是为了递归结束后给上一级的函数使用
		temp_arr[k] = arr[k];
														/*这种方法使得归并排序时每次递归时不会重新创建一个临时数组来存放中间结果，但是不可避免地时间效率下降了不少，
														它牺牲了时间复杂度，来换取空间复杂度的提高；如果每一次递归时都创建一个临时数组存放中间结果，等到递归结束后
														释放，这样的话当递归深度不断提高时，内存中的栈空间也会被消耗不少，但是时间效率却提高了不少。这种方法牺牲了
														空间复杂度换取了时间复杂度的提高。（就如同课本那样）
														*/
}


/*=====================================归并排序（非递归方法）================================*/
void Merge_Sort_nonrecursion(pSqList psl)
{
	int* ptemp = (int*)malloc(sizeof(int) * psl->length);
	if (!ptemp)
		exit(-1);
	int k = 1;
	while (k < psl->length)
	{																			/*先按照对子序列以长度为1这样两两归并，然后按照子序列长度为2这样两两归并
																					然后按照长度为4的两两归并。。。，直到子序列长度变得比整个数组长度大时退出*/
		k_length_Seqmerge(psl->parr, ptemp, k, psl->length);					//先将原始数组中以子序列长度为k两两归并到临时数组当中
		k *= 2;
		k_length_Seqmerge(ptemp, psl->parr, k, psl->length);					//再将临时数组中以子序列长度为2k两两归并到原始数组当中
		k *= 2;
	}
	free(ptemp);
}

void k_length_Seqmerge(int* source_arr, int* target_arr, int k, int length)
{
	int i;
	for (i = 0; i + 2 * k <= length; i += 2 * k)							//i + 2 * k <= length成立说明原始数组可以两两归并
		Merge2(source_arr, target_arr, i, i + k - 1, i + 2 * k - 1);

	if (i + k < length)														//归并剩下的两个子序列（其中一个子序列长度不到k）
		Merge2(source_arr, target_arr, i, i + k-1, length - 1);
	else
		for (; i < length; i++)												//当剩下的数组中只有一个子序列（长度不到k）时，直接将这个序列复制到目标数组当中
			target_arr[i] = source_arr[i];
}

void Merge2(int* source_arr, int* target_arr, int low, int mid, int high)
{																			//对low到mid和mid+1到high的两个子序列归并，放到目标数组当中（原数组不会改动，这点与递归时的函数不同）
	int i, j;																
	int k;
	for (i = low, j = mid + 1, k = low; i <= mid && j <= high; k++)
	{
		if (source_arr[i] < source_arr[j])
			target_arr[k] = source_arr[i++];
		else
			target_arr[k] = source_arr[j++];
	}

	while (i <= mid)
		target_arr[k++] = source_arr[i++];
	while (j <= high)
		target_arr[k++] = source_arr[j++];
}