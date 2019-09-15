#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
int i = 1;

typedef struct btnode {									//定义树结点的结构
	char data;
	struct btnode* lchild;
	struct btnode* rchild;
}BTNODE ,*PBTNODE;

typedef struct node {									//定义链表队列结点的结构
	PBTNODE pbtnode;
	struct node* pNext;
}NODE,*PNODE;

typedef struct LinkedQueue {							//定义链对的队头指针和队尾指针
	PNODE front;
	PNODE rear;
}LINKEDQUEUE,*PLINKEDQUEUE;

void init_LinkedQueue(PLINKEDQUEUE pLQ);				//初始化链对
void enqueue(PLINKEDQUEUE pLQ, PBTNODE pT);				//入队
PBTNODE dequeue(PLINKEDQUEUE pLQ);						//出队
bool is_emptyqueue(PLINKEDQUEUE pLQ);					//判断链对是否为空
void destroy_queue(PLINKEDQUEUE pLQ);					//销毁链对

PBTNODE Create_BinaryTree(void);						//以先序遍历的方式创建二叉树
void LevelorderTraverse_BTree(PBTNODE pT);				//层序遍历
void Destroy_BinaryTree(PBTNODE pT);					//销毁二叉树

int main(void)
{
	PBTNODE pT = Create_BinaryTree();
	LevelorderTraverse_BTree(pT);
	Destroy_BinaryTree(pT);

	return 0;
}

void init_LinkedQueue(PLINKEDQUEUE pLQ)
{
	pLQ->front = (PNODE)malloc(sizeof(NODE));
	if (!pLQ->front)
		exit(-1);
	else
	{
		pLQ->rear = pLQ->front;
		pLQ->front->pNext = NULL;
	}
}

void enqueue(PLINKEDQUEUE pLQ, PBTNODE pT)
{
	PNODE p = (PNODE)malloc(sizeof(NODE));
	if (!p)
		exit(-1);
	else
	{
		p->pbtnode = pT;								//放入二叉树结点的地址
		p->pNext = pLQ->rear->pNext;
		pLQ->rear->pNext = p;							//在原来的队尾指针域加上新生成结点的地址
		pLQ->rear = p;									//改变队尾指针
	}
}

bool is_emptyqueue(PLINKEDQUEUE pLQ)
{
	if (pLQ->front == pLQ->rear)
		return true;
	else
		return false;
}

PBTNODE dequeue(PLINKEDQUEUE pLQ)
{
	if (is_emptyqueue(pLQ))
		return NULL;
	else
	{
		PNODE qtemp = pLQ->front->pNext;
		PBTNODE q = qtemp->pbtnode;
		pLQ->front->pNext = qtemp->pNext;

		if (pLQ->rear == qtemp)							//出队时，不仅要将队头指针指向下下个结点，而且还要检查这个要出队的结点是不是队尾，
			pLQ->rear = pLQ->front;						//如果是，为了避免释放内存后尾指针不知道指向了什么地方，所以要特别处理下
		free(qtemp);
		return q;
	}
}

void destroy_queue(PLINKEDQUEUE pLQ)
{
	PNODE p = pLQ->front->pNext;
	while (p != NULL)
	{
		PNODE q = p;
		p = p->pNext;
		free(q);
	}
}

PBTNODE Create_BinaryTree(void)										//扩展二叉树的方式先序建立二叉链表
{
	char data;
	PBTNODE NewNode = NULL;
	printf("Enter character %d: ", i++);
	data = getchar();
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

void LevelorderTraverse_BTree(PBTNODE pT)
{
	/*层序遍历的算法详解：
		先将根结点的地址入队，然后只要链对不为空（链对为空说明已经遍历完成），就循环
			1、从队列中取出一个元素（指向链表结点的指针）；
			2、访问该元素所指的结点（打印）；
			3、若该元素所指的结点的左右孩子非空，则将其左右孩子的指针顺序入队。
	*/
	if (!pT)
		return;
	LINKEDQUEUE LQ;
	init_LinkedQueue(&LQ);
	enqueue(&LQ, pT);
	while (!is_emptyqueue(&LQ))
	{
		PBTNODE p = dequeue(&LQ);
		printf("%c ", p->data);
		if (p->lchild)
			enqueue(&LQ, p->lchild);
		if (p->rchild)
			enqueue(&LQ, p->rchild);
	}
	putchar('\n');
	destroy_queue(&LQ);
}