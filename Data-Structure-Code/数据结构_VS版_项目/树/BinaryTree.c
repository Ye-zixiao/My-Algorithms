//													二叉树的建立、遍历释放、深度和结点数
#include<stdio.h>
#include<stdlib.h>
int i = 0;

typedef struct BTnode {											//构造一个二叉树的二叉链表结点结构
	char data;
	struct BTnode* lchild;
	struct BTnode* rchild;
}BTNODE,*PBTNODE;

PBTNODE Create_BinaryTree(void);								//以扩展二叉树前序遍历序列的形式构建二叉树
void PreorderTraverse_BTree(PBTNODE pT);						//前序遍历
void InorderTraverse_BTree(PBTNODE pT);							//中序遍历
void PostorderTraverse_BTree(PBTNODE pT);						//后序遍历
void PreorderTraverse_Leaves(PBTNODE pT);						//以前序遍历的方式访问叶结点
void Destroy_BinaryTree(PBTNODE pT);							//删除二叉链表。释放所有内存
int Depth_BinaryTree(PBTNODE pT);
int Node_count(PBTNODE pT);

int main(void)
{
	printf("Enter the characters in the order of pretraverse:\n");
	PBTNODE BTree = Create_BinaryTree();

	PreorderTraverse_BTree(BTree);
	putchar('\n');
	InorderTraverse_BTree(BTree);
	putchar('\n');
	PostorderTraverse_BTree(BTree);
	putchar('\n');

	printf("The depth of Binary Tree is %d.\n", Depth_BinaryTree(BTree));
	printf("The count of Binary Tree is %d.\n", Node_count(BTree));

	Destroy_BinaryTree(BTree);
	return 0;
}

PBTNODE Create_BinaryTree(void)										//扩展二叉树的方式先序建立二叉链表
{
	char data;
	PBTNODE NewNode=NULL;
	printf("Enter character %d: ", i++);
	scanf("%c", &data);
	while (getchar() != '\n')										//清空输入缓存区回车符前面的字符
		continue;

	if (data == '#')												//一个节点上输入井号返回空指针
		return NULL;
	else
	{
		NewNode= (PBTNODE)malloc(sizeof(BTNODE));					//分配新结点的动态内存
		if (NULL == NewNode)
		{
			fprintf(stderr, "Can't create a new tree node.\n");
			exit(EXIT_FAILURE);
		}
		NewNode->data = data;
		NewNode->lchild = Create_BinaryTree();						//左孩子递归创建
		NewNode->rchild = Create_BinaryTree();						//右孩子递归创建

		return NewNode;												//返回新（有效）结点的地址
	}
}

void PreorderTraverse_BTree(PBTNODE pT)								
{
	/*前序遍历的伪算法：
		1、访问根结点
		2、先序遍历左子树
		3、先序遍历右子树
	*/
	if (pT == NULL)													//当遇到空指针的时候就直接返回上一级递归的函数
		return;
	else
	{
		printf("%c ", pT->data);
		if (pT->lchild != NULL)										//用if做判断是为了防止左右孩子指针域是空指针时仍递归，
			PreorderTraverse_BTree(pT->lchild);						//这样不仅防止了递归造成的时间和空间上的浪费
		if (pT->rchild != NULL)
			PreorderTraverse_BTree(pT->rchild);
	}
}

void InorderTraverse_BTree(PBTNODE pT)
{
	/*中序遍历的伪算法：
		1、中序遍历左子树
		2、访问根结点
		3、中序遍历右子树
	*/
	if (pT == NULL)
		return;
	else
	{
		if (pT->lchild != NULL)
			InorderTraverse_BTree(pT->lchild);
		printf("%c ", pT->data);
		if (pT->rchild != NULL)
			InorderTraverse_BTree(pT->rchild);
	}
}

void PostorderTraverse_BTree(PBTNODE pT)
{
	/*后序遍历的伪算法：
		1、后序遍历左子树
		2、后序遍历右子树
		3、访问根结点
	*/
	if (pT == NULL)
		return;
	else
	{
		if (pT->lchild != NULL)
			PostorderTraverse_BTree(pT->lchild);
		if (pT->rchild != NULL)
			PostorderTraverse_BTree(pT->rchild);
		printf("%c ", pT->data);
	}
}

void Destroy_BinaryTree(PBTNODE pT)
{
	//PBTNODE p = pT;
	if (pT == NULL)
		return;
	else
	{
		Destroy_BinaryTree(pT->lchild);
		Destroy_BinaryTree(pT->rchild);
		free(pT);								//先左右递归（删除函数），然后释放本结点的动态内存。
	}											//为的是保证当前结点的左右孩子和子孙的内存都在之前被释放了
}

int Depth_BinaryTree(PBTNODE pT)
{
	
	if (pT != NULL)											//改造后序遍历的算法
	{
		int hl = Depth_BinaryTree(pT->lchild);
		int hr = Depth_BinaryTree(pT->rchild);
		return 1 + (hl > hr ? hl : hr);						//借用遍历的思想将回返的左右子树的深度进行比较+1（当前结点）
	}
	else
		return 0;											//否则对于空指针的话就返回0
}

int Node_count(PBTNODE pT)
{
	if (pT == NULL)
		return 0;
	else
	{
		int ct1 = Node_count(pT->lchild);
		int ct2 = Node_count(pT->rchild);
		return ct1 + ct2 + 1;								//这个和上面的计算深度的方法基本上一样，
	}														//先把左右子树的结点数计算出再加上当前结点的这个1
}

void PreorderTraverse_Leaves(PBTNODE pT)
{
	if (pT == NULL)													//当遇到空指针的时候就直接返回上一级递归的函数
		return;
	else
	{
		if(!pT->lchild&&!pT->rchild)
			printf("%c ", pT->data);
		if (pT->lchild != NULL)										//用if做判断是为了防止左右孩子指针域是空指针时仍递归，
			PreorderTraverse_BTree(pT->lchild);						//这样不仅防止了递归造成的时间和空间上的浪费
		if (pT->rchild != NULL)
			PreorderTraverse_BTree(pT->rchild);
	}
}