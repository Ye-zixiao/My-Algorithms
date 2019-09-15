//											使用非递归形式中序遍历二叉树
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
int i = 1;

typedef struct btnode {											//二叉树结点结构定义
	char data;
	struct btnode* lchild;
	struct btnode* rchild;
}BTNODE ,*PBTNODE;

typedef struct stacknode {										//栈结点结构定义
	PBTNODE temp;												//每一个栈结点数据域只要存放一个树结点的地址就可以了
	struct stacknode* pNext;
}STACKNODE,*PSTACKNODE;

typedef struct stack {											//定义栈底指针和栈顶指针结构
	PSTACKNODE ptop;
	PSTACKNODE pbottom;
}STACK,*PSTACK;

void init_stack(PSTACK pS);										//初始化堆栈
void push(PSTACK pS, PBTNODE pT);								//压栈
PBTNODE pop(PSTACK pS);											//出栈
bool is_emptystack(PSTACK pS);									//检测栈是否为空
void destroy_stack(PSTACK pS);									//销毁栈

PBTNODE Create_BinaryTree(void);								//创建二叉树
void inorder_tree(PBTNODE pT);									//以非递归算法中序遍历二叉树
void destroy_tree(PBTNODE pT);									//销毁二叉树

int main(void)
{
	PBTNODE pT = Create_BinaryTree();
	printf("Inorder traverse binary tree: \n");
	inorder_tree(pT);
	destroy_tree(pT);

	return 0;
}

void init_stack(PSTACK pS)
{
	pS->pbottom = (PSTACKNODE)malloc(sizeof(STACKNODE));
	if (!pS->pbottom)
		exit(-1);
	else
	{
		pS->ptop = pS->pbottom;
		pS->pbottom->pNext = NULL;
	}
}

void push(PSTACK pS, PBTNODE pT)
{
	PSTACKNODE p = (PSTACKNODE)malloc(sizeof(STACKNODE));
	if (!p)
		exit(-1);
	else
	{
		p->temp = pT;
		p->pNext = pS->ptop;							//记住链栈的栈顶从上到下指向栈底
		pS->ptop = p;
	}
}

bool is_emptystack(PSTACK pS)
{
	if (pS->pbottom == pS->ptop)
		return true;
	else
		return false;
}

PBTNODE pop(PSTACK pS)
{
	if (is_emptystack(pS))
		return NULL;
	else
	{
		PBTNODE q = pS->ptop->temp;
		PSTACKNODE qtemp = pS->ptop;
		pS->ptop = qtemp->pNext;
		free(qtemp);
		return q;
	}
}

void destroy_stack(PSTACK pS)
{
	PSTACKNODE p = pS->ptop;
	while (p != NULL)
	{
		PSTACKNODE q = p;
		p = p->pNext;
		free(q);
	}
}

PBTNODE Create_BinaryTree(void)										//扩展二叉树的方式先序建立二叉链表
{
	char data;
	PBTNODE NewNode = NULL;
	printf("Enter character %d: ", i++);
	scanf("%c", &data);
	while (getchar() != '\n')										//清空输入缓存区回车符前面的字符
		continue;

	if (data == '#')												//一个节点上输入井号返回空指针
		return NULL;
	else
	{
		NewNode = (PBTNODE)malloc(sizeof(BTNODE));					//分配新结点的动态内存
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

void inorder_tree(PBTNODE pT)
{
	PBTNODE p = pT;
	STACK S;										//创建一个堆栈区（链栈形式）
	init_stack(&S);
	while (p || !is_emptystack(&S))					//只有当堆栈为空且所指向的树结点为空时才结束遍历
	{
		while (p)									//一直向左并将沿途结点压入堆栈：									
													//当树结点不为空就将当前树结点的指针压栈
		{											//并将指针指向当前结点的左孩子，直到没有左孩子为止
			push(&S, p);
			p = p->lchild;
		}
		if (!is_emptystack(&S))						//当堆栈中还有数据且左孩子没有时，弹栈出上一个树结点的地址
		{
			p = pop(&S);
			printf("%c ", p->data);					//输出树结点的数据，然后将指针指向右孩子
			p = p->rchild;							//转向右子树
		}
	}
	destroy_stack(&S);								//最后销毁堆栈
}

void destroy_tree(PBTNODE pT)
{
	if (pT == NULL)
		return;
	else
	{
		destroy_tree(pT->lchild);
		destroy_tree(pT->rchild);
		free(pT);
	}
}

void preorder_tree(PBTNODE pT)
{
	PBTNODE p = pT;
	STACK S;										//创建一个堆栈区（链栈形式）
	init_stack(&S);
	while (p || !is_emptystack(&S))					//只有当堆栈为空且所指向的树结点为空时才结束遍历
	{
		while (p)									//一直向左并将沿途结点压入堆栈：									
													//当树结点不为空就将当前树结点的指针压栈
		{											//并将指针指向当前结点的左孩子，直到没有左孩子为止
			push(&S, p);
			printf("%c ", p->data);//先序遍历时第一次碰到就将其打印出
			p = p->lchild;
		}
		if (!is_emptystack(&S))						//当堆栈中还有数据且左孩子没有时，弹栈出上一个树结点的地址
		{
			p = pop(&S);
			//printf("%c ", p->data);					//输出树结点的数据，然后将指针指向右孩子
			p = p->rchild;							//转向右子树
		}
	}
	destroy_stack(&S);								//最后销毁堆栈
}