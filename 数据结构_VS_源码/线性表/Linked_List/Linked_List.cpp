#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct Node {
	int data;
	struct Node* pNext;
}NODE, * PNODE;

PNODE create_Linklist(void);											//创建链表
void traverse_Linklist(PNODE pHead);									//遍历链表
void Empty_Linklist(PNODE pHead);										//释放链表的全部内存
int length_List(PNODE pHead);											//计算链表的长度
bool is_empty(PNODE pHead);												//判断链表是否为空
bool insert_Linklist(PNODE pHead, int pos, int value);					//插入一个结点到链表当中
bool delete_Linklist(PNODE pHead, int pos, int* value);					//删除一个结点，并将返回值用指针形式带回到主调函数当中
void sort_Linklist(PNODE pHead);										//利用选择排序法将链表进行升序排序

int main(void)
{
	PNODE pHead;
	int value;
	int len;

	pHead = create_Linklist();											//创建链表，并要求输入值
	printf("The linkedlist shows at follow:\n");
	traverse_Linklist(pHead);											//遍历打印出链表中的数据
	len = length_List(pHead);
	printf("The length of linked List is %d.\n", len);

	insert_Linklist(pHead, 4, 33);										//插入一个数据
	insert_Linklist(pHead, 4, 98);
	printf("After inserting:\n");
	traverse_Linklist(pHead);

	sort_Linklist(pHead);												//排序
	printf("After sorting:\n");
	traverse_Linklist(pHead);

	if (delete_Linklist(pHead, 2, &value))								//删除一个数据
		printf("You delete node %d,and its data is %d.\n", 2, value);
	else
		printf("Error in deleting node %d.\n", 2);
	printf("After deleting:\n");
	traverse_Linklist(pHead);

	Empty_Linklist(pHead);												//将其重新变成空表
	free(pHead);														//最终释放全部的动态内存（这一步只释放了头结点的动态内存）

	return 0;
}

PNODE create_Linklist(void)
{
	PNODE pHead, pTemp;
	pHead = (PNODE)malloc(sizeof(NODE));								//创建头结点
	if (pHead == NULL)
	{
		printf("Can't assign dynamic memory for this program.\n");
		exit(EXIT_FAILURE);
	}
	pTemp = pHead;														//创建一个临时指向链表的最后一个结点的结构指针，当链表为空的时候头结点就是最后一个结点
	int Node_num;														//结点数量
	int i;
	int value;

	printf("Enter numbers of Node that you want to create: ");
	scanf("%d", &Node_num);
	for (i = 0; i < Node_num; i++)
	{
		printf("Enter the value for member %d: ", i + 1);
		scanf("%d", &value);
		PNODE p = (PNODE)malloc(sizeof(NODE));							//创建新的结点
		if (p == NULL)
		{
			printf("Can't assign dynamic memory for this Node.\n");
			exit(EXIT_FAILURE);
		}
		p->data = value;
		pTemp->pNext = p;												//尾插法：将新生成的结点的地址给上一个尾结点的指针域和临时结构指针pTemp
		pTemp = p;														//然后又让临时指针指向最后一个结点
	}
	pTemp->pNext = NULL;												//在退出循环的时候将尾结点的指针域置为NULL

	return pHead;
}

void traverse_Linklist(PNODE pHead)
{
	PNODE p;
	p = pHead->pNext;
	while (p != NULL)
	{
		printf("%d ", p->data);
		p = p->pNext;
	}
	putchar('\n');
}

void Empty_Linklist(PNODE pHead)
{
	PNODE p = pHead->pNext;
	while (p != NULL)
	{
		PNODE q = p;
		p = p->pNext;
		free(q);
	}
	pHead->pNext = NULL;												//将链表置为空表，使头结点的指针域置为NULL
}

bool is_empty(PNODE pHead)
{
	if (pHead->pNext == NULL)
		return true;
	else
		return false;
}

int length_List(PNODE pHead)
{
	int length = 0;
	PNODE p = pHead->pNext;
	while (p != NULL)
	{
		length++;
		p = p->pNext;
	}

	return length;
}

bool insert_Linklist(PNODE pHead, int pos, int value)
{
	PNODE p = pHead;
	int j;
	j = 1;

	while (j < pos && p != NULL)							//找到第pos-1个结点.p!=NULL主要是为了在错误情况插入序号大于线性表长度时及时跳出
	{
		p = p->pNext;
		j++;
	}
	if (j > pos || p == NULL)								//j>pos是为了排除输入负数序号的错误情况而设立的
		return false;

	PNODE pNew = (PNODE)malloc(sizeof(NODE));
	pNew->data = value;
	pNew->pNext = p->pNext;
	p->pNext = pNew;

	return true;
}

bool delete_Linklist(PNODE pHead, int pos, int* value)
{
	PNODE p = pHead;
	int j;
	j = 1;

	while (p->pNext != NULL && j < pos)						//找到第pos-1个结点.p->pNext 主要是为了判断第pos-1个结点的下一个结点（即第pos个结点是否存在）
	{
		p = p->pNext;
		j++;
	}
	if (p->pNext == NULL || j > pos)						//当第pos个结点为空或者出现输入负数序号的情况下返回出错
		return false;

	PNODE q = p->pNext;
	*value = q->data;
	p->pNext = q->pNext;
	free(q);												//释放动态内存

	return true;
}

void sort_Linklist(PNODE pHead)								//选择排序法（升序）
{
	int top, seek;
	int length = length_List(pHead);

	PNODE q, p;
	for (top = 0, q = pHead->pNext; top < length - 1; top++, q = q->pNext)			//基本上大体的思路与顺序存储结构的选择排序法基本上相同
		for (seek = top + 1, p = q->pNext; seek < length; seek++, p = p->pNext)
			if (q->data > p->data)
			{
				int temp = q->data;
				q->data = p->data;
				p->data = temp;
			}
}

/*
什么是算法？
	狭义的算法是与数据的存储方式密切相关；
	广义的算法是与数据的存储方式无关的。

	泛型：利用某种技术达到的效果就是：不同的数据存储方式但执行的操作是相同的

	这是几个网友的见解我觉得还不错：
	1、狭义与广义的不同：两种算法在逻辑上是一样的，但是以依赖的存储方式不一样，导致了算法的实现就不同。
	2、广义上实现的算法思想上和规律上一样，狭义是算法的真正实现的步骤不一样。

	郝斌老师还提到了C++上的函数重载符就是这种思想。

	这种狭义和广义的编程正是泛型编程需要研究的。
	在宏观层面上，普通程序员在编程时拿到封装了的函数，在编程的过程中感觉到不同的编程语言之间的实现上似乎是相同的，
	但是在底层的实现细节上不同功能的编程语言函数上或者同样在操作上相似的函数实现上是不同的
	*/