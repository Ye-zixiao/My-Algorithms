/*----------顺序存储结构-线性表------*/
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<malloc.h>

typedef struct Arr {                                            //用typedef声明一个结构类型
	int* pArray;
	int len;
	int cnt;
}SqList;

void init_arr(SqList* pArr,int size);                           //顺序存储初始化：为数组分配动态内存
bool append_arr(SqList* pArr,int value);                        //追加模式：给链表的后面加上一个数据
bool insert_arr(SqList* pArr, int i,int value);                 //插入模式
bool delete_arr(SqList* pArr, int i, int* Back_value);          //删除操作，并返回Back_value
bool Getelem(SqList* pArr, int i,int *Back_value);              //查找操作
bool is_empty(SqList* pArr);                                    //判断链表是否已满
bool is_full(SqList* pArr);                                     //判断链表是否为空
void show_arr(SqList* pArr);                                    //显示输出链表
void sort_arr(SqList* pArr);                                    //对链表中的元素进行排序
void inverse_arr(SqList* pArr);                                 //对链表中的元素进行倒置
void free_arr(SqList* pArr);                                    //是否先前的为数组分配的动态内存

int main(void)
{
	SqList arr;
	int value;

	init_arr(&arr,6);                                           //初始化
	show_arr(&arr);

	append_arr(&arr, 1);                                        //现在末尾追加四个数据
	append_arr(&arr, 2);
	append_arr(&arr, 3);
	append_arr(&arr, 4);
	show_arr(&arr);

	insert_arr(&arr, 3, 88);                                    //在第三个位置插入一个元素
	show_arr(&arr);
	if (Getelem(&arr, 4, &value))                               //查找第四个元素，并返回结果和数据
		printf("I get a element %d\n", value);
	else
		printf("No data gets.\n");
	inverse_arr(&arr);                                          //将数据倒置
	show_arr(&arr);

	sort_arr(&arr);                                             //对数据进行排序
	show_arr(&arr);
	if (delete_arr(&arr, 3, &value))                            //删除第三个元素
		printf("I deletes a element %d.\n", value);
	else
		printf("No data deletes.\n");
	show_arr(&arr);

	free_arr(&arr);                                                 //释放内存
	return 0;
}

void init_arr(SqList* pArr,int size)
{
	pArr->pArray = (int *)malloc(size*sizeof(int));
	if (!pArr->pArray)
	{
		printf("Can't assign dynamic memory for this program.\n");
		exit(EXIT_FAILURE);
	}
	else                                                        //内存分配成功就可以初始化其他的结构成员
    {
        pArr->cnt=0;
        pArr->len=size;
    }
}

void show_arr(SqList* pArr)
{
	if (is_empty(pArr))                                         //检查链表是否为空
		printf("There is no data in the array.\n");
	else
	{
		int i;
		for (i = 0; i < pArr->cnt; i++)
			printf("%d ", pArr->pArray[i]);
		putchar('\n');
	}
	return;
}

void free_arr(SqList* pArr)
{
    free(pArr->pArray);
	printf("Free the memory.\n");
}

bool is_full(SqList* pArr)
{
	if (pArr->cnt == pArr->len)
	    return true;
	else
        return false;
}

bool is_empty(SqList* pArr)
{
	if (pArr->cnt == 0)
		return true;
	else
		return false;
}

bool append_arr(SqList* pArr, int value)
{
	if (is_full(pArr)==true)                                    //在追加前检查链表是否已满
        return false;
	else
	{
		pArr->pArray[pArr->cnt] = value;                        //注意：追加是给最后一个元素的下一个空闲单元赋值
		(pArr->cnt)++;                                          //所以是cnt
		return true;
	}
}

bool Getelem(SqList* pArr, int i,int *Back_value)
{
	if (i<1 || i>pArr->cnt)                                     //检查错误的情况
	{
		printf("Error in getting data.\n");
		return false;
	}
	else
	{
		*Back_value = pArr->pArray[i - 1];                      //用指针向主调函数返回查找的数据
		return true;
	}

}

bool insert_arr(SqList* pArr, int i, int value)
{
	if (i<1 || i>pArr->cnt+1)                                   //在插入之前需要检查下是否处于错误情况
	{
		printf("Error in inserting.\n");
		return false;
	}
	if (is_full(pArr))
	{
		printf("There is no room for storing data.\n");
		return false;
	}
	int j;
	for (j = pArr->cnt-1; j >=i-1; j--)                         //注意：右移是从实际的数组下标cnt-1开始的，即最后一个元素
		pArr->pArray[j+1] = pArr->pArray[j];
	pArr->pArray[i-1] = value;
	pArr->cnt++;
	return true;
}

bool delete_arr(SqList* pArr, int i, int* Back_value)
{
	if (i<1 || i>pArr->cnt)
	{
		printf("Error in deleting data.\n");
		return false;
	}
	if (is_empty(pArr))
	{
		printf("There is no data in the array.\n");
		return false;
	}
	int j;
	*Back_value = pArr->pArray[i - 1];                          //在左移前先将数据赋给返回的指针变量所指的变量
	for (j = i ; j < pArr->cnt; j++)                            //注意：j最开始的计数值等于i
		pArr->pArray[j] = pArr->pArray[j+1];
	pArr->cnt--;
	return true;
}

void sort_arr(SqList* pArr)									    //利用冒泡法进行升序排序
{
	int top, seek;
	for(top=0;top<pArr->cnt-1;top++)
		for(seek=top+1;seek<pArr->cnt;seek++)
			if (pArr->pArray[top] > pArr->pArray[seek])
			{
				int temp = pArr->pArray[top];
				pArr->pArray[top] = pArr->pArray[seek];
				pArr->pArray[seek] = temp;
			}
}

void inverse_arr(SqList* pArr)
{
	int i;
	for (i = 0; i < pArr->cnt / 2; i++)                         //利用除法确定出需要循环的次数
	{
		int temp = pArr->pArray[pArr->cnt - i - 1];
		pArr->pArray[pArr->cnt - 1 - i] = pArr->pArray[i];
		pArr->pArray[i] = temp;
	}
}
