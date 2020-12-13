/**
 * 左倾红黑树实现
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NODESTRLEN 64
#define RED 1
#define BLACK 0

#define MAX(l,r) ((l)>(r)?(l):(r))

struct Node {
	char str[NODESTRLEN];
	int val;
	int color;
	struct Node* left, * right;
};

struct RBT {
	struct Node* root;
};


//结点创建
struct Node* NodeCreate(const char* buf, int value) {
	struct Node* node;
	if ((node = malloc(sizeof(struct Node))) == NULL)
		return NULL;
	strncpy(node->str, buf, NODESTRLEN - 1);
	node->str[NODESTRLEN - 1] = '\0';
	node->val = value;
	node->color = RED;
	node->left = NULL;
	node->right = NULL;
	return node;
}


//红黑树初始化
void RBTInit(struct RBT* rbt) {
	rbt->root = NULL;
}


void NodeDestroy(struct Node* h) {
	if (h == NULL)return;

	if (h->left)NodeDestroy(h->left);
	if (h->right)NodeDestroy(h->right);
	free(h);
}


//红黑树销毁
void RBTDestroy(struct RBT* rbt) {
	if (rbt == NULL)return;
	NodeDestroy(rbt->root);
	rbt->root = NULL;
}


int isEmpty(const struct RBT* rbt) {
	return (rbt == NULL || rbt->root == NULL) ? 1 : 0;
}


//判断当前结点是否为红结点
int isRed(const struct Node* node) {
	return node == NULL ? 0 : node->color ? 1 : 0;
}


int NodeSize(const struct Node* h) {
	if (h == NULL)return 0;
	return NodeSize(h->left) + NodeSize(h->right) + 1;
}


//结点总数
int RBTSize(const struct RBT* rbt) {
	if (rbt == NULL)return 0;
	return NodeSize(rbt->root);
}


int height(const struct Node* node) {
	if (node == NULL)return 0;
	int hs = MAX(height(node->left), height(node->right));
	return hs + ((node->color == BLACK) ? 1 : 0);
}


//树高
int RBTHeight(const struct RBT* rbt) {
	return rbt == NULL ? 0 : height(rbt->root);
}


//颜色翻转
void flipColors(struct Node* h) {
	h->color = !h->color;
	h->left->color = !h->left->color;
	h->right->color = !h->right->color;
}


//左旋
struct Node* rotateLeft(struct Node* h) {
	struct Node* x = h->right;

	h->right = x->left;
	x->left = h;
	x->color = h->color;
	h->color = RED;
	return x;
}


//右旋
struct Node* rotateRight(struct Node* h) {
	struct Node* x = h->left;

	h->left = x->right;
	x->right = h;
	x->color = h->color;
	h->color = RED;
	return x;
}


/**
 * 从当前结点的右子树中提出个结点使左子结点变成非2-结点
 */
struct Node* removeLeft(struct Node* h) {
	flipColors(h);
	if (isRed(h->right->left)) {
		h->right = rotateRight(h->right);
		h = rotateLeft(h);
		flipColors(h);
	}
	return h;
}


/**
 * 从当前结点的左子树中提出个结点使右子结点变成非2-结点
 */
struct Node* removeRight(struct Node* h) {
	flipColors(h);
	if (isRed(h->left->left)) {
		h = rotateRight(h);
		flipColors(h);
	}
	return h;
}


struct Node* NodeMin(struct Node* node) {
	if (node == NULL)return NULL;
	return node->left ? NodeMin(node->left) : node;
}


//返回最小键
const char* RBTMin(const struct RBT* rbt) {
	return isEmpty(rbt) ? NULL : NodeMin(rbt->root)->str;
}


struct Node* NodeMax(struct Node* node) {
	if (node == NULL)return NULL;
	return node->right ? NodeMax(node->right) : node;
}


//返回最大键
const char* RBTMax(const struct RBT* rbt) {
	return isEmpty(rbt) ? NULL : NodeMax(rbt->root)->str;
}


struct Node* NodePut(struct Node* h, const char* buf, int value) {
	int cmp;

	if (h == NULL)
		return NodeCreate(buf, value);
	if ((cmp = strcmp(buf, h->str)) < 0) {
		h->left = NodePut(h->left, buf, value);
	}
	else if (cmp > 0) {
		h->right = NodePut(h->right, buf, value);
	}
	else h->val = value;

	if (!isRed(h->left) && isRed(h->right))
		h = rotateLeft(h);
	if (isRed(h->left) && isRed(h->left->left))
		h = rotateRight(h);
	if (isRed(h->left) && isRed(h->right))
		flipColors(h);
	return h;
}


//插入操作
void RBTPut(struct RBT* rbt, const char* buf, int value) {
	if (rbt == NULL) {
		fprintf(stderr, "rbt is null\n");
		return;
	}
	rbt->root = NodePut(rbt->root, buf, value);
	rbt->root->color = BLACK;
}


int get(const struct Node* h, const char* buf) {
	int cmp;

	if (h == NULL)return -1;
	if ((cmp = strcmp(buf, h->str)) < 0)
		return get(h->left, buf);
	else if (cmp > 0)
		return get(h->right, buf);
	return h->val;
}


//查找
int RBTGet(const struct RBT* rbt, const char* buf) {
	return rbt == NULL ? -1 : get(rbt->root, buf);
}


//检测是否存在该键
int contains(const struct RBT* rbt, const char* buf) {
	return RBTGet(rbt, buf) != -1;
}


//在删除结点后调用该函数来重新对结点进行调整，使其保持平衡
struct Node* balance(struct Node* h) {
	if (isRed(h->right))
		h = rotateLeft(h);
	if (isRed(h->left) && isRed(h->left->left))
		h = rotateRight(h);
	if (isRed(h->left) && isRed(h->right))
		flipColors(h);
	return h;
}


struct Node* deleteMin(struct Node* h) {
	if (h == NULL)return NULL;
	if (h->left == NULL) {
		free(h);
		return NULL;
	}
	if (!isRed(h->left) && !isRed(h->left->left))
		h = removeLeft(h);
	h->left = deleteMin(h->left);
	return balance(h);
}


//删除最小结点
void RBTDeleteMin(struct RBT* rbt) {
	if (rbt == NULL)return;
	if (!isRed(rbt->root->left) && !isRed(rbt->root->right))
		rbt->root->color = RED;
	rbt->root = deleteMin(rbt->root);
	if (!isEmpty(rbt))rbt->root->color = BLACK;
}


struct Node* deleteMax(struct Node* h) {
	if (h == NULL)return NULL;
	if (isRed(h->left))
		h = rotateRight(h);
	if (h->right == NULL) {
		free(h);
		return NULL;
	}
	if (!isRed(h->right) && !isRed(h->right->left))
		h = removeRight(h);
	h->right = deleteMax(h->right);
	return balance(h);
}


//删除最大结点
void RBTDeleteMax(struct RBT* rbt) {
	if (rbt == NULL)return;
	if (!isRed(rbt->root->left) && !isRed(rbt->root->right))
		rbt->root->color = RED;
	rbt->root = deleteMax(rbt->root);
	if (!isEmpty(rbt))rbt->root->color = BLACK;
}


struct Node* delete(struct Node* h, const char* buf) {
	if (h == NULL)return NULL;

	if (strcmp(buf, h->str) < 0) {
		if (!isRed(h->left) && !isRed(h->left->left))
			h = removeLeft(h);
		h->left = delete(h->left, buf);
	}
	else {
		if (isRed(h->left))
			h = rotateRight(h);
		if (/*strcmp(buf,h->str)==0 && */h->right == NULL) {
			free(h);
			return NULL;
		}
		if (!isRed(h->right) && !isRed(h->right->left))
			h = removeRight(h);

		if (strcmp(buf, h->str) == 0) {
			struct Node* t = NodeMin(h->right);
			strcpy(h->str, t->str);
			h->val = t->val;
			h->right = deleteMin(h->right);
		}
		else h->right = delete(h->right, buf);
	}
	return balance(h);
}


//任意删除
void RBTDelete(struct RBT* rbt, const char* buf) {
	if (isEmpty(rbt)) {//检查红黑树是否为空？
		fprintf(stderr, "rbt is null or is empty\n");
		return;
	}
	if (!contains(rbt, buf)) {//检测红黑树中是否包含该键
		fprintf(stderr, "key: %s is not contain!\n", buf);
		return;
	}

	if (!isRed(rbt->root->left) && !isRed(rbt->root->right))
		rbt->root->color = RED;
	rbt->root = delete(rbt->root, buf);
	if (!isEmpty(rbt))rbt->root->color = BLACK;
}


static void printNode(const struct Node* node) {
	if (node == NULL)return;
	if (node->left)
		printNode(node->left);
	printf("str: %s, val: %d, color: %d\n", node->str, node->val, isRed(node));
	if (node->right)
		printNode(node->right);
}


//打印
static void RBTPrint(const struct RBT* rbt) {
	if (rbt == NULL) {
		fprintf(stderr, "rbt is null\n");
		return;
	}
	printNode(rbt->root);
}


int main(void)
{
	struct RBT rbt;

	RBTInit(&rbt);
	RBTPut(&rbt, "w", 12);
	RBTPut(&rbt, "a", 32);
	RBTPut(&rbt, "c", 33);
	RBTPut(&rbt, "d", 36);
	RBTPut(&rbt, "z", 31);
	RBTPut(&rbt, "g", 37);
	RBTPut(&rbt, "m", 30);
	RBTPut(&rbt, "s", 23);
	printf("head: %s\n", rbt.root->str);
	printf("size: %d\n", RBTSize(&rbt));
	printf("height: %d\n", RBTHeight(&rbt));
	RBTPrint(&rbt);
	printf("d's value: %d\n", RBTGet(&rbt, "d"));
	printf("k's value: %d\n", RBTGet(&rbt, "k"));
	RBTDeleteMin(&rbt);
	RBTDeleteMax(&rbt);
	RBTPrint(&rbt);
	RBTDelete(&rbt, "u");
	RBTPrint(&rbt);
	printf("size: %d\n", RBTSize(&rbt));
	RBTDelete(&rbt, "g");
	putchar('\n');
	RBTPrint(&rbt);
	printf("size: %d\n", RBTSize(&rbt));
	printf("d's value: %d\n", RBTGet(&rbt, "d"));
	printf("height: %d\n", RBTHeight(&rbt));
	RBTDestroy(&rbt);

	exit(EXIT_SUCCESS);
}