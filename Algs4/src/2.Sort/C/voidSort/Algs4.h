#ifndef ALGS4XX3E4_H_
#define ALGS4XX3E4_H_

#include <stddef.h>

typedef int _Comp(const void* lhs, const void* rhs);


void BubleSort(char* arr, size_t nmemb, size_t size, _Comp* pf);
void SelectSort(char* arr, size_t nmemb, size_t size, _Comp* pf);
void InsertionSort(char* arr, size_t nmemb, size_t size, _Comp* pf);
void InsertionSort1(char* arr, size_t nmemb, size_t size, _Comp* pf);
void ShellSort(char* arr, size_t nmemb, size_t size, _Comp* pf);
void QuickSort(char* arr, size_t nmemb, size_t size, _Comp* pf);


#endif