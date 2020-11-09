#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KEYSTRMAX 256

struct Node{
    char key[KEYSTRMAX];
    int val;
    int n;
    struct Node*left,*right;
};

struct BST{
    struct Node*root;  
};

void debug(void){
    static int d=0;
    fprintf(stderr,"get here(%d)\n",d++);
}


static struct Node* Node_Create(const char*str,int value){
    struct Node*node=NULL;

    if((node=malloc(sizeof(struct Node)))==NULL)
        return NULL;
    strcpy(node->key,str);
    node->val=value;
    node->n=1;
    node->left=node->right=NULL;
    return node;
}

struct BST*BST_Create(void){
    struct BST*bst;

    if((bst=malloc(sizeof(struct BST)))==NULL)
        return NULL;
    bst->root=NULL;
    return bst;
}

static void Node_Destroy(struct Node*x){
    if(x->left!=NULL)Node_Destroy(x->left);
    if(x->right!=NULL)Node_Destroy(x->right);
    if(x==NULL)free(x);
}

void BST_Destroy(struct BST*bst){
    Node_Destroy(bst->root);
    free(bst);
}

static struct Node* Node_Put(struct Node*x,const char*str,int value){
    if(x==NULL)return Node_Create(str,value);
    
    int cmp=strcmp(str,x->key);//strcmp的作用类似于less
    // fprintf(stderr,"%s:%s %d\n",str,x->key,cmp);
    if(cmp<0)
        x->left=Node_Put(x->left,str,value);
    else if(cmp>0)
        x->right=Node_Put(x->right,str,value);
    else x->val=value;
    x->n++;
    return x;
}

void BST_Put(struct BST*bst,const char*str,int value){
    bst->root=Node_Put(bst->root,str,value);
}

static int Node_Get(struct Node*x,const char*str){
    int cmp=strcmp(str,x->key);

    if(cmp<0)
        return Node_Get(x->left,str);
    else if(cmp>0)
        return Node_Get(x->right,str);
    return x->val;
}

int BST_Get(const struct BST*bst,const char*str){
    return Node_Get(bst->root,str);
}

// /* 缺点是没有真的删除这个最小值元素结点，删除的工作交给了用户 */
// static struct Node*Remove_MinNode(struct Node*x){
//     if(x->left==NULL)return x->right;
//     x->left=Remove_MinNode(x->left);
//     x->n--;
//     return x;
// }

// void Remove_Min(struct BST*bst){
//     bst->root=Remove_MinNode(bst->root);
// }

// static struct Node*Min_Node(struct Node*x){
//     if(x->left==NULL)return x;
//     return Min_Node(x->left);
// }

// const char* Min(const struct BST*bst){
//     return Min_Node(bst->root)->key;
// }

// static struct Node*Node_Delete(struct Node*x,const char*str){
//     if(x==NULL) return NULL;

//     int cmp=strcmp(str,x->key);
//     if(cmp<0)
//         x->left=Node_Delete()
// }

static void Print_Node(const struct Node*x){
    if(x->left!=NULL)Print_Node(x->left);
    printf("Key: %s, Val: %d\n",x->key,x->val);
    if(x->right!=NULL)Print_Node(x->right);
}

void Print(const struct BST*bst){
    Print_Node(bst->root);
}


int main(void)
{
    struct BST *bst;

    if((bst=BST_Create())==NULL)
        return 1;
    BST_Put(bst,"b",21);
    BST_Put(bst,"c",32);
    BST_Put(bst,"a",52);
 
    Print(bst);
    printf("b's value: %d\n",BST_Get(bst,"b"));

    BST_Destroy(bst);
    return 0;
}