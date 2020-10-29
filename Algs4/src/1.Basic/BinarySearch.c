#include <stdio.h>

int BinarySearch(int key,int arr[],int n){
    int low=0,high=n-1,mid;

    while(low<=high){
        mid=low+(high-low)/2;
        if(key<arr[mid]) high=mid-1;
        else if(key>arr[mid]) low=mid+1;
        else return mid;
    }
    return -1;
}

int rBSearch(int key,int arr[],int low,int high){
    if(low>high) return -1;

    int mid=low+(high-low)/2;
    if(key<arr[mid])
        return rBSearch(key,arr,low,mid-1);
    else if(key>arr[mid]) 
        return rBSearch(key,arr,mid+1,high);
    return mid;
}

int rBinarySearch(int key,int arr[],int n){
    return rBSearch(key,arr,0,n-1);
}

int main(void)
{
    int arr[10]={0,1,2,3,4,5,6,7,8,9};

    printf("5's position: %d\n",BinarySearch(5,arr,10));
    printf("5's position: %d\n",rBinarySearch(5,arr,10));
    return 0;
}