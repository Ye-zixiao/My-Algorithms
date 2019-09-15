//						改进型KMP算法
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
	j = 0;					//后缀，是用来确定next数组的下标
	k = -1;					//前缀

	while (j < tlen - 1)
	{
		if (k == -1 || st[j] == st[k])				//当前缀位等于-1，或者前缀等于后缀，那么各自递增，去识别下一位
		{
			j++;
			k++;
			if (st[j] != st[k])
				next[j] = k;						//j、k自增后，表示在序号j的字符前最大前缀后缀公共元素长度为k。如果递增后的j、k位置的字符不相同
			else
				next[j] = next[k];					//如果自增后j跳到了next[j]=k的位置，但是这个位置上的字符和跳之前的字符还是一样，那么它必然会跟主串失配，所以还要继续跳转到next[next[k]]的位置
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


/*
“KMP的算法流程：

假设现在文本串S匹配到 i 位置，模式串P匹配到 j 位置
如果j = -1，或者当前字符匹配成功（即S[i] == P[j]），都令i++，j++，继续匹配下一个字符；
如果j != -1，且当前字符匹配失败（即S[i] != P[j]），则令 i 不变，j = next[j]。此举意味着失配时，模式串P相对于文本串S向右移动了j - next [j] 位。”
    我们发现如果某个字符匹配成功，模式串首字符的位置保持不动，仅仅是i++、j++；如果匹配失配，i 不变（即 i 不回溯），模式串会跳过匹配过的next [j]个字符。
	整个算法最坏的情况是，当模式串首字符位于i - j的位置时才匹配成功，算法结束。

*/