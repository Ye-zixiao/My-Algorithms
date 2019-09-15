#include<stdio.h>
#define MAXSIZE 20
const int F[MAXSIZE] = { 0,1,1,2,3,5,8,13,21,34, };

int Interpolation_Search(int* arr, int n, int key);										//插值查找
int Fibonacci_Search(int* arr, int n, int key);											//斐波那契查找
int Binary_Search(int* arr, int n, int key);											//二分查找
int Sequential_Search(int* arr, int n, int key);										//顺序查找
int Sequential_Search2(int* arr, int n, int key);										//优化后的顺序查找（增加了哨兵检查i是否越界）

int main(void)
{
	int arr[MAXSIZE] = { 0,1,16,24,35,47,59,62,73,88,99 };
	int n= Binary_Search(arr, 10, 59);
	printf("Number in the array of 59 is %d.（Binary_Search）\n", n);
	n = Interpolation_Search(arr, 10, 59);
	printf("Number in the array of 59 is %d.(Interpolation_Search)\n", n);
	n = Fibonacci_Search(arr, 10, 59);
	printf("Number in the array of 59 is %d.(Fibonacci_Search)\n", n);

	return 0;
}

int Sequential_Search(int* arr, int n, int key)
{
	int i;
	for (i = 1; i < n; i++)
	{
		if (arr[i] == key)
			return i;
	}
	return 0;
}

int Sequential_Search2(int* arr, int n, int key)
{
	int i=n;
	arr[0] = key;							//设立一个哨兵arr[0]使得不断向下查找时不用像普通查找一样担心i越界的问题
	while (arr[i] != key)
		i--;
	return i;
}


int Binary_Search(int* arr, int n, int key)
{
	int low, high, mid;
	low = 1;
	high = n;
	while (low <= high)
	{
		mid = (low + high) / 2;
		if (key < arr[mid])
			high = mid - 1;
		else if (key > arr[mid])
			low = mid + 1;
		else
			return mid;
	}
	return 0;
}

int Interpolation_Search(int* arr, int n, int key)										//n代表的是有效数组元素中的最大下标
{
	int low, high, mid;
	low = 1;
	high = n;
	while (low <= high)
	{
		mid = low + (high - low) * (key - arr[low]) / (arr[high] - arr[low]);			/*插值查找的原理就是根据插值公式去判断所查找的数据在顺序表中的分布
																						（是分布在靠前的部分还是靠后的部分，还是中间部分，这些完全可以由插值公式判断）
																						，然后从这个大致的判断位置出发去重复上述方法查找那个数据是否在顺序表中存在。
																						但是有一点就是插值查找很依赖顺序表中的元素是均匀分布的，不然就会效率很低*/
		if (key < arr[mid])
			high = mid - 1;
		else if (key > arr[mid])
			low = mid + 1;
		else
			return mid;
	}
	return 0;
}

int Fibonacci_Search(int* arr, int n, int key)
{
	int low, high, mid;
	low = 1;
	high = n;
	int k = 0;
	while (n > F[k] - 1)							//根据当前有效元素的长度去找一个合适的稍微大一点的斐波那契数，记录它在斐波那契数组中的下标k
		k++;
	for (int i = n; i <= F[k] - 1; i++)				//若得到的斐波那契数大于当前数组有效元素的长度，那么为了查找的必要性就需要将右边的部分补成arr[n]
		arr[i] = arr[n];

	while (low <= high)
	{
		mid = low + F[k - 1] - 1;					/*斐波那契查找的原理就是：把数组中长度为F[k]-1区域分成 长度为F[k-1]-1的左半区 和 长度为F[k-2]-1的右半区，
													以及一个处于中间的mid元素。若key<mid，那么就继续在左半区查找；若key>mid，那么就继续在右半区查找；若正好是mid就返回*/
		if (key < arr[mid])
		{
			high = mid - 1;							//把high改成左半区的最大值
			k = k - 1;								//最好写成k = k - 1;这样意思更明了
		}
		else if (key > arr[mid])
		{
			low = mid + 1;							//把low改成右半区的最小值
			k = k - 2;
		}
		else
		{
			if (mid <= n)
				return mid;
			else
				return n;							//若得到的mid大于n，说明程序查找在补足区匹配到了arr[n]
		}
	}
	return 0;
}