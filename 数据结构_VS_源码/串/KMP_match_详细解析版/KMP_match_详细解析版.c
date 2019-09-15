/*------------------------------------------详细解析版kmp算法-------------------*/
#include<stdio.h>
#include<string.h>
#define MAXSIZE 30

void get_next(char* st, int* next);
int kmp_match(char* text, char* pattern);

int main(void)
{
	char text[MAXSIZE] = "appbasfgsdbcfdgsa";
	char pattern[MAXSIZE] = "pba";
	int value;

	printf("The start number of string pattern in the string text ");
	if ((value = kmp_match(text, pattern)) > 0)
		printf("%d.\n", value);
	else
		printf("not found.\n");

	return 0;
}

void get_next(char* st, int* next)
{
	int tlen = strlen(st);
	next[0] = -1;
	int j = 0;									//其中j是next数组的下标，它只会自增，它是用于模式串的自我匹配
	int k = -1;									//k是活动性游标，记录着最大前后缀长度

	while (j < tlen - 1)
	{
		if (k == -1 || st[k] == st[j])			//字符匹配时或者当j=-1时，继续自增（这里是先比较后自增，将最大前后缀长度赋给下一个next元素）
		{										//st[k]是模式串的前缀要比较的字符，st[j]是模式串后缀要比较的字符
			j++;
			k++;
			next[j] = k;						//如果判断两个比较的字符相同，那么就会将p[j]前的最大前后缀公共元素长度给next[j]。即next[j+1]=next[j]+1
							/*改进版基本上就只在这里变化：
							if(st[k]!=st[j])
								next[j]=k;
							else
								next[j]=next[k];			//有点像递归的意思，但它本身不是递归，只不过给人的感觉很像
								*/
		}
		else
			k = next[k];						//将k回溯
	}
}
/*
		next数组的算法详解：
		如何在已知next[j]的前提下去推断next[j+1]?
			1、p[k]≠p[j]时，转而去用p[next[k]]去和p[j]进行比较。
			2、用p[next[k]]去和p[j]进行比较，因为p[k]前面和p[j]前面我们之前就比较过了，知道它们俩相同，而p[k]前又有相同的前后缀（假设）
		，那么p[j]前面也必然有块区域有相同的前后缀。所以可以认为p[next[k]]与p[j]前面的一小块区域已经比较过了且判定为相同，只要继续
		比较p[next[k]]和p[j]就可以确定两个小块区域是否稍小的最大前后缀公共元素长度，否则还要找下一个next[next[k]]，直到找到或者没有找到
		最终变成了0。

*/

int kmp_match(char* text, char* pattern)
{
	int text_len = strlen(text);
	int pattern_len = strlen(pattern);
	int next[MAXSIZE];
	get_next(pattern, next);
	int j = 0;										//j是文本串的下标，自增不减，kmp的核心就是主串不回溯
	int k = 0;										//k是模式串的下标，都是从0开始比较（这与next数组求值不同），按照next数组的规律进行活动性移动

	while (j < text_len && k < pattern_len)			//当模式串的所有字符比较完成，且全部匹配成功，就会由于k++变成pattern_len而退出
	{												//或者由于一直没有匹配成功导致遍历结束而退出了循环
		if (k == -1 || text[j] == pattern[k])		//如果相同，就自增继续比较下一位两者的元素
		{
			j++;
			k++;
		}
		else
		{
			k = next[k];							//失配时，模式串的下标回溯但是主串是不会回溯的
		}
	}
	if (k == pattern_len)
		return j - k + 1;							//若是由于模式串匹配成功而导致的退出循环说明就是在主串当中找到了子串，
													//故返回主串当中的首字母位置（注意要加1）
	else
		return -1;
}