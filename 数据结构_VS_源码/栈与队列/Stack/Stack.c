#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct node {
	int data;
	struct node* pNext;
}NODE, * PNODE;

typedef struct Stack {
	PNODE pTop;
	PNODE pBottom;
}STACK, * PSTACK;

void init_Stack(PSTACK pS);                     //初始化栈
void push_Stack(PSTACK pS, int value);          //压栈
bool pop_Stack(PSTACK pS, int* value);          //弹栈（出栈）
void traverse_Stack(PSTACK pS);                 //遍历
bool is_empty(PSTACK pS);                       //检验链表是否为空
void clear_Stack(PSTACK pS);                    //将链栈清空，只剩下一个头结点

int main(void)
{
	STACK S;
	int value;

	init_Stack(&S);
	push_Stack(&S, 1);
	push_Stack(&S, 2);
	push_Stack(&S, 3);
	push_Stack(&S, 4);
	push_Stack(&S, 5);
	push_Stack(&S, 6);
	traverse_Stack(&S);

	if (pop_Stack(&S, &value))
		printf("Pop success,and we pop the data %d.\n", value);
	else
		printf("Pop failed.\n");

	traverse_Stack(&S);

	clear_Stack(&S);
	free(S.pTop);                               //释放头结点

	return 0;
}

void init_Stack(PSTACK pS)
{
	pS->pTop = (PNODE)malloc(sizeof(NODE));              //创建一个头结点，将初始化的头结点的地址给栈顶指针和栈底指针
	if (pS->pTop == NULL)
	{
		fprintf(stderr, "Can't create stack.\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		pS->pBottom = pS->pTop;
		pS->pTop->pNext = NULL;                          //并设置头结点的指针域为空指针
	}
}

void push_Stack(PSTACK pS, int value)
{
	PNODE pNew = (PNODE)malloc(sizeof(NODE));
	if (pNew == NULL)
	{
		fprintf(stderr, "Can't create a new node.\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		pNew->data = value;
		pNew->pNext = pS->pTop;                          //压栈，将新建的结点的指针域指向原来的栈顶结点
		pS->pTop = pNew;                                 //使新加的结点成为新一个栈顶结点
	}
}

bool is_empty(PSTACK pS)
{
	if (pS->pTop == pS->pBottom)                         //当栈顶指针和栈底指针都指向同一个头结点时，表示是空栈
		return true;
	else
		return false;
}

bool pop_Stack(PSTACK pS, int* value)
{
	if (is_empty(pS))                                    //检错模块
		return false;
	else
	{
		PNODE q = pS->pTop;                              //将原来的栈顶结点的地址暂放给另一个指向结点的指针，然后调节栈顶指针，并释放这个原来的栈顶结点的内存
		*value = q->data;
		pS->pTop = q->pNext;
		free(q);
		return true;
	}
}

void traverse_Stack(PSTACK pS)
{
	PNODE p = pS->pTop;
	while (p != pS->pBottom)                             //注意：栈底指针指向的是头结点
	{
		printf("%d ", p->data);
		p = p->pNext;
	}
	putchar('\n');
}

void clear_Stack(PSTACK pS)
{
	PNODE p = pS->pTop;
	while (p != pS->pBottom)                             //释放除头结点以外的所有结点的动态内存
	{
		PNODE q = p;
		p = p->pNext;
		free(q);
	}
}
