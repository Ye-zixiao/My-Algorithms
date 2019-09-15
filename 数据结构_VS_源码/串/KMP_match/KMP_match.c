//						KMP算法
#include<stdio.h>
#include<string.h>
#define MAXSIZE 30

void get_next(char* st, int* next);									//计算next数组
int KMP_match(char* S, char* T);									//进行匹配，并将匹配的首字母位置返回给主调函数

int main(void)
{
	char st1[MAXSIZE] = "abcxagh";
	char st2[MAXSIZE] = "agh";
	int value;

	printf("the start number of string 2 in the string 1 is ");
	if ((value = KMP_match(st1, st2)) > 0)
		printf("%d\n", value);
	else
		printf("not found.\n");

	return 0;
}

void get_next(char* st, int* next)
{
	int tlen = strlen(st);
	int j, k;
	next[0] = -1;
	j = 0;					//后缀
	k = -1;					//前缀

	while (j < tlen - 1)
	{
		if (k == -1 || st[j] == st[k])				//当前缀位等于-1，或者前缀等于后缀，那么各自递增，去识别下一位
		{
			j++;
			k++;
			next[j] = k;							//j、k自增后，表示在序号j的字符前最大前缀后缀公共元素长度为k
		}
		else
			k = next[k];							//如果前缀后缀不再相同，那么k跳到next[k]的位置继续与st[j]去匹配，这个等效于是模式串的自我匹配
	}
}

int KMP_match(char* S, char* T)
{
	int next[MAXSIZE];
	get_next(T, next);
	int slen = strlen(S);
	int tlen = strlen(T);
	int i = 0;										//S串（主串）的下标位置，只增不减
	int j = 0;										//T串（子串、模式串）的下标位置

	while (i < slen && j < tlen)
	{
		if (j == -1 || S[i] == T[j])				//如果主串和模式串的一个字符匹配或者模式串的字符位置在-1，那么就都自增
		{
			i++;
			j++;
		}
		else
			j = next[j];							//失配时，让j跳到next[j]的位置继续与主串匹配
	}
	if (j == tlen)
		return i - j + 1;							//加上1，是为了补上数组下标少一造成的不协调
	else
		return -1;
}
