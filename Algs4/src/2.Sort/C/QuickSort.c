#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define NUMSIZE 100


static void show(int arr[],int N){
    for(int i=0;i<N;++i)
        printf("%d\n",arr[i]);
}


static void swap(int arr[],int i,int j){
    int temp=arr[i];
    arr[i]=arr[j];
    arr[j]=temp;
}

/* 对待排序数组进行三取样，使得返回的下标位置上的元素
   尽可能是数组中的中间值，从而避免快速排序中切分位置
   过大或者过小的问题 */
int ThreeMid(int arr[],int low,int high){
    int tma[3]={low,low+(high-low)/2,high};

    for(int i=1,j;i<3;++i){
        int tpos=tma[i];
        int temp=arr[tma[i]];
        for(j=i;j>0&&temp<arr[tma[j-1]];--j)
            tma[j]=tma[j-1];
        tma[j]=tpos;
    }
    // printf("tma[1]: %d\n",tma[1]);
    return tma[1];
}

/* 对数组进行切分，切分后前面的元素总是小于切分元素，后
    面的元素总是大于切分元素 */
int partition(int arr[],int low,int high){
    int i=low,j=high+1;
    swap(arr,low,ThreeMid(arr,low,high));
    int key=arr[low];

    for(;;){
        while(arr[++i]<key)
            if(i==high)break;
        while(key<arr[--j])
            if(j==low)break;
        if(j<=i)break;
        swap(arr,i,j);
    }
    swap(arr,low,j);
    return j;
}


/* 递归形式下的快速排序 */
void rqsort(int arr[],int low,int high){
    if(low>=high)return;

    int k=partition(arr,low,high);
    rqsort(arr,low,k-1);
    rqsort(arr,k+1,high);
}


void QuickSort(int arr[],int N){
    rqsort(arr,0,N-1);
}


int main(void)
{
    int arr[NUMSIZE];
    for(int i=0;i<NUMSIZE;++i)
        arr[i]=NUMSIZE-i;
    QuickSort(arr,NUMSIZE);
    show(arr,NUMSIZE);
    return 0;
}