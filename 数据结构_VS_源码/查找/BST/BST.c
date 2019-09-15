#include<stdio.h>															//这个程序就是一个被调函数不能改变主调函数中的指针变量的错误示范！
#include<stdlib.h>															//解决方法就是要不就是使用二级指针作为函数参数，或者就是使用返回值的体系去修改主调函数的指针变量
#include<stdbool.h>

typedef struct BTnode {
	int data;
	struct BTnode* lchild;
	struct BTnode* rchild;
}BTNODE, * PBTNODE;

PBTNODE Create_BST(PBTNODE BST,int *arr,int size);
PBTNODE BST_Search_Recursion(PBTNODE BST, int key);
PBTNODE BST_Search_nonRecursion(PBTNODE BST, int key);
PBTNODE BST_Max_Search(PBTNODE BST);
PBTNODE BST_Min_Search(PBTNODE BST);
PBTNODE Insert_BST(PBTNODE BST, int key);
bool Delete_BST(PBTNODE BST, int key);
PBTNODE Delete_BST_Element(PBTNODE del);
void destroy_BST(PBTNODE BST);
void InorderTraverse_BST(PBTNODE BST);

int main(void)
{
	const int arr[11] = { 62,58,47,35,37,51,88,73,99,93,95 };
	PBTNODE BST = NULL;
	BST=Create_BST(BST, arr, 11);
	printf("Before deleting:\n");
	InorderTraverse_BST(BST);
	putchar('\n');

	printf("After deleting:\n");
	Delete_BST(BST, 37);
	//Delete_BST(BST, 99);
	InorderTraverse_BST(BST);
	putchar('\n');

	destroy_BST(BST);

	return 0;
}

PBTNODE BST_Search_Recursion(PBTNODE BST, int key)
{
	if (!BST)
		return NULL;
	else if(key < BST->data)
		return BST_Search_Recursion(BST->lchild, key);
	else if(key > BST->data)
		return BST_Search_Recursion(BST->rchild, key);
	else
		return BST;
}

PBTNODE BST_Search_nonRecursion(PBTNODE BST, int key)
{
	while (BST)
	{
		if (key < BST->data)
			BST = BST->lchild;
		else if (key > BST->data)
			BST = BST->rchild;
		else
			break;
	}

	return BST;
}

PBTNODE BST_Max_Search(PBTNODE BST)
{
	//PBTNODE temp;
	//while (BST)
	//{
	//	temp = BST;
	//	BST = BST->rchild;
	//}
	//return temp;
	if (BST)
		while (BST->rchild)
			BST = BST->rchild;
	return BST;
}

PBTNODE BST_Min_Search(PBTNODE BST)
{
	if (!BST)
		return NULL;
	else if (BST->lchild)
		return BST_Min_Search(BST->lchild);
	return BST;
}

PBTNODE Insert_BST(PBTNODE BST, int key)
{
	if (!BST)
	{
		BST = (PBTNODE)malloc(sizeof(BTNODE));
		if (!BST)
			exit(-1);
		BST->data = key;
		BST->lchild = BST->rchild = NULL;
	}
	else if (key < BST->data)
		BST->lchild = Insert_BST(BST->lchild, key);
	else if (key > BST->data)
		BST->rchild = Insert_BST(BST->rchild, key);

	return BST;
}

bool Delete_BST(PBTNODE BST, int key)
{
	if (!BST)
		return false;
	else if (key < BST->data)
		return Delete_BST(BST->lchild, key);
	else if (key > BST->data)
		return Delete_BST(BST->rchild, key);
	else
	{
		BST=Delete_BST_Element(BST);
		return true;
	}
}

PBTNODE Delete_BST_Element(PBTNODE del)
{
	PBTNODE ptemp;
	if (!del->rchild)
	{
		ptemp = del;
		del = del->lchild;
		free(ptemp);
	}
	else if (!del->lchild)
	{
		ptemp = del;
		del = del->rchild;
		free(ptemp);
	}
	else
	{
		PBTNODE father = del;
		PBTNODE s = del->lchild;
		while (s->rchild)
		{
			father = s;
			s = s->rchild;
		}
		del->data = s->data;
		if (father != del)
			father->rchild = s->lchild;
		else
			father->lchild = s->lchild;
		free(s);
	}

	return del;
}

PBTNODE Create_BST(PBTNODE BST, int* arr, int size)
{
	int i;
	for (i = 0; i < size; i++)
	{
		BST=Insert_BST(BST, arr[i]);
	}
	return BST;
}

void InorderTraverse_BST(PBTNODE BST)
{
	if (!BST)
		return;
	else
	{
		InorderTraverse_BST(BST->lchild);
		printf("%d ", BST->data);
		InorderTraverse_BST(BST->rchild);
	}
}

void destroy_BST(PBTNODE BST)
{
	if (!BST)
		return;
	else
	{
		destroy_BST(BST->lchild);
		destroy_BST(BST->rchild);
		free(BST);
	}
}