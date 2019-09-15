//													重新修改的BST二叉搜索树(版本2)
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct BTnode {														//构造一个二叉树的二叉链表结点结构
	char data;
	struct BTnode* lchild;
	struct BTnode* rchild;
}BTNODE, * PBTNODE;

void Create_BST(PBTNODE* BST, const int* arr, int size);					//生成BST
bool Insert_BST(PBTNODE* BST, int key);										//插入一个数据到BST中
bool Delete_BST(PBTNODE* BST, int key);										//删除一个BST中的数据（若存在），这个函数重在查找而不是删除，删除的任务交给下一个函数
bool Delete_BST_elem(PBTNODE* BST);											//删除传递过来的结点的数据
void Destroy_BST(PBTNODE* BST);												//销毁BST的动态内存

PBTNODE BST_Search_Recursion(PBTNODE BST, int key);							//使用递归去进行查找
PBTNODE BST_Search_nonRecursion(PBTNODE BST, int key);						//使用非递归进行BST查找
PBTNODE BST_Max_Search(PBTNODE BST);										//寻找BST的最大值
PBTNODE BST_Min_Search(PBTNODE BST);										//寻找BST的最小值
void InorderTraverse_BST(PBTNODE BST);										//中序遍历
bool is_emptyBST(PBTNODE BST);												//判断BST是否为空树

int main(void)
{
	const int arr[11] = { 62,58,47,35,37,51,88,73,99,93,95 };
	PBTNODE BST = NULL;
	Create_BST(&BST,arr,11);

	printf("Before deleting:\n");
	InorderTraverse_BST(BST);
	putchar('\n');

	printf("After deleting:\n");
	Delete_BST(&BST, 37);
	Delete_BST(&BST, 99);
	InorderTraverse_BST(BST);
	putchar('\n');

	printf("The maxinum number is %d.\n", BST_Max_Search(BST)->data);
	printf("The mininum number is %d.\n", BST_Min_Search(BST)->data);
	printf("The address of the number %d is %p.\n", 51,
		BST_Search_nonRecursion(BST, 51));
	printf("The address of the number %d is %p.\n", 51,
		BST_Search_Recursion(BST, 51));

	Destroy_BST(&BST);
	if (is_emptyBST(BST))
		printf("BST is destroyed.\n");
	return 0;
}

void Create_BST(PBTNODE* BST, const int* arr, int size)
{
	int i;
	for (i = 0; i < size; i++)
	{
		Insert_BST(BST, arr[i]);
	}
}

bool Insert_BST(PBTNODE* BST, int key)						//这里使用了二级指针比直接通过返回值去修改主调中的变量简洁了很多
{
	if (!(*BST))											//当前指针所指向的结点是空的，那么新建一个结点
	{
		(*BST) = (PBTNODE)malloc(sizeof(BTNODE));
		if (!(*BST))
			exit(-1);
		(*BST)->data = key;
		(*BST)->lchild = (*BST)->rchild = NULL;
		return true;
	}
	else if (key < (*BST)->data)							//插入值小于当前结点
		return Insert_BST(&(*BST)->lchild, key);
	else if (key > (*BST)->data)							//插入值大于当前结点
		return Insert_BST(&(*BST)->rchild, key);
	else
		return false;										//BST中已经存在这个数据，就返回失败标志
}

bool Delete_BST(PBTNODE* BST, int key)
{
	if (!(*BST))											//在BST中没有找到函数参数所代表的数据，就什么也不做返回
		return false;
	else if (key < (*BST)->data)							//两个判断语句其实就是在寻找适合插入的地方，若插入值小于当前结点值，就向左寻找删除，同理享有的情况
		return Delete_BST(&(*BST)->lchild, key);
	else if (key > (*BST)->data)
		return Delete_BST(&(*BST)->rchild, key);
	else
	{
		Delete_BST_elem(BST, key);						//若找到这个值，就需要特别调用一个函数去删除结点：使用调用函数的方式既好分类又比较条理清晰
		return true;
	}
}

bool Delete_BST_elem(PBTNODE* BST)
{
	PBTNODE ptemp;										/*删除结点有四种情况：1、没有孩子；
																			  2、只有左孩子；
																			  3、只有右孩子；
																			  4、左右孩子都有。
															但值得注意的是没有孩子的情况可以通过只有左孩子的情况的代码处理，因为即使是这样最后也是附上了一个NULL				  */
	if (!(*BST)->rchild)
	{
		ptemp = *BST;
		(*BST) = (*BST)->lchild;
		free(ptemp);
	}
	else if (!(*BST)->lchild)
	{
		ptemp = *BST;
		(*BST) = (*BST)->rchild;
		free(ptemp);
	}
	else
	{													/*当删除的结点有两个孩子时，这里使用了找其左子树最大的结点去替代删除的结点的数据，然后删除该最大的孩子（或者是孙子）。
														当然也可以找右子树的最小结点。
															在查找最大的结点时既要记录该最大孩子的地址，也要记录该孩子的双亲结点的地址，毕竟该最大孩子的孩子不能丢弃，需要接到
														它的双亲结点的身上。这里有分为了两种情况：
																			1、待删除结点的左孩子就是左子树最大结点
																			2、待删除结点的左孩子有右子树，那么这个最大结点需要到左孩子的右子树身上去找*/
		PBTNODE father = *BST;
		PBTNODE s = (*BST)->lchild;
		while (s->rchild)
		{
			father = s;
			s = s->rchild;
		}
		(*BST)->data = s->data;

		if (father != (*BST))				//2、待删除结点的左孩子有右子树
			father->rchild = s->rchild;
		else
			father->lchild = s->lchild;		//1、待删除结点的左孩子就是左子树最大结点，所以记录的最大结点的父节点是待删除结点本身
		free(s);
	}
	return true;
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

void Destroy_BST(PBTNODE* BST)
{
	if (!(*BST))
		return;
	else
	{
		Destroy_BST(&(*BST)->lchild);
		Destroy_BST(&(*BST)->rchild);
		free(*BST);
		*BST = NULL;						//释放动态内存后，也同时将指针统一修改成空指针
	}
}

PBTNODE BST_Search_Recursion(PBTNODE BST, int key)
{
	if (!BST)
		return NULL;
	else if (key < BST->data)
		return BST_Search_Recursion(BST->lchild, key);		//使用尾递归查找目标结点
	else if (key > BST->data)
		return BST_Search_Recursion(BST->rchild, key);
	else
		return BST;
}

PBTNODE BST_Search_nonRecursion(PBTNODE BST, int key)
{
	while (BST)												//使用非递归方式寻找目标结点
	{
		if (key < BST->data)								//小了就向左找，大了就向右找
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
		while (BST->rchild)									//一直向右找
			BST = BST->rchild;
	return BST;
}

PBTNODE BST_Min_Search(PBTNODE BST)
{
	if (!BST)
		return NULL;
	else if (BST->lchild)
		return BST_Min_Search(BST->lchild);					//使用尾递归向左找
	return BST;
}

bool is_emptyBST(PBTNODE BST)
{
	if (!BST)
		return true;
	else
		return false;
}