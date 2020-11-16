#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINE 64
#undef min
#undef max

struct Node {
	char str[MAXLINE];
	int val;
	struct Node* left, * right;
};

struct BST {
	struct Node* root;
};


struct Node* CreateNode(const char* buf, int value) {
	struct Node* node;

	if ((node = malloc(sizeof(struct Node))) == NULL)
		return NULL;
	strcpy(node->str, buf);
	node->val = value;
	node->left = NULL;
	node->right = NULL;
	return node;
}


void InitBST(struct BST*bst) {
	bst->root = NULL;
}


void destroy(struct Node* h) {
	if (h == NULL)return;

	if (h->left)  destroy(h->left);
	if (h->right) destroy(h->right);
	free(h);
}


void BSTDestroy(struct BST* bst) {
	if (bst == NULL)return;
	destroy(bst->root);
	bst->root = NULL;
}


//插入操作
struct Node*insert(struct Node*h,const char*buf,int value){
	if (h == NULL)
		return CreateNode(buf, value);
	
	int cmp = strcmp(buf, h->str);
	if (cmp < 0)
		h->left = insert(h->left, buf, value);
	else if (cmp > 0)
		h->right = insert(h->right, buf, value);
	else
		h->val = value;
	return h;
}


void BSTInsert(struct BST* bst, const char* buf, int value) {
	bst->root = insert(bst->root, buf, value);
}


//查找操作
int get(const struct Node* h,const char*buf) {
	int cmp;

	if (h == NULL)return -1;
	if ((cmp = strcmp(buf, h->str)) < 0)
		return get(h->left, buf);
	else if (cmp > 0)
		return get(h->right, buf);
	else return h->val;
}


int BSTGet(const struct BST* bst, const char* buf) {
	if (bst == NULL)return -1;
	return get(bst->root, buf);
}


//最小值
struct Node* min(struct Node* h) {
	if (h == NULL)return NULL;
	if (h->left != NULL)
		return min(h->left);
	else return h;
}


const char* BSTMin(const struct BST* bst) {
	if (bst == NULL)return NULL;
	return min(bst->root)->str;
}


//最大值
struct Node* max(struct Node* h) {
	if (h == NULL)return NULL;
	if (h->right != NULL)
		return max(h->right);
	else return h;
}


const char* BSTMax(const struct BST* bst) {
	if (bst == NULL) return NULL;
	return max(bst->root)->str;
}


//删除最小值
struct Node* deleteMin(struct Node* h) {
	struct Node* t;

	if (h == NULL)return NULL;
	if (h->left != NULL) {
		h->left = deleteMin(h->left);
		return h;
	}
	else {
		t = h->right;
		free(h);
		return t;
	}
}


void BSTDeleteMin(struct BST* bst) {
	if (bst == NULL)return;
	bst->root = deleteMin(bst->root);
}


//删除最大值
struct Node* deleteMax(struct Node* h) {
	struct Node* t;

	if (h == NULL)return NULL;
	if (h->right != NULL) {
		h->right = deleteMax(h->right);
		return h;
	}
	else {
		t = h->left;
		free(h);
		return t;
	}
}


void BSTDeleteMax(struct BST* bst) {
	if (bst == NULL)return;
	bst->root = deleteMax(bst->root);
}


//从当前结点的右子树中挑一个最小结点（并从该树中移除，但不是free），
//其中过程需要调整移除后的右子树
struct Node* RemoveRightMin(struct Node* h, struct Node** r) {
	if (h == NULL) { *r = NULL; return NULL; }

	if (h->left != NULL) {
		h->left = RemoveRightMin(h->left, r);
		return h;
	}
	else {
		*r = h;
		return h->right;
	}
}


//任意删除
struct Node* delete(struct Node* h, const char* buf) {
	//t表示替代删除结点的结点指针,right用来表示右子树的根节点（可能跟原来不一样）
	struct Node* t/*, * right*/;
	int cmp;

	if (h == NULL)return NULL;
	if ((cmp = strcmp(buf, h->str)) < 0) {
		h->left = delete(h->left, buf);
		return h;
	}
	else if (cmp > 0) {
		h->left = delete(h->right, buf);
		return h;
	}
	else {
        if(h->right==NULL){
            t=h->left;
            free(h);
            return t;
        }
        else {
            strcpy(h->str,min(h->right)->str);
            h->val=min(h->right)->val;
            h->right=deleteMin(h->right);
            return h;
        }

		// right = RemoveRightMin(h->right, &t);
		// if(t==NULL){//右边根本就没有
		// 	t = h->left;
		// 	free(h);
		// 	return t;
		// }
		// else {
		// 	t->left = h->left;
		// 	t->right = right;
		// 	free(h);
		// 	return t;
		// }
	}
}


void BSTDelete(struct BST* bst, const char* buf) {
	if (bst == NULL)return;
	bst->root = delete(bst->root, buf);
}


//打印操作（中序）
void print(const struct Node* h) {
	if (h == NULL)return;

	if (h->left != NULL)
		print(h->left);
	printf("str: %s, value: %d\n", h->str, h->val);
	if (h->right != NULL)
		print(h->right);
}


void BSTPrint(const struct BST* bst) {
	print(bst->root);
	putchar('\n');
}


int main(void)
{
	struct BST bst;

	InitBST(&bst);
	BSTInsert(&bst, "s", 32);
	BSTInsert(&bst, "m", 12);
	BSTInsert(&bst, "a", 13);
	BSTInsert(&bst, "c", 75);
	BSTInsert(&bst, "f", 31);
	BSTInsert(&bst, "z", 45);
	BSTInsert(&bst, "w", 42);
	BSTPrint(&bst);

	BSTDeleteMax(&bst);

	putchar('\n');
	BSTPrint(&bst);

	putchar('\n');
	BSTDeleteMin(&bst);

	BSTPrint(&bst);
	putchar('\n');

	BSTDelete(&bst, "m");
	BSTPrint(&bst);

	printf("m's value: %d\n", BSTGet(&bst, "m"));
	printf("d's value: %d\n", BSTGet(&bst, "d"));
	printf("k's value: %d\n", BSTGet(&bst, "k"));
	printf("min string: %s, and it's value: %d\n",
		BSTMin(&bst), BSTGet(&bst, BSTMin(&bst)));
	printf("max string: %s, and it's value: %d\n",
		BSTMax(&bst), BSTGet(&bst, BSTMax(&bst)));

	BSTDestroy(&bst);
	return 0;
}