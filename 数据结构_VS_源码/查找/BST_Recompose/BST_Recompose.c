//													重新修改的BST二叉搜索树
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct BTnode {														//构造一个二叉树的二叉链表结点结构
	char data;
	struct BTnode* lchild;
	struct BTnode* rchild;
}BTNODE, * PBTNODE;

/*==========================以下部分函数需要对BST进行改动,建议下次使用二级指针解决===================*/
PBTNODE Create_BST(PBTNODE BST, int* arr, int size);						//得到一个指向BST的空指针，然后创建一个二叉搜索树，并重新返回这个BST的根结点地址给BST指针。 使用返回体系去修改一级指针BST
PBTNODE Insert_BST(PBTNODE BST, int key);									//使用了返回体系对BST进行插入
bool Delete_BST(PBTNODE* BST, int key);										//使用二级指针体系对BST进行查找删除（重在查找，删除的事通过调用函数来解决）
bool Delete_BST_Element(PBTNODE* BST);										//删除具体的结点
void destroy_BST(PBTNODE* BST);												//销毁BST中的所有结点

/*=========================以下部分函数不需要对BST进行修改=================================*/
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
	BST = Create_BST(BST, arr, 11);
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

	destroy_BST(&BST);
	if (is_emptyBST(BST))
		printf("empty.\n");
	return 0;
}

PBTNODE Insert_BST(PBTNODE BST, int key)
{
	if (!BST)												//若当前结点是空的，且新加的数据确实插入到这里，那么就需要创建一个新的叶结点
	{
		BST = (PBTNODE)malloc(sizeof(BTNODE));
		if (!BST)
			exit(-1);
		BST->data = key;
		BST->lchild = BST->rchild = NULL;
	}
	else if (key < BST->data)
		BST->lchild = Insert_BST(BST->lchild, key);			//若插入值小于当前的结点数据，就向左寻找插入
	else if (key > BST->data)
		BST->rchild = Insert_BST(BST->rchild, key);
	
	return BST;												//注意：因为这个函数是通过返回值的方式去修改主调函数的指针变量和数据，所以必须return
}

PBTNODE Create_BST(PBTNODE BST, int* arr, int size)						/*这里是故意使用return来返回二叉搜索树的根结点，目的是为了让自己能够区分使用二级指针改变主调函数的指针变量和
																		使用返回值来修改主调函数中的指针变量两种情况和改变主调函数的变量的方法。
																			在实际中，如果不采用返回值的方式去修改主调函数中的BST指针，那么即使在Create_BST（）这个函数中修改了BST，但
																		事实上却并没有改变主调中的BST（主调中BST仍然是NULL），因为Create_BST（）函数中的BST只不过是主调函数BST的副本。
																			或者更方便的是就是使用二级指针作为Create_BST函数的参数，让主调函数向被调函数传递BST的地址，让被调函数去直接
																		修改主调函数的BST指针。这样就不用return了。
																			同样的在下面的删除结点函数Delete_BST（）也同样会出现这种情况，普通函数在递归他自己的时候在进入递归后修改一个
																		传递过来的BST一级指针后返回到原来的函数后BST也没有发生变化，因为他只不过是改变了BST的副本而已。这是为了既能使用bool
																		类型，也为了能够改变调用前的指针变量，就最好使用二级指针来做参数：即
																				函数传递一个二级指针就能修改二级指针变量自己的值，但是可以修改它所指针的一级指针！
																		*/
{															//但千万也不要写成Create_BST(BTNODE** BST, int* arr, int size),一个最不要做的事就是以（直接）二级指针作为形参，这个和PBTNODE* BST还是有不同的
	int i;													//这个可以去想想为什么二维数组的数组名不能直接赋给二级指针，用它来访问二维数组
	for (i = 0; i < size; i++)
		BST=Insert_BST(BST, arr[i]);
	return BST;
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
		Delete_BST_Element(BST, key);						//若找到这个值，就需要特别调用一个函数去删除结点：使用调用函数的方式既好分类又比较条理清晰
		return true;
	}
}

bool Delete_BST_Element(PBTNODE* BST)
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

void destroy_BST(PBTNODE *BST)
{
	if (!(*BST))
		return;
	else
	{
		destroy_BST(&(*BST)->lchild);
		destroy_BST(&(*BST)->rchild);
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