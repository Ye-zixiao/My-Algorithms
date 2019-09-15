//									BF算法
#include<stdio.h>
#include<string.h>
#define MAXSIZE 20

int violent_match(char* st1, char* st2);				//暴力匹配法

int main(void)
{
	char st1[MAXSIZE] = "abdxagh";
	char st2[MAXSIZE] = "agh";
	int ret_val;

	printf("The start number of the string \"abcdxagh\" to the string \"agh\" is ");
	if ((ret_val = violent_match(st1, st2)) > 0)
		printf("%d.\n", ret_val);
	else
		printf("not found.\n");

	return 0;
}

int violent_match(char* st1, char* st2)
{
	int slen = strlen(st1);
	int tlen = strlen(st2);

	int i = 0;
	int j = 0;
	while (i < slen && j < tlen)
	{
		if (st1[i] == st2[j])							//匹配时，两个计数值都相应的递增，去检查下一个字符是否相同
		{
			i++;
			j++;
		}
		else
		{												//失配时
			i = i - j + 1;								//i回溯到S串原来最开始匹配的下一个位置
			j = 0;										//j回溯到T串最开始的位置
		}
	}
	if (j == tlen)
		return i - j + 1;								//加上6的目的是由于数组是从0开始计数的，所以+1是为了补上这个差值
	else
		return -1;
}