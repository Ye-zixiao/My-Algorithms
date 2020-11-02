#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static int *aux=NULL;

void merge(int array[],int low,int mid,int high){
    int i=low,j=mid+1;
    // memcpy(aux+sizeof(int)*low,array+sizeof(int)*low,sizeof(int)*(high-low+1));//??
    for(int i=low;i<=high;i++)
        aux[i]=array[i];
    for(int k=low;k<=high;++k){
        if(i>mid)
            array[k]=aux[j++];
        else if(j>high)
            array[k]=aux[i++];
        else if(aux[i]<aux[j])
            array[k]=aux[i++];
        else
            array[k]=aux[j++];
    }
}


void msort(int array[],int low,int high){
    if(low>=high) return;
    
    int mid=low+(high-low)/2;
    msort(array,low,mid);
    msort(array,mid+1,high);
    merge(array,low,mid,high);

    // for(int i=low;i<=high;++i)
    //     printf("%d ",array[i]);
    // putchar('\n');
}


void MergeSort(int array[],int N){
    if(aux==NULL)
        aux=calloc(N,sizeof(int));
    msort(array,0,N-1);
}


#define MIN(x,y) ((x)<(y)?(x):(y))

void MergeSort1(int array[],int N){
    if(aux==NULL)
        aux=calloc(N,sizeof(int));
    for(int sz=1;sz<N;sz*=2){
        for(int low=0;low<N-sz;low+=sz*2)
            merge(array,low,low+sz-1,MIN(low+sz*2-1,N-1));
    }
}


int main(void)
{
    int array[10];
    for(int i=0;i<10;i++)
        array[i]=10-i;

    // for(int i=0;i<10;++i)
    //     printf("%d ",array[i]);
    // putchar('\n');

    MergeSort(array,10);
    for(int i=0;i<10;i++)
        printf("%d\n",array[i]);
    return 0;
}