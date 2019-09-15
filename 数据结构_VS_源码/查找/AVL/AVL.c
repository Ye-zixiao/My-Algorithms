/*=========================================平衡二叉树AVL=========================*/
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
/*=========定义平衡因子的情况===========*/
#define EH 0			//等高
#define RH -1			//右高
#define LH 1			//左高

typedef struct btnode {
	int data;
	int bf;					//平衡因子
	struct btnode* lchild;
	struct btnode* rchild;
}BTNODE,*PBTNODE;

void Create_AVL(PBTNODE* AVL, const int* arr, int size);					//创建AVL树
void R_Rotate(PBTNODE* pnode);										//右单旋
void L_Rotate(PBTNODE* pnode);										//左单旋
void Leftbalance(PBTNODE* pnode);									//左不平衡处理
void Rightbalance(PBTNODE* pnode);									//右不平衡处理
bool Insert_AVL(PBTNODE* AVL, int key, bool* taller);				//向AVL插入结点
bool is_emptyAVL(PBTNODE AVL);										//判断AVL是否为空树
void Inorder_Traverse(PBTNODE AVL);									//中序遍历
void Destroy_AVL(PBTNODE* AVL);										//释放AVL的动态内存
int Depth_AVL(PBTNODE AVL);											//计算AVL的高度（空树为0，不为空从1开始计）
	
int main(void)
{
	const int arr[11] = { 62,58,47,35,37,51,73,88,95,93,99 };
	PBTNODE AVL=NULL;
	Create_AVL(&AVL, arr, 11);
	printf("It is the AVL:\n");
	Inorder_Traverse(AVL);
	putchar('\n');
	printf("The depth of this AVL is %d.\n", Depth_AVL(AVL));		//计算出当前AVL的树高
	
	Destroy_AVL(&AVL);
	if (is_emptyAVL(AVL))
		printf("AVL is empty.\n");

	return 0;
}

/*右旋：把当前结点的左孩子的右子树作为当前结点的左子树，然后让结点成为其左孩子的右孩子，并重新使原来的左孩子成为根结点*/
void R_Rotate(PBTNODE* pnode)
{
	PBTNODE Left = (*pnode)->lchild;
	(*pnode)->lchild = Left->rchild;
	Left->rchild = (*pnode);
	(*pnode) = Left;
}

/*左旋：把当前结点的右孩子的左子树作为当前结点的右子树，然后让结点成为其右孩子的左孩子，并重新使原来的右孩子成为根结点*/
void L_Rotate(PBTNODE* pnode)
{
	PBTNODE Right = (*pnode)->rchild;
	(*pnode)->rchild = Right->lchild;
	Right->lchild = (*pnode);
	(*pnode) = Right;
}

/*=============注意：平衡因子BF是在做旋转的之前就进行修改============*/
void Leftbalance(PBTNODE* pnode)
{
	PBTNODE L, LR;
	L = (*pnode)->lchild;							/*将当前结点的左孩子地址赋给了L，使得L能够操作这个左孩子结点的成员（如rchild、lchild、data、和bf）甚至是L本身的值可以改变，
													 但是他终究不能改变实际上的该左孩子的双亲结点到底指向了哪一个结点！（即不能改变(*pnode)->lchild的值）因为L仅仅是左孩子地址的副本
													 所以下面的LR旋转（先左旋后右旋）中的左旋语句中的
													 L_Rotate(&(*pnode)->lchild);
													 是不能改成L_Rotate(&L);
													 因为这样做，可能改变了L这个结点的成员，但是却不能使得它的双亲结点真的指向另一个结点。
													 */
	switch (L->bf)
	{
		case LH:									//若插入点做： LL插入，就使用右单旋处理
			(*pnode)->bf = L->bf = EH;
			R_Rotate(pnode);
			break;
		case RH:									//若插入点做： LR插入，就使用先左旋后右旋处理
			LR = L->rchild;
			switch (LR->bf)
			{
				case EH:
					(*pnode)->bf = L->bf = EH;
					break;
				case LH:
					L->bf = EH;
					(*pnode)->bf = RH;
					break;
				case RH:
					L->bf = LH;
					(*pnode)->bf = EH;
					break;
			}
			LR->bf = EH;
			L_Rotate(&(*pnode)->lchild);			/*重点：为什么这句语句不能改成L_Rotate(&L);？答案见书上夹的纸条的解释。
													但总的来说还是需要对（二级）指针的深入理解和主被调函数之间在什么情况下会改变主调的变量值*/
			R_Rotate(pnode);
			break;
	}
}

void Rightbalance(PBTNODE* pnode)
{
	PBTNODE R, RL;
	R = (*pnode)->rchild;
	switch (R->bf)
	{
		case RH:									//若插入点做： RR插入，就使用左单旋处理
			(*pnode)->bf = R->bf = EH;
			L_Rotate(pnode);
			break;
		case LH:									//若插入点做： RL插入，就先做右旋再做左旋处理
			RL = R->lchild;
			switch (RL->bf)
			{
				case EH:
					(*pnode)->bf = R->bf = EH;
					break;
				case LH:
					(*pnode)->bf = EH;
					R->bf = RH;
					break;
				case RH:
					(*pnode)->bf = LH;
					R->bf = EH;
					break;
			}
			RL->bf = EH;
			R_Rotate(&(*pnode)->rchild);
			L_Rotate(pnode);
			break;
	}
}

bool Insert_AVL(PBTNODE* AVL, int key,bool *taller)
{
	if (!(*AVL))											//当前结点是空，就创建一个新的结点插入
	{
		*AVL = (PBTNODE)malloc(sizeof(BTNODE));
		if (!(*AVL))
			exit(-1);
		(*AVL)->data = key;
		(*AVL)->bf = EH;
		(*AVL)->lchild = (*AVL)->rchild = NULL;
		*taller = true;
	}
	else
	{
		if (key == (*AVL)->data)							//若当前AVL树中已经存在key这个数值，就退出
		{
			*taller = false;
			return false;
		}
		else if (key < (*AVL)->data)						
		{
			if (!Insert_AVL(&(*AVL)->lchild, key, taller))	//若key小于当前结点的数值，向左插入
				return false;
			if(*taller)
			{												/*决定某一个结点是否需要进行旋转处理1、看当前的结点的平衡因子BF；2、看它的整棵树是否长高了。
																单单看插入了子树上插入了结点就认为需要进行旋转处理和更改平衡因子BF是不科学的。
																所以在这个判断语句中不能写else，而应该写 if(*taller)即长高了就进入判断块中   同样的下面的在右边插入时的程序也是一样的*/

				switch ((*AVL)->bf)							//插入完毕后，需要对它的祖先结点的BF和树是否长高进行判断，并作出相应的修改
				{
					case EH:
						(*AVL)->bf = LH;
						*taller = true;
						break;
					case LH:
						Leftbalance(AVL);
						*taller = false;
						break;
					case RH:
						(*AVL)->bf = EH;
						*taller = false;
						break;
				}
			}
		}
		else
		{
			if (!Insert_AVL(&(*AVL)->rchild, key, taller))	//若key大于当前结点的数值，向右插入
				return false;
			if(*taller)
			{
				switch ((*AVL)->bf)							//插入完毕后，需要对它的祖先结点的BF和树是否长高进行判断，并作出相应的修改
				{
					case EH:
						(*AVL)->bf = RH;
						*taller = true;
						break;
					case LH:
						(*AVL)->bf = EH;
						*taller = false;
						break;
					case RH:
						Rightbalance(AVL);
						*taller = false;
						break;
				}
			}
		}
	}

	return true;
}

bool is_emptyAVL(PBTNODE AVL)
{
	if (!AVL)
		return true;
	else
		return false;
}

void Create_AVL(PBTNODE* AVL, const int* arr, int size)
{
	int i;
	bool taller=false;
	for (i = 0; i < size; i++)
		Insert_AVL(AVL, arr[i], &taller);
}

void Inorder_Traverse(PBTNODE AVL)
{
	if (!AVL)
		return;
	else
	{
		Inorder_Traverse(AVL->lchild);
		printf("%d ", AVL->data);
		Inorder_Traverse(AVL->rchild);
	}
}

void Destroy_AVL(PBTNODE* AVL)
{
	if(!(*AVL))
		return;
	else
	{
		Destroy_AVL(&(*AVL)->lchild);
		Destroy_AVL(&(*AVL)->rchild);
		free(*AVL);
		*AVL = NULL;
	}
}

int Depth_AVL(PBTNODE AVL)
{
	if (!AVL)
		return 0;
	else
	{
		int h1 = Depth_AVL(AVL->lchild);
		int h2 = Depth_AVL(AVL->rchild);
		return (h1 > h2 ? h1 : h2) + 1;
	}
}