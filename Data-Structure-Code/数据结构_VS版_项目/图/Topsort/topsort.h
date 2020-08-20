#ifndef TOPSORT_H_
#define TOPSORT_H_
#define MAXVER 20

/*----------链表结点结构-------*/
typedef struct node {
	int data;
	struct node* pNext;
}NODE, * PNODE;

/*----------堆栈结构-----------*/
typedef struct Stack {
	PNODE pTop;
	PNODE pBottom;
}STACK, * PSTACK;

/*----------队列结构-----------*/
typedef struct Linkqueue {									//链式队列
	PNODE front, rear;
}L_QUEUE, * P_QUEUE;

typedef struct edgenode {									//边表结点结构
	int adjvertex;											//携带邻接点在数组当中的下标
	int weight;												//边的权重
	struct edgenode* pNext;
}EdgeNode, * PEdgeNode;

typedef struct vertexnode {									//顶点数组结构
	int indegree;
	char data;
	PEdgeNode firstedge;									//指向头一个临界点的下标
}VerNode[MAXVER];

typedef struct lgragh {										//图的结构
	VerNode adjlist;										//创建一个顶点带头指针的数组
	int num_ver;											//顶点数量
	int num_edge;											//边的数量
}LGragh, * PLgragh;

void init_Stack(PSTACK pS);									//初始化栈
void push_Stack(PSTACK pS, int value);						//压栈
bool pop_Stack(PSTACK pS, int* value);						//弹栈（出栈）
bool is_emptystack(PSTACK pS);									//检验链表是否为空
void destroy_Stack(PSTACK pS);								//将链栈清空，只剩下一个头结点

void create_AdjListGragh(PLgragh LG);						//创建创建一个邻接表
void clear_input(void);										//清除输入缓冲区中的数据
void destroy_LGragh(PLgragh LG);							//释放邻接表中的邻接链表中的结点的动态内存

void init_LinkQueue(P_QUEUE pP);							//初始化队列
void en_queue(P_QUEUE pP, int value);						//入队
bool de_queue(P_QUEUE pP, int* pvalue);						//出队
bool is_emptyqueue(P_QUEUE pP);								//检查队列是否为空
void destroy_queue(P_QUEUE pP);								//释放队列的所有动态内存

#endif TOPSORT_H_