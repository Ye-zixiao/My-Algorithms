#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define MAXSIZE 20																	/*静态链表有个问题我发现就是：当静态链表满时比较麻烦，书上也没有详细的说明*/
																					//所以尽可能要让数组的长度大一点
typedef struct node {
	int data;
	int cur;
}StaticLinklist[MAXSIZE];

void create_StaticLinklist(StaticLinklist arr);										//创建静态链表，并要求输入数据
int length_StaticLinklist(StaticLinklist arr);										//计算链表长度
bool is_empty(StaticLinklist arr);													//判断链表是否为空
bool is_full(StaticLinklist arr);													//判断链表是否为满
bool insert_StaticLinklist(StaticLinklist arr, int pos, int value);					//插入一个数值到链表当中
bool delete_StaticLinklist(StaticLinklist arr, int pos, int* value);				//删除一个链表元素，并将数据返回到指针value当中
int malloc_node(StaticLinklist arr);												//将一个空闲链表（第一个备份链表元素）的结点分配到数据链表当中。 **这个函数与书上的不同
void free_node(StaticLinklist arr, int k);											//将一个选中的数据链表结点处理到空闲链表中
void sort_StaticLinklist(StaticLinklist arr);										//使用选择排序法以升序将链表重新排列
void show_StaticLinklist(StaticLinklist arr);										//打印输出链表中的所有元素
int Getelem_StaticLinklist(StaticLinklist arr, int pos);							//获取一个数据链表中的数据

int main(void)
{
	StaticLinklist arr;																//创建了一个结构数组，而这个arr就是结构数组名，事实上是一个指针（个人见解）
	int value;

	create_StaticLinklist(arr);														//赋给函数的就是传递了结构数组的指针
	printf("You enter a static linked list:\n");
	show_StaticLinklist(arr);

	if (insert_StaticLinklist(arr, 2, 34))
		printf("Inserting success.\n");
	else
		printf("Error in inserting.\n");
	if(insert_StaticLinklist(arr, 1, 99))
		printf("Inserting success.\n");
	else
		printf("Error in inserting.\n");
	printf("After inserting: \n");
	show_StaticLinklist(arr);

	printf("After deleting:\n");
	if (delete_StaticLinklist(arr, 4, &value))
		printf("You deletes member %d and its value is %d.\n", 4, value);
	else
		printf("No data deletes.\n");
	show_StaticLinklist(arr);

	sort_StaticLinklist(arr);
	printf("After sorting:\n");
	show_StaticLinklist(arr);
	printf("The value of member %d is %d\n", 3, Getelem_StaticLinklist(arr, 3));

	return 0;
}

void create_StaticLinklist(StaticLinklist arr)
{
	int len;
	int i;

	printf("Enter the length of Static Link list: ");
	scanf("%d", &len);
	if (len > MAXSIZE - 2)											//检错模块,这个也是我经常在想的就是好像静态链表就只能最多放MAXSIZE-2个数据
	{
		printf("No enough room to put data.\n");
		exit(EXIT_FAILURE);
	}

	for (i = 0; i < MAXSIZE - 1; i++)								//先将链表中的所有元素的游标设置为空表时的状态
		arr[i].cur = i + 1;
	arr[MAXSIZE - 1].cur = 0;										//除了最后一个游标要设置为0，表示当前为空表

	for (i = 1; i <= len; i++)										//进入用户输入环节
	{
		printf("Enter the data for member %d: ", i);
		scanf("%d", &arr[i].data);
	}
	arr[MAXSIZE - 1].cur = 1;										//初始化时，将链表的最后一个元素的游标指向数据链表第一个元素的下标
	arr[i - 1].cur = 0;												//最后一个数据链表的游标要设置为0
	arr[0].cur = i;													//链表第一个元素的游标设置为备用链表的第一元素的下标
}

int length_StaticLinklist(StaticLinklist arr)
{
	int len = 0;
	int i = arr[MAXSIZE - 1].cur;

	while (i)														//在没有遇到静态链表中的最后一个元素的0游标之前，可以循环进入while中
	{
		i = arr[i].cur;
		len++;
	}
	return len;
}

bool is_empty(StaticLinklist arr)
{
	if (arr[MAXSIZE - 1].cur == 0)									//判断链表最后一个元素的游标是否为0
		return true;
	else
		return false;
}

bool is_full(StaticLinklist arr)
{
	if (length_StaticLinklist(arr)>=MAXSIZE-2)						//判断链表长度是否为MAXSIZE-1，如果是那么就是已满
		return true;
	else
		return false;
}

int malloc_node(StaticLinklist arr)									//从备份链表中取出一个空闲元素以备存储数据使用
{
	int i = arr[0].cur;

	if (!is_full(arr))												//分配前先检查链表是否满了，如果满了就不分配空间了。   //老版本是：if(i)
	{
		arr[0].cur = arr[i].cur;									//如果还有空间那么就将备份链表第一元素的下标（指向下一个备份链表元素）赋给链表第一元素的下标
		return i;
	}
	else
		return 0;
}

void free_node(StaticLinklist arr, int k)
{
	arr[k].cur = arr[0].cur;										//将原先备份链表的第一个元素的下标赋给将从数据链表中删除的元素的游标，
	arr[0].cur = k;													//使删除元素成为备份链表的首元素
}

bool insert_StaticLinklist(StaticLinklist arr, int pos, int value)
{
	int i, k;
	k = MAXSIZE - 1;
	if (pos<1 || pos>length_StaticLinklist(arr) + 1)				//检错模块，注意这是可以在末尾插入的
		return false;

	int j = malloc_node(arr);
	if (j)															//查看空闲链表是否还有空间以供使用,如果链表满了就不能再插入了
	{
		for (i = 1; i < pos; i++)									//找出插入位置的前一个元素！！！
			k = arr[k].cur;

		arr[j].data = value;										//先给新添的元素数据域赋值
		arr[j].cur = arr[k].cur;									//使新添元素的游标赋上上一个元素的游标，使其可以指向刚被插入元素（原来的第pos位）
		arr[k].cur = j;												//将新添的元素的下标赋给上一个元素的游标
		return true;
	}
	else
		return false;
}

bool delete_StaticLinklist(StaticLinklist arr, int pos, int* value)
{
	int i, j, k;
	k = MAXSIZE - 1;
	if (pos<1 || pos>length_StaticLinklist(arr))
		return false;

	for (i = 1; i < pos; i++)										//找出插入位置的前一个元素！！！
		k = arr[k].cur;
	j = arr[k].cur;													//注意：第pos个元素的位置不一定就在数据链表的第pos个位置上。  找出第pos个元素的下标
	*value = arr[j].data;											//返回删除值
	arr[k].cur = arr[j].cur;										//跳过一个元素赋给下标给上一个元素的游标
	free_node(arr, j);												//重新使删除元素分配到备份链表中
	return true;
}

void sort_StaticLinklist(StaticLinklist arr)
{
	int top, seek;
	int i, j;

	for (top = 0, i = arr[MAXSIZE - 1].cur; top < length_StaticLinklist(arr) - 1; top++, i = arr[i].cur)			//选择排序法升序排列，基本上与动态单链表、顺序存储结构的算法一致
		for (seek = top + 1, j = arr[i].cur; seek < length_StaticLinklist(arr); seek++, j = arr[j].cur)		//，只是在细节上由于存储形式不同导致了操作的不同
			if (arr[i].data > arr[j].data)
			{
				int temp = arr[i].data;
				arr[i].data = arr[j].data;
				arr[j].data = temp;
			}
}

void show_StaticLinklist(StaticLinklist arr)
{
	int k = arr[MAXSIZE - 1].cur;																//为什么静态链表老是要从arr[MAXSIZE-1].cur开始？
	//printf("k=%d\n", k);																		//因为arr结构数组（或者说是链表的）最后一个元素就是静态链表的头结点
	while (k)
	{
		printf("%d ", arr[k].data);
		k = arr[k].cur;
	}
	putchar('\n');
}

int Getelem_StaticLinklist(StaticLinklist arr, int pos)
{
	int i, k;
	k = MAXSIZE - 1;
	if (pos<1 || pos>length_StaticLinklist(arr) + 1)
		return -1;

	for (i = 1; i <= pos; i++)
		k = arr[k].cur;
	return arr[k].data;
}

//有下面的程序可知：定义一个结构数组类型，并将结构类型的变量以	function(StaticLinklist arr)的形式将结构数组的传入，
//表面上看传入的是结构数组变量，其实事实上传入的是一个指向结构数组的指针arr

/*
#include<stdio.h>

typedef struct node{
	int data;
	int cur;
}StaticLinklist[3];

int sum(struct node arr[],int n);
int main(void)
{
	StaticLinklist arr = {
		{1,2},{3,4},{5,6}
	};
	printf("The sum of arr data is %d\n", sum(arr, 3));

	return 0;
}

int sum(struct node arr[], int n)//StaticLinklist生命的数组传入到函数的是一个指向函数的指针（数组名）
{
	int i;
	int sum = 0;

	for (i = 0; i < n; i++)
		sum += arr[i].data;
	return sum;
}
*/