#include <stdio.h>
#include <string.h>
#include <stdlib.h>


struct Node{
    struct Node*next;
    char value[1];/* 虽然value数组只有一个字节，但可以通过malloc扩展
                    字节大小，而且还能够很好的获取其指针 */
};


struct List{
    struct Node*first;
    struct Node*last;
    int ListSize;
};


/*
 * 链表初始化
 */
void ListInit(struct List*list){
    list->first=NULL;
    list->last=NULL;
    list->ListSize=0;
}


/*
 * 链表销毁 
 */
void ListDestroy(struct List*list){
    struct Node*node,*temp;

    node=list->first;
    while(node!=NULL){
        temp=node;
        node=node->next;
        free(temp);
    }
    list->first=NULL;
    list->last=NULL;
    list->ListSize=0;
}


/* 
 * 返回链表长度
 */
static inline 
int Size(const struct List*list){
    return list->ListSize;
}


/*
 * 链表是否为空
 */
static inline 
int isEmpty(const struct List*list){
    return list->ListSize==0;
}


/*
 * 链表前向插入数据
 */
struct Node* FInsert(struct List*list,void*value,size_t sz){
    struct Node*newNode;

    if((newNode=malloc(sizeof(struct Node)+sz-1))==NULL)
        return NULL;
    memcpy(newNode->value,value,sz);
    newNode->next=list->first;
    if(isEmpty(list)) list->last=newNode;
    list->first=newNode;
    list->ListSize++;
    return newNode;
}


/*
 * 链表后向插入 
 */
struct Node* BInsert(struct List*list,void*value,size_t sz){
    struct Node*newNode;

    if((newNode=malloc(sizeof(struct Node)+sz-1))==NULL)
        return NULL;
    memcpy(newNode->value,value,sz);
    newNode->next=NULL;
    if(isEmpty(list)) list->first=newNode;
    else list->last->next=newNode;
    list->last=newNode;
    list->ListSize++;
    return newNode;
}


/*
 * 链表普通插入，当node==NULL等同于FInsert() 
 */
struct Node* Insert(struct List*list,struct Node*node,void*value,size_t sz){
    struct Node*newNode;

    if(node==NULL)
        return FInsert(list,value,sz);
    else if(list->first==NULL)
        return NULL;
    if((newNode=malloc(sizeof(struct Node)+sz-1))==NULL)
        return NULL;
    memcpy(newNode->value,value,sz);
    newNode->next=node->next;
    node->next=newNode;
    if(list->last==node)
        list->last=newNode;
    list->ListSize++;
    return newNode;
}


/*
 * 链表前向删除元素 
 */
int FRemove(struct List*list,void*retval,size_t sz){
    struct Node*temp;

    if(isEmpty(list))
        return -1;
    if(retval!=NULL)//若retval非空才选择拷贝待删除元素中的数据
        memcpy(retval,list->first->value,sz);
    temp=list->first;
    list->first=list->first->next;
    free(temp);
    if(list->ListSize==1)
        list->last=NULL;
    list->ListSize--;
    return 0;     
}


//不支持bremove()


/*
 * 普通链表元素删除，当node==NULL时等同于FRemove()
 */
int Remove(struct List*list,struct Node*node,void*retval,size_t sz){
    struct Node*temp;

    if(node==NULL)
        return FRemove(list,retval,sz);
    if(node->next==NULL)
        return NULL;
    temp=node->next;
    node->next=temp->next;
    if(list->last==temp)
        list->last=node;
    if(retval!=NULL)
        memcpy(retval,temp->value,sz);
    free(temp);
    list->ListSize--;
    return 0;
}


/*
 * 链表遍历函数，使用用法类似于strtok() 
 */
struct Node* Iterator(struct List*list){
    static struct Node*node=NULL;
    struct Node*ret=NULL;
    
    if(list!=NULL)
        node=list->first;
    if(node!=NULL){
        ret=node;
        node=node->next;
    }
    return ret;
}


/*
 * 返回链表首元素指针
 */
inline static 
struct Node*First(struct List*list){
    return list->first;
}


/*
 * 返回链表尾元素指针 
 */
inline static 
struct Node*Last(struct List*list){
    return list->last;
}


/*
 * 在链表中查找指定元素 
 */
struct Node*Find(const struct List*list,const void*val,size_t sz,
                int(*pf)(const void*,const void*)){
    struct Node*node=list->first;

    while(node!=NULL){
        if(pf(node->value,val))
            return node;
        node=node->next;
    }
    return NULL;
}


int main(void){
    struct List list;
    double darr[10]={
        1.2,1.4,3.12,3.1,8.3,
        2.4,8.3,3.2,6.4,1.6
    };

    ListInit(&list);
    for(int i=0;i<5;i++)
        Insert(&list,NULL,(void*)&darr[i],sizeof(double));
    for(int i=5;i<10;++i)
        Insert(&list,list.last,(void*)&darr[i],sizeof(double));

    for(const struct Node*p=Iterator(&list);
            p!=NULL;p=Iterator(NULL)){
        printf("%.2f\n",*(double*)(p->value));
    }
    printf("current list size: %d\n",Size(&list));
    ListDestroy(&list);
    printf("final list size: %d\n",Size(&list));
    
    return 0;
}