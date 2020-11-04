#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMSIZE 100

int Comp(const void*lhs,const void*rhs){
    return *(double*)lhs<*(double*)rhs?1:0;
}

static void swap(void *arr,size_t sz,int i,int j){
    static char*tmp=NULL;
    static size_t tmpsz=0;

    if(tmpsz!=sz){
        tmpsz=sz;
        if(tmp==NULL) 
            tmp=malloc(sz);
        else tmp=realloc(tmp,sz);
    }
    memcpy(tmp,arr+sz*i,sz);
    memcpy(arr+sz*i,arr+sz*j,sz);
    memcpy(arr+sz*j,tmp,sz);   
}

void SelectSort(void*arr,size_t sz,int mems,int (*pf)(const void*,const void*)){
    for(int i=0,mpos;i<mems;i++){
        mpos=i;
        for(int j=i;j<mems;j++){
            if(pf(arr+sz*j,arr+sz*mpos))
                mpos=j;
        }
        swap(arr,sz,i,mpos);
    }
}

static void show(double arr[],int N){
    for(int i=0;i<N;++i)
        printf("%.1f\n",arr[i]);
}

int main(void)
{
    double arr[NUMSIZE];
    for(int i=0;i<NUMSIZE;++i)
        arr[i]=(double)(NUMSIZE-i)-0.1;
    SelectSort(arr,sizeof(double),NUMSIZE,Comp);
    show(arr,NUMSIZE);

    return 0;
}