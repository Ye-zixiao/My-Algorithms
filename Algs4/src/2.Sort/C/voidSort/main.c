#include <stdio.h>
#include "Algs4.h"

#define NUMSIZE 100

int shorter(const void* lhs, const void* rhs) {
	return *(int*)lhs < *(int*)rhs ? 1 : 0;
}


int greater(const void* lhs, const void* rhs) {
	return *(int*)lhs > * (int*)rhs ? 1 : 0;
}


static void show(int arr[], int N) {
	for (int i = 0; i < N; ++i)
		printf("%d\n", arr[i]);
}


int main(void)
{
	int arr[NUMSIZE];
	for (int i = 0; i < NUMSIZE; ++i)
		arr[i] = NUMSIZE - i;

	//BubleSort(arr, NUMSIZE, sizeof(int), shorter);
	//ShellSort(arr, NUMSIZE, sizeof(int), shorter);
	QuickSort(arr, NUMSIZE, sizeof(int), shorter);
	//printf("Array has been sorted!\n");
	show(arr, NUMSIZE);
	return 0;
}