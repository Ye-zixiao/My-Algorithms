#include "Algs4.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

static char* temp = NULL;
static size_t tempsz = 0;

static void debug(void) {
	static int v = 0;
	fprintf(stderr, "get here(%d)?\n", v++);
}


static char* tempalloc(size_t sz) {
	if (sz != tempsz) {
		tempsz = sz;
		if (temp == NULL)
			return (temp = malloc(sz));
		else
			return (temp = realloc(temp, sz));
	}
}


void swap(char* arr, size_t sz, int i, int j) {
	assert(tempalloc(sz) != NULL);
	memcpy(temp, arr + sz * i, sz);
	memcpy(arr + sz * i, arr + sz * j, sz);
	memcpy(arr + sz * j, temp, sz);
}


/* 冒泡排序 */
void BubleSort(char* arr, size_t nmemb, size_t sz, _Comp* pf) {
	for (int N = nmemb; N > 0; --N) {
		for (int i = 1; i < N; ++i)
			if (pf(arr + sz * i, arr + sz * (i - 1)))
				swap(arr, sz, i - 1, i);
	}
}


/* 选择排序 */
void SelectSort(char* arr, size_t nmemb, size_t sz, _Comp* pf) {
	for (int i = 0, mpos; i < nmemb; ++i) {
		mpos = i;
		for (int j = i; j < nmemb; ++j)
			if (pf(arr + sz * j, arr + sz * mpos))
				mpos = j;
		swap(arr, sz, i, mpos);
	}
}


/* 插入排序 */
void InsertionSort(char* arr, size_t nmemb, size_t sz, _Comp* pf) {
	for (int i = 1; i < nmemb; ++i) {
		for (int j = i; j > 0 && pf(temp, arr + sz * (j - 1)); --j)
			swap(arr, sz, j, j - 1);
	}
}


/* 通过移动元素实现的插入排序 */
void InsertionSort1(char* arr, size_t nmemb, size_t sz, _Comp* pf) {
	assert(tempalloc(sz) != NULL);
	for (int i = 1, j; i < nmemb; ++i) {
		memcpy(temp, arr + sz * i, sz);
		for (j = i; j > 0 && pf(temp, arr + sz * (j - 1)); --j)
			memcpy(arr + sz * j, arr + sz * (j - 1), sz);
		memcpy(arr + sz * j, temp, sz);
	}
}


/* 希尔排序 */
void ShellSort(char* arr, size_t nmemb, size_t sz, _Comp* pf) {
	assert(tempalloc(sz) != NULL);
	for (int h = nmemb / 3; h >= 1; h /= 3) {
		for (int i = h, j; i < nmemb; ++i) {
			memcpy(temp, arr + sz * i, sz);
			for (j = i; j >= h && pf(temp, arr + sz * (j - h)); j -= h)
				memcpy(arr + sz * j, arr + sz * (j - h), sz);
			memcpy(arr + sz * j, temp, sz);
		}
	}
}


int ThreeMid(char* arr, size_t sz, int low, int high, _Comp* pf) {
	int tma[3] = { low,low + (high - low) / 2,high };

	for (int i = 1, j; i < 3; ++i) {
		int pos = tma[i];
		for (j = i; j > 0 && pf(arr + sz * pos, arr + sz * tma[j]); --j)
			tma[j] = tma[j - 1];
		tma[j] = pos;
	}
	return tma[1];
}


static int partition(char* arr, size_t sz, int low, int high, _Comp* pf) {
	int i = low, j = high + 1;
	char* pkey = NULL;

	swap(arr, sz, low, ThreeMid(arr, sz, low, high, pf));
	assert((pkey = malloc(sz)) != NULL);
	memcpy(pkey, arr + sz * low, sz);
	for (;;) {
		while (pf(arr + sz * (++i), pkey))
			if (i == high)break;
		while (pf(pkey, arr + sz * (--j)))
			if (j == low)break;
		if (i >= j)break;
		swap(arr, sz, i, j);
	}
	swap(arr, sz, low, j);

	free(pkey);
	return j;
}


static void rqsort(char* arr, size_t sz, int low, int high, _Comp* pf) {
	if (high - low <= 0)return;
	else if (high - low < 10)
		return InsertionSort1(arr + sz * low, high - low + 1, sz, pf);

	int k = partition(arr, sz, low, high, pf);
	rqsort(arr, sz, low, k - 1, pf);
	rqsort(arr, sz, k + 1, high, pf);
}


/* 快速排序 */
void QuickSort(char* arr, size_t nmemb, size_t sz, _Comp* pf) {
	rqsort(arr, sz, 0, nmemb - 1, pf);
}
